#include "pch.h"
#include "../GreenLight/ModCommandProcessor.cpp"
#include "DatabaseMock.h"
#include "PrinterMock.h"

using namespace testing;

class ModCommandProcessorTest : public testing::Test
{
protected:
	void SetUp(void) override {
		databaseMock_ = new DatabaseMock();
		printerMock_ = new PrinterMock();
		processor_ = new ModCommandProcessor(databaseMock_, printerMock_);
	}
	void TearDown(void) override {
		delete databaseMock_;
		delete printerMock_;
		delete processor_;
	}

	DatabaseMock* databaseMock_;
	PrinterMock* printerMock_;
	ModCommandProcessor* processor_;
};

TEST_F(ModCommandProcessorTest, Construct) {
}

TEST_F(ModCommandProcessorTest, ProcessMod) {
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
