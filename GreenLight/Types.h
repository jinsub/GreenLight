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
	unsigned int num_;
	string fullName_;
	string firstName_;
	string lastName_;
	CareerLevel cl_;
	string fullPhoneNum_;
	string midPhoneNum_;
	string lastPhoneNum_;
	unsigned int birth_;
	unsigned int birthYear_;
	unsigned int birthMonth_;
	unsigned int birthDay_;
	CertLevel certi_;

	bool operator==(const EmployeeInfo& a) const
	{
		if (this->num_ == a.num_)
			return true;
		return false;
	}
};

enum class PrintOption
{
	PrintLines,
	PrintCount,
	Invalid
};