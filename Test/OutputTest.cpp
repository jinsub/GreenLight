#include "pch.h"
#include "gmock/gmock.h"
#include "../GreenLight/FileOutput.cpp"
#include <istream>

class OutputTest : public ::testing::Test {
protected:
	void SetUp(void) override
	{
		outputFile = "output.txt";
		fileOutput_ = new FileOutput(outputFile);

		employee_1 = {
			2000018054,
			string("CHANGHYUN"), string("HYUN"),
			string("CL2"),
			string("6606"), string("4404"),
			string("1995"), string("02"), string("14"),
			string("PRO")
		};

		employee_2 = {
			2017018052,
			string("HYELIN"), string("JANG"),
			string("CL2"),
			string("4932"), string("1423"),
			string("1991"), string("05"), string("14"),
			string("PRO")
		};

		employee_3 = {
			1989043212,
			string("GILDONG"), string("HONG"),
			string("CL4"),
			string("3214"), string("5677"),
			string("1985"), string("12"), string("14"),
			string("PRO")
		};

	}

	void TearDown(void) override
	{
		delete fileOutput_;
	}

	string ConvertCmdTypeToString(CommandType commandType)
	{
		switch (commandType)
		{
		case CommandType::DEL:
			return "DEL,";
		case CommandType::MOD:
			return "MOD,";
		case CommandType::SCH:
			return "SCH,";
		default:
			return "ERROR,";
		}
	}

	string ConvertEmployeeNumToString(const int employeeNum)
	{
		string result;

		if ((employeeNum <= 99999999) && (employeeNum >= 10000000))
		{
			result = std::to_string(employeeNum);
		}
		else if ((employeeNum < 10000000) && (employeeNum >= 01000000))
		{
			result = "0" + std::to_string(employeeNum);
		}
		else if ((employeeNum < 01000000) && (employeeNum >= 00100000))
		{
			result = "00" + std::to_string(employeeNum);
		}
		else if ((employeeNum < 00100000) && (employeeNum >= 00010000))
		{
			result = "000" + std::to_string(employeeNum);
		}
		else if ((employeeNum < 00010000) && (employeeNum >= 00001000))
		{
			result = "0000" + std::to_string(employeeNum);
		}
		else if ((employeeNum < 00001000) && (employeeNum >= 00000100))
		{
			result = "00000" + std::to_string(employeeNum);
		}
		else if ((employeeNum < 00000100) && (employeeNum >= 00000010))
		{
			result = "000000" + std::to_string(employeeNum);
		}
		else if ((employeeNum < 00000010) && (employeeNum >= 00000001))
		{
			result = "0000000" + std::to_string(employeeNum);
		}

		return result;
	}

	int GetShrinkEmployeeNum(const int employeeNum) {
		constexpr int TwentyCentry = 1900000000;
		constexpr int TwentyOneCentry = 2000000000;

		if (employeeNum >= TwentyOneCentry)
		{
			return employeeNum - TwentyOneCentry;
		}
		return employeeNum - TwentyCentry;
	}


	string MergeString(CommandType commandType, EmployeeInfo info)
	{
		string result = "";

		int employeeNum = GetShrinkEmployeeNum(info.num_);

		result += (ConvertCmdTypeToString(commandType));
		result += (ConvertEmployeeNumToString(employeeNum) + ",");
		result += (info.GetFullName() + ",");
		result += (info.cl_ + ",");
		result += (info.GetFullPhoneNum() + ",");
		result += (info.GetFullBirthday() + ",");
		result += (info.certi_);

		return result;
	}

	FileOutput* fileOutput_;
	string outputFile;
	EmployeeInfo employee_1;
	EmployeeInfo employee_2;
	EmployeeInfo employee_3;
};

TEST_F(OutputTest, FileOutputTest_ShowInfo)
{
	vector<EmployeeInfo> info;
	info.push_back(employee_3);
	info.push_back(employee_2);
	info.push_back(employee_1);

	CommandType cmdType = CommandType::MOD;
	fileOutput_->Show(cmdType, info);

	ifstream ifs;
	ifs.open(outputFile);

	string output;
	int loopCount = 0;
	auto iter = info.begin();

	while (getline(ifs, output))
	{
		EXPECT_EQ(output, MergeString(cmdType, *iter));
		++iter;
		++loopCount;
	}

	EXPECT_EQ(true, (loopCount <= 5));
}

TEST_F(OutputTest, FileOutputTest_ShowInfo_NONE)
{
	vector<EmployeeInfo> info;
	
	CommandType cmdType = CommandType::MOD;
	fileOutput_->Show(cmdType, info);

	ifstream ifs;
	ifs.open(outputFile);

	string output;
	getline(ifs, output);

	string result = ConvertCmdTypeToString(cmdType) + "NONE";
	EXPECT_EQ(output, result);
}

TEST_F(OutputTest, FileOutputTest_ShowCount)
{
	vector<EmployeeInfo> info;
	info.push_back(employee_3);
	info.push_back(employee_2);
	info.push_back(employee_1);

	CommandType cmdType = CommandType::MOD;
	fileOutput_->Show(cmdType, info.size());

	ifstream ifs;
	ifs.open(outputFile);

	string output;
	getline(ifs, output);

	string result = ConvertCmdTypeToString(cmdType) + std::to_string(info.size());
	EXPECT_EQ(output, result);
}

TEST_F(OutputTest, FileOutputTest_ShowCount_NONE)
{
	vector<EmployeeInfo> info;

	CommandType cmdType = CommandType::MOD;
	fileOutput_->Show(cmdType, info.size());

	ifstream ifs;
	ifs.open(outputFile);

	string output;
	getline(ifs, output);

	string result = ConvertCmdTypeToString(cmdType) + "NONE";
	EXPECT_EQ(output, result);
}