#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;
enum class CareerLevel {
	CL1,
	CL2,
	CL3,
	CL4,
};
enum class CertLevel {
	ADV,
	PRO,
	EX,
};
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
struct EmployeeInfo {
	string toString() {

	};
	unsigned int num;
	string firstName;
	string lasttName;
	CareerLevel cl;
	string midPhoneNum;
	string lastPhoneNum;
	unsigned int birthYear;
	unsigned int birthMonth;
	unsigned int birthDay;
	CertLevel certi;
};

struct IDatabase {
	virtual vector<EmployeeInfo> createDB() = 0;
	virtual vector<EmployeeInfo> readDB(FilterOptionType opt, Parameter param) = 0;
	virtual vector<EmployeeInfo> updateDB(FilterOptionType opt, Parameter paramOld, Parameter paramNew) = 0;
	virtual vector<EmployeeInfo> deleteDB(FilterOptionType opt, Parameter param) = 0;
};