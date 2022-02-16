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
	MOCK_METHOD(void, Show, (const PrintOption printOption, const vector<EmployeeInfo>& info), (override));
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

TEST_F(PrinterTest, printTest)
{
	const vector<EmployeeInfo> info;
	vector<EmployeeInfo> result;

	ON_CALL(*mockSorter, Sort(info)).WillByDefault(Return(result));

	printer_->Print(PrintOption::PrintLines, info);

	EXPECT_CALL(*mockSorter, Sort(info));
	EXPECT_CALL(*mockOutput, Show(PrintOption::PrintLines, info));
}