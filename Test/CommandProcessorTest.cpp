#include "pch.h"
#include "../GreenLight/CommandProcessor.cpp"
#include "DatabaseMock.h"
#include "PrinterMock.h"

using namespace testing;

class CommandProcessorTest : public testing::Test
{
protected:
	void SetUp(void) override {
		databaseMock_ = new DatabaseMock();
		printerMock_ = new PrinterMock();
		processor_ = new CommandProcessor(databaseMock_, printerMock_);
	}
	void TearDown(void) override {
		delete databaseMock_;
		delete printerMock_;
		delete processor_;
	}

	DatabaseMock* databaseMock_;
	PrinterMock* printerMock_;
	CommandProcessor* processor_;
};

TEST_F(CommandProcessorTest, Construct) {
}

TEST_F(CommandProcessorTest, ProcessAdd) {
	Command command;
	command.type_ = CommandType::ADD;
	command.printOption_ = PrintOption::Invalid;
	command.filterOption_ = FilterOption::Invalid;
	command.arguments_.push_back("12345678");
	command.arguments_.push_back("JINSEOB YANG");
	command.arguments_.push_back("CL2");
	command.arguments_.push_back("010-1234-5678");
	command.arguments_.push_back("20220215");
	command.arguments_.push_back("PRO");

	EmployeeInfo info;
	vector<EmployeeInfo> result;
	ON_CALL(*databaseMock_, CreateDB(_)).WillByDefault(Return(result));
	EXPECT_CALL(*databaseMock_, CreateDB(_));

	processor_->Process(command);
}

TEST_F(CommandProcessorTest, ProcessDel) {
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

TEST_F(CommandProcessorTest, ProcessSch) {
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

TEST_F(CommandProcessorTest, ProcessMod) {
	Command command;
	command.type_ = CommandType::MOD;
	command.printOption_ = PrintOption::PrintLines;
	command.filterOption_ = FilterOption::None;
	command.arguments_.push_back("cl");
	command.arguments_.push_back("CL2");
	command.arguments_.push_back("cl");
	command.arguments_.push_back("CL3");

	EmployeeInfo info;
	vector<EmployeeInfo> result;
	ON_CALL(*databaseMock_, UpdateDB(_, _)).WillByDefault(Return(result));
	EXPECT_CALL(*databaseMock_, UpdateDB(_, _));
	EXPECT_CALL(*printerMock_, Print(_, _, _));

	processor_->Process(command);
}
