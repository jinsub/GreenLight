#include "FileOutput.h"

void FileOutput::Show(const CommandType commandType, const vector<EmployeeInfo>& info)
{
	fout_.open(outputFile_);

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

			if (loopCount == 5) {
				break;
			}
		}
	}
	fout_.close();
}

void FileOutput::Show(const CommandType commandType, const int infoCount)
{
	fout_.open(outputFile_);

	fout_ << ConvertCmdTypeToString_(commandType);

	if (infoCount == 0)
	{
		fout_ << "NONE" << "\n";
	}
	else
	{
		fout_ << infoCount << "\n";
	}
	fout_.close();
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

string FileOutput::MergeString_(EmployeeInfo info)
{
	string result = "";
	
	result += (std::to_string(GetShrinkEmployeeNum_(info.num_)) + ",");
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