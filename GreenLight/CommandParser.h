#pragma once
#include <iostream>
#include <vector>
#include "ControlTypes.h"
#include "IDatabase.h"
#include "IPrinter.h"

using namespace std;

enum class CmdIndex {
	CmdType = 0,
	Opt1,
	Opt2,
	Opt3,
	ArgStart,
	Filter = ArgStart
};

class CommandParser
{
public:
	vector<string> ParseFile(const string inputFile);
	vector<Command> ParseLine(vector<string>& lines);

private:
	Command MakeCommand_(const vector<string>& str);

	CommandType GetCommandType_(const string& commandType);
	PrintOption GetPrintOption_(const string& printOption);
	FilterOption GetFilterOption_(const string& filterOption, const string& filterField);
};
