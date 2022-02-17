#include "FileOutput.h"

#define MAX_PRINT_CNT (5)

void FileOutput::Show(const CommandType commandType, const vector<EmployeeInfo>& info)
{
//	fout_.open(outputFile_);

	if (info.size() == 0)
	{
		fout_ << ConvertCmdTypeToString_(commandType);
		fout_ << "NONE" << "\n";
	}
	else
	{
		int loopCount = 0;

		for (auto iter : info)
		{
			fout_ << ConvertCmdTypeToString_(commandType);
			fout_ << MergeString_(iter) << "\n";
			++loopCount;

			if (loopCount == MAX_PRINT_CNT) {
				break;
			}
		}
	}
//	fout_.close();
}

void FileOutput::Show(const CommandType commandType, const int infoCount)
{
//	fout_.open(outputFile_);

	fout_ << ConvertCmdTypeToString_(commandType);

	if (infoCount == 0)
	{
		fout_ << "NONE" << "\n";
	}
	else
	{
		fout_ << infoCount << "\n";
	}
//	fout_.close();
}

int FileOutput::GetShrinkEmployeeNum_(const int employeeNum) {
	constexpr int TwentyCentry = 1900000000;
	constexpr int TwentyOneCentry = 2000000000;

	if (employeeNum >= TwentyOneCentry)
	{
		return employeeNum - TwentyOneCentry;
	}
	return employeeNum - TwentyCentry;
}


string FileOutput::ConvertEmployeeNumToString_(const int employeeNum)
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

string FileOutput::MergeString_(EmployeeInfo info)
{
	string result = "";
	
	int employeeNum = GetShrinkEmployeeNum_(info.num_);

	result += (ConvertEmployeeNumToString_(employeeNum) + ",");
	result += (info.GetFullName() + ",");
	result += (info.cl_ + ",");
	result += (info.GetFullPhoneNum() + ",");
	result += (info.GetFullBirthday() + ",");
	result += (info.certi_);

	return result;
}

string FileOutput::ConvertCmdTypeToString_(CommandType commandType)
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