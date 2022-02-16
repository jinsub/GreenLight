#pragma once
#include <vector>
#include "Types.h"

class IOutput
{
public:
	virtual void Show(const vector<EmployeeInfo>& info) = 0;
	virtual void Show(const int infoCount) = 0;
};