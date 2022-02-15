#pragma once
#include <iostream>
#include <vector>

#include "Types.h"

using namespace std;

enum class FilterOption {
	FirstName,
	LastName,
	MiddlePhoneNum,
	LastPhoneNum,
	BirthdayYear,
	BirthdayMonth,
	BirthdayDay,
	None,
	Invalid
};
struct Parameter {
	// TODO
};

struct IDatabase {
	virtual vector<EmployeeInfo> CreateDB() = 0;
	virtual vector<EmployeeInfo> ReadDB(FilterOption opt, Parameter param) = 0;
	virtual vector<EmployeeInfo> UpdateDB(FilterOption opt, Parameter paramOld, Parameter paramNew) = 0;
	virtual vector<EmployeeInfo> DeleteDB(FilterOption opt, Parameter param) = 0;
};