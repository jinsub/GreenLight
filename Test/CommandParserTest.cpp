#include "pch.h"
#include "../GreenLight/CommandParser.cpp"

class CommandPerserTest : public testing::Test
{
protected:
	void SetUp(void) override
	{
		auto file = fopen(fileName_, "w");
		for (int sampleNum = 0; sampleNum < inputCount_; sampleNum++)
		{
			fprintf(file, "ADD, , , ,%d,JINSEOB YANG,CL2,010-2644-6239,19920616,PRO\n", 17106626 + sampleNum);
		}
		fclose(file);
	}
	void TearDown(void) override
	{
		std::remove(fileName_);
	}

	static constexpr char* fileName_ = "test.txt";
	static constexpr int inputCount_ = 10;
	CommandParser parser_;
};

TEST_F(CommandPerserTest, Construct)
{
}

TEST_F(CommandPerserTest, ParseFile)
{
	auto result = parser_.ParseFile(fileName_);
	EXPECT_EQ(result.size(), inputCount_);
}

TEST_F(CommandPerserTest, ParseLine)
{
	auto result = parser_.ParseLine(parser_.ParseFile(fileName_));
	EXPECT_EQ(result.size(), inputCount_);
}