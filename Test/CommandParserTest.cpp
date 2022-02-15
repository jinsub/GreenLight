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

	CommandParser m_parser;
};

TEST_F(CommandPerserTest, Construct)
{
}

TEST_F(CommandPerserTest, ParseFile)
{
	constexpr int InputCount = 10;
	auto fileName = "input.text";
	_MakeSampleInput(fileName, InputCount);

	auto result = m_parser.ParseFile(fileName);
	EXPECT_EQ(result.size(), InputCount);
}

TEST_F(CommandPerserTest, ParseLine)
{
	vector<string> lines;
	auto result = m_parser.ParseLine(lines);
	EXPECT_TRUE(result.empty());
}