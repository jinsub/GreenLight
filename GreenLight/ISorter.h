#pragma once
#include <vector>
#include "Types.h"

class ISorter {
public:
	virtual vector<EmployeeInfo> Sort(const vector<EmployeeInfo>& info) = 0;
};