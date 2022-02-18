#include "pch.h"
#include "../GreenLight/SchCommandProcessor.cpp"
#include "DatabaseMock.h"
#include "PrinterMock.h"

using namespace testing;

class SchCommandProcessorTest : public testing::Test
{
protected:
	void SetUp(void) override {
		databaseMock_ = new DatabaseMock();
		printerMock_ = new PrinterMock();
		processor_ = new SchCommandProcessor(databaseMock_, printerMock_);
	}
	void TearDown(void) override {
		delete databaseMock_;
		delete printerMock_;
		delete processor_;
	}

	DatabaseMock* databaseMock_;
	PrinterMock* printerMock_;
	SchCommandProcessor* processor_;
};

TEST_F(SchCommandProcessorTest, Construct) {
}


TEST_F(SchCommandProcessorTest, ProcessSch) {
	Command command;
	command.type_ = CommandType::SCH;
	command.printOption_ = PrintOption::PrintCount;
	command.filterOption_ = FilterOption::FirstName;
	command.arguments_.push_back("name");
	command.arguments_.push_back("JINSEOB YANG");

	EmployeeInfo info;
	vector<EmployeeInfo> result;
	ON_CALL(*databaseMock_, ReadDB(_)).WillByDefault(Return(result));
	EXPECT_CALL(*databaseMock_, ReadDB(_));
	EXPECT_CALL(*printerMock_, Print(_, _, _));

	processor_->Process(command);
}
