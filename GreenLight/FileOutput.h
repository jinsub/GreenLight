#pragma once
#include "IOutput.h"
#include <fstream>

using namespace std;


class FileOutput : public IOutput
{
public:
	FileOutput(string outputFile) :
		outputFile_(outputFile)
	{
		fout_.open(outputFile_);
	}
	~FileOutput()
	{
		fout_.close();
	}

	void Show(const CommandType commandType, const vector<EmployeeInfo>& info) override;
	void Show(const CommandType commandType, const int infoCount) override;

private:
	string MergeString_(EmployeeInfo info);
	string ConvertCmdTypeToString_(CommandType commandType);
	string ConvertEmployeeNumToString_(const int employeeNum);
	int GetShrinkEmployeeNum_(const int employeeNum);

	ofstream fout_;
	string outputFile_;
};