#pragma once
#include <vector>
#include "Types.h"

enum class PrintOption
{
	PrintLines,
	PrintCount
};

class IPrinter
{
public:
	virtual void Print(PrintOption printOption, std::vector<EmployeeInfo> info) = 0;
};
