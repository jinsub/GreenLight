#include "pch.h"
#include "../GreenLight/CommandParser.cpp"

class CommandPerserTest : public testing::Test
{
protected:
	void SetUp(void) override {
	}
	void TearDown(void) override {
	}

	CommandParser parser_;
};

TEST_F(CommandPerserTest, Construct) {
}

TEST_F(CommandPerserTest, ParseFile) {
	constexpr char* fileName = "test.txt";
	constexpr int inputCount = 10;
	auto file = fopen(fileName, "w");
	for (int sampleNum = 0; sampleNum < inputCount; sampleNum++)
	{
		fprintf(file, "ADD, , , ,12345678,JINSEOB YANG,CL2,010-1234-5678,20220215,PRO\n");
	}
	fclose(file);

	auto result = parser_.ParseFile(fileName);
	EXPECT_EQ(result.size(), inputCount);

	std::remove(fileName);
}

TEST_F(CommandPerserTest, ParseLine_PrintCountCheck) {
	vector<string> lines;
	lines.push_back("ADD, , , ,12345678,JINSEOB YANG,CL2,010-1234-5678,20220215,PRO");
	lines.push_back("DEL, , , ,employNum,12345678");
	lines.push_back("SCH, , , ,name,JINSEOB YANG");
	lines.push_back("MOD, , , ,cl,CL2,phoneNum,010-1234-5678");

	auto result = parser_.ParseLine(lines);
	EXPECT_EQ(result.size(), lines.size());

	for (auto command : result) {
		EXPECT_EQ(command.printOptino, PrintOption::PrintCount);
	}
}

TEST_F(CommandPerserTest, ParseLine_PrintLineCheck) {
	vector<string> lines;
	lines.push_back("ADD,-p, , ,12345678,JINSEOB YANG,CL2,010-1234-5678,20220215,PRO");
	lines.push_back("DEL,-p, , ,employNum,12345678");
	lines.push_back("SCH,-p, , ,name,JINSEOB YANG");
	lines.push_back("MOD,-p, , ,cl,CL2,phoneNum,010-1234-5678");

	auto result = parser_.ParseLine(lines);
	EXPECT_EQ(result.size(), lines.size());

	for (auto command : result) {
		EXPECT_EQ(command.printOptino, PrintOption::PrintLines);
	}
}

TEST_F(CommandPerserTest, ParseLine_FilterOptionCheck) {
	vector<string> lines;
	lines.push_back("DEL, , , ,employeeNum,12345678");
	lines.push_back("SCH, , , ,name,JINSEOB YANG");
	lines.push_back("MOD, , , ,cl,CL2,phoneNum,010-1234-5678");
	lines.push_back("DEL, , , ,phoneNum,010-1234-5678");
	lines.push_back("SCH, , , ,birthday,010-1234-5678");
	lines.push_back("MOD, , , ,certi,12345678,phoneNum,010-1234-5678");
	lines.push_back("DEL, ,-f, ,name,JINSEOB");
	lines.push_back("SCH, ,-l, ,name,YANG");
	lines.push_back("MOD, ,-m, ,phoneNum,1234,phoneNum,010-1234-5678");
	lines.push_back("DEL, ,-l, ,phoneNum,5678");
	lines.push_back("SCH, ,-y, ,birthday,2022");
	lines.push_back("MOD, ,-m, ,birthday,02,phoneNum,010-1234-5678");
	lines.push_back("DEL, ,-d, ,birthday,15");

	auto result = parser_.ParseLine(lines);
	EXPECT_EQ(result.size(), lines.size());

	for (int index = 0; index < result.size(); index++) {
		auto command = result.at(index);
		auto option = static_cast<FilterOption>(index);
		EXPECT_EQ(command.filterOption, option);
	}
}
