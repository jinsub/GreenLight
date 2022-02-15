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
	None
};
struct Parameter {
	// TODO
};

struct IDatabase {
	virtual vector<EmployeeInfo> createDB() = 0;
	virtual vector<EmployeeInfo> readDB(FilterOption opt, Parameter param) = 0;
	virtual vector<EmployeeInfo> updateDB(FilterOption opt, Parameter paramOld, Parameter paramNew) = 0;
	virtual vector<EmployeeInfo> deleteDB(FilterOption opt, Parameter param) = 0;
};