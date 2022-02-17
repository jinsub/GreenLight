#pragma once
#include <iostream>
#include <vector>

#include "Types.h"

using namespace std;

enum class Column {
	EmployeeNum = 0,
	Name,
	CareerLevel,
	PhoneNumber,
	Birthday,
	Certi,
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

struct TargetParam {
	Column column;
	string value;
};

struct IDatabase {
	virtual vector<EmployeeInfo> CreateDB(EmployeeInfo info) = 0;
	virtual vector<EmployeeInfo> ReadDB(TargetParam filter) = 0;
	virtual vector<EmployeeInfo> UpdateDB(TargetParam filter, TargetParam update) = 0;
	virtual vector<EmployeeInfo> DeleteDB(TargetParam filter) = 0;
};