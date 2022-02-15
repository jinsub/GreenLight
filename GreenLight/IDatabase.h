#pragma once
#include <iostream>
#include <vector>

#include "Types.h"

using namespace std;

enum class FilterOptionType {
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
	virtual vector<EmployeeInfo> CreateDB() = 0;
	virtual vector<EmployeeInfo> ReadDB(FilterOptionType opt, Parameter param) = 0;
	virtual vector<EmployeeInfo> UpdateDB(FilterOptionType opt, Parameter paramOld, Parameter paramNew) = 0;
	virtual vector<EmployeeInfo> DeleteDB(FilterOptionType opt, Parameter param) = 0;
};