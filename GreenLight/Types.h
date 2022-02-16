#pragma once
#include <string>
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

struct EmployeeInfo {
	unsigned int num;
	string fullName;
	string firstName;
	string lastName;
	CareerLevel cl;
	string fullPhoneNum;
	string midPhoneNum;
	string lastPhoneNum;
	unsigned int birth;
	unsigned int birthYear;
	unsigned int birthMonth;
	unsigned int birthDay;
	CertLevel certi;
};