#pragma once
#include <string>
using namespace std;

#define MAX_PRINT_CNT (5)

enum class CommandType {
	Start = 0,

	ADD = Start,
	DEL,
	SCH,
	MOD,

	End,
	Count = End - Start,
	INVALID
};

struct EmployeeInfo {
	unsigned int num_;
	string firstName_;
	string lastName_;
	string cl_;
	string midPhoneNum_;
	string lastPhoneNum_;
	string birthYear_;
	string birthMonth_;
	string birthDay_;
	string certi_;

	bool operator==(const EmployeeInfo& a) const
	{
		if (this->num_ == a.num_)
			return true;
		return false;
	}

	bool operator<(const EmployeeInfo& a) const
	{
		return this->num_ > a.num_;
	}

	bool operator>(const EmployeeInfo& a) const
	{
		return this->num_ < a.num_;
	}

	string GetFullName(void) const {
		return firstName_ + " " + lastName_;
	}
	string GetFullPhoneNum(void) const {
		return "010-" + midPhoneNum_ + "-" + lastPhoneNum_;
	}
	string GetFullBirthday(void) const {
		return birthYear_ + birthMonth_ + birthDay_;
	}
};
