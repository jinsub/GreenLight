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

	CommandParser m_parser;
};

TEST_F(CommandPerserTest, Construct)
{
}

TEST_F(CommandPerserTest, Parse)
{
	auto fileName = "input.text";
	auto result = m_parser.Parse(fileName);
	EXPECT_FALSE(result.empty());
}