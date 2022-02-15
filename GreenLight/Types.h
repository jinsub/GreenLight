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