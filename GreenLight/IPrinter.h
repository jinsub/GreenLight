#pragma once
#include <vector>
#include "Types.h"
class IPrinter
{
public:
	virtual void Print(const PrintOption printOption, const std::vector<EmployeeInfo>& info) = 0;
};
