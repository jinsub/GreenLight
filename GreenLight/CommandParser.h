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
	MOD
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
	vector<Command> Parse(string inputFile);
};
