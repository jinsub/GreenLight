#pragma once
#include <string>
using namespace std;

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
