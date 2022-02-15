#pragma once
#include <vector>
#include "Types.h"

class IOutput
{
public:
	virtual void show(const vector<EmployeeInfo>& info) = 0;
};