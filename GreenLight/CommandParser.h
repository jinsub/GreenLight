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

struct Command
{
	CommandType type;
	PrintOption printOptino;
	FilterOption filterOption;
	std::vector<std::string> arguments;
};

class CommandParser
{
public:
	vector<string> ParseFile(const string inputFile);
	vector<Command> ParseLine(vector<string>& lines);

private:
	vector<string> Split_(string str, const char separator);
	Command MakeCommand_(vector<string>& str);
};
