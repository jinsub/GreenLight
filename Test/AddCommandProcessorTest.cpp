#include "pch.h"
#include "../GreenLight/CommandProcessor.cpp"
#include "../GreenLight/AddCommandProcessor.cpp"
#include "DatabaseMock.h"

using namespace testing;

class AddCommandProcessorTest : public testing::Test
{
protected:
	void SetUp(void) override {
		databaseMock_ = new DatabaseMock();
		processor_ = new AddCommandProcessor(databaseMock_);
	}
	void TearDown(void) override {
		delete databaseMock_;
		delete processor_;
	}

	DatabaseMock* databaseMock_;
	AddCommandProcessor* processor_;
};

TEST_F(AddCommandProcessorTest, Construct) {
}


TEST_F(AddCommandProcessorTest, Process) {
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