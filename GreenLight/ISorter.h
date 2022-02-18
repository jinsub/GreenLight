#pragma once
#include <vector>
#include "Types.h"

class ISorter {
public:
	virtual vector<EmployeeInfo> Sort(const vector<EmployeeInfo>& info) = 0;
	virtual vector<EmployeeInfo> Sort_partial(const vector<EmployeeInfo>& info, const int max) = 0;
};