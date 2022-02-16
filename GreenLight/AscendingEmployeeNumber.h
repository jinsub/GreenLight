#pragma once
#include "ISorter.h"
#include <queue>

class AscendingEmployeeNumber : public ISorter
{
public:
	vector<EmployeeInfo> Sort(const vector<EmployeeInfo>& info) override;
};