#include "FileOutput.h"


void FileOutput::Show(const CommandType commandType, const vector<EmployeeInfo>& info)
{
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
}

void FileOutput::Show(const CommandType commandType, const int infoCount)
{
	fout_ << ConvertCmdTypeToString_(commandType);

	if (infoCount == 0)
	{
		fout_ << "NONE" << "\n";
	}
	else
	{
		fout_ << infoCount << "\n";
	}
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
	else if ((employeeNum < 10000000) && (employeeNum >= 1000000))
	{
		result = "0" + std::to_string(employeeNum);
	}
	else if ((employeeNum < 1000000) && (employeeNum >= 100000))
	{
		result = "00" + std::to_string(employeeNum);
	}
	else if ((employeeNum < 100000) && (employeeNum >= 10000))
	{
		result = "000" + std::to_string(employeeNum);
	}
	else if ((employeeNum < 10000) && (employeeNum >= 1000))
	{
		result = "0000" + std::to_string(employeeNum);
	}
	else if ((employeeNum < 1000) && (employeeNum >= 100))
	{
		result = "00000" + std::to_string(employeeNum);
	}
	else if ((employeeNum < 100) && (employeeNum >= 10))
	{
		result = "000000" + std::to_string(employeeNum);
	}
	else if ((employeeNum < 10) && (employeeNum >= 1))
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