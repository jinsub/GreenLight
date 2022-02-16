#pragma once
#include <vector>
#include "Types.h"

class IOutput
{
public:
	virtual void Show(const PrintOption printOption, const vector<EmployeeInfo>& info) = 0;
};