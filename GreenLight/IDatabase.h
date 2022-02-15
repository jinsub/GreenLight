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

};

struct IDatabase {
	virtual vector<EmployeeInfo> createDB() = 0;
	virtual vector<EmployeeInfo> readDB(FilterOptionType opt, Parameter param) = 0;
	virtual vector<EmployeeInfo> updateDB(FilterOptionType opt, Parameter paramOld, Parameter paramNew) = 0;
	virtual vector<EmployeeInfo> deleteDB(FilterOptionType opt, Parameter param) = 0;
};