#include "pch.h"
#include "../GreenLight/CommandParser.cpp"

class CommandPerserTest : public testing::Test
{
protected:
	void SetUp(void) override
	{
	}
	void TearDown(void) override
	{
	}

	void _MakeSampleInput(const char* fileName, const int inputCount)
	{
		auto file = fopen(fileName, "w");
		for (int sampleNum = 0; sampleNum < inputCount; sampleNum++)
		{
			fprintf(file, "ADD, , , ,%d,JINSEOB YANG,CL2,010-2644-6239,19920616,PRO\n", 17106626 + sampleNum);
		}
		fclose(file);
	}

	CommandParser parser_;
};

TEST_F(CommandPerserTest, Construct)
{
}

TEST_F(CommandPerserTest, ParseFile)
{
	constexpr int InputCount = 10;
	auto fileName = "input.text";
	_MakeSampleInput(fileName, InputCount);

	auto result = parser_.ParseFile(fileName);
	EXPECT_EQ(result.size(), InputCount);
}

TEST_F(CommandPerserTest, ParseLine)
{
	constexpr int InputCount = 10;
	auto fileName = "input.text";
	_MakeSampleInput(fileName, InputCount);

	auto result = parser_.ParseLine(parser_.ParseFile(fileName));
	EXPECT_EQ(result.size(), InputCount);
}