#pragma once
#include "ISorter.h"
#include <queue>

class AscendingEmployeeNumber : public ISorter
{
public:
	vector<EmployeeInfo> Sort(const vector<EmployeeInfo>& info) override;
	vector<EmployeeInfo> Sort_partial(const vector<EmployeeInfo>& info, const int max) override;
};