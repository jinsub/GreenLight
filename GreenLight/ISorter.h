#pragma once
#include <vector>
#include "Types.h"

class ISorter
{
public:
	virtual vector<EmployeeInfo> sort(const vector<EmployeeInfo>& info) = 0;
};