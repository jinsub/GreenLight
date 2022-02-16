#include "pch.h"
#include "../GreenLight/CommandProcessor.cpp"

class CommandProcessorTest : public testing::Test
{
protected:
	void SetUp(void) override {
		processor_ = new CommandProcessor(nullptr, nullptr);
	}
	void TearDown(void) override {
	}

	CommandProcessor* processor_;
};

TEST_F(CommandProcessorTest, Construct) {
}
