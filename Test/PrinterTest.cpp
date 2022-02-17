#include "pch.h"
#include "gmock/gmock.h"
#include "../GreenLight/Printer.cpp"
#include "../GreenLight/ISorter.h"
#include "../GreenLight/IOutput.h"

using namespace testing;

class MockSorter : public ISorter {
public:
	MOCK_METHOD(vector<EmployeeInfo>, Sort, (const vector<EmployeeInfo>& info), (override));
};

class MockOutput : public IOutput
{
public:
	MOCK_METHOD(void, Show, (const vector<EmployeeInfo>& info), (override));
	MOCK_METHOD(void, Show, (const int infoCount), (override));
};

class PrinterTest : public testing::Test {
protected:
	void SetUp(void) override
	{
		mockSorter = new MockSorter();
		mockOutput = new MockOutput();
		printer_ = new Printer(mockSorter, mockOutput);
	}
	void TearDown(void) override
	{
		delete printer_;
		delete mockSorter;
		delete mockOutput;
	}

	Printer* printer_ = nullptr;
	MockSorter* mockSorter;
	MockOutput* mockOutput;
};

TEST_F(PrinterTest, printTestOptionLines)
{
	const vector<EmployeeInfo> info;
	vector<EmployeeInfo> result;

	ON_CALL(*mockSorter, Sort(info)).WillByDefault(Return(result));

	EXPECT_CALL(*mockSorter, Sort(info));
	EXPECT_CALL(*mockOutput, Show(info));

	printer_->Print(CommandType::DEL, PrintOption::PrintLines, info);

}

TEST_F(PrinterTest, printTestOptionCount)
{
	const vector<EmployeeInfo> info;
	vector<EmployeeInfo> result;

	ON_CALL(*mockSorter, Sort(info)).WillByDefault(Return(result));

	EXPECT_CALL(*mockSorter, Sort(info));
	EXPECT_CALL(*mockOutput, Show(result.size()));

	printer_->Print(CommandType::DEL, PrintOption::PrintCount, info);

}