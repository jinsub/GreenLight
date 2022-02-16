#pragma once
#include <iostream>
#include <vector>
#include "IDatabase.h"
#include "IPrinter.h"

using namespace std;

enum class CommandType
{
	ADD,
	DEL,
	SCH,
	MOD,
	INVALID
};

enum class CmdIndex
{
	CmdType = 0,
	Opt1,
	Opt2,
	Opt3,
	ArgStart,
	Filter = ArgStart
};

struct Command
{
	CommandType type_;
	PrintOption printOptino_;
	FilterOption filterOption_;
	std::vector<std::string> arguments_;
};

class CommandParser
{
public:
	vector<string> ParseFile(const string inputFile);
	vector<Command> ParseLine(vector<string>& lines);

private:
	vector<string> Split_(string str, const char separator);
	Command MakeCommand_(const vector<string>& str);

	CommandType GetCommandType_(const string& commandType);
	PrintOption GetPrintOption_(const string& printOption);
	FilterOption GetFilterOption_(const string& filterOption, const string& filterField);
};
