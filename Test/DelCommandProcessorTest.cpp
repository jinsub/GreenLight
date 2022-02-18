#include "pch.h"
#include "../GreenLight/DelCommandProcessor.cpp"
#include "DatabaseMock.h"
#include "PrinterMock.h"

using namespace testing;

class DelCommandProcessorTest : public testing::Test
{
protected:
	void SetUp(void) override {
		databaseMock_ = new DatabaseMock();
		printerMock_ = new PrinterMock();
		processor_ = new DelCommandProcessor(databaseMock_, printerMock_);
	}
	void TearDown(void) override {
		delete databaseMock_;
		delete printerMock_;
		delete processor_;
	}

	DatabaseMock* databaseMock_;
	PrinterMock* printerMock_;
	DelCommandProcessor* processor_;
};

TEST_F(DelCommandProcessorTest, Construct) {
}

TEST_F(DelCommandProcessorTest, ProcessDel) {
	Command command;
	command.type_ = CommandType::DEL;
	command.printOption_ = PrintOption::PrintCount;
	command.filterOption_ = FilterOption::None;
	command.arguments_.push_back("name");
	command.arguments_.push_back("JINSEOB YANG");

	EmployeeInfo info;
	vector<EmployeeInfo> result;
	ON_CALL(*databaseMock_, DeleteDB(_)).WillByDefault(Return(result));
	EXPECT_CALL(*databaseMock_, DeleteDB(_));
	EXPECT_CALL(*printerMock_, Print(_, _, _));

	processor_->Process(command);
}
