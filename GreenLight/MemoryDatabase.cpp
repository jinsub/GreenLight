#include "MemoryDatabase.h"
#include <vector>
#include <string>
using namespace std;

vector<EmployeeInfo> MemoryDatabase::CreateDB(EmployeeInfo info) {
	vector<EmployeeInfo> result;

	return result;
}

vector<EmployeeInfo> MemoryDatabase::UpdateDB(TargetParam filter, TargetParam update) {
	vector<EmployeeInfo> result;

	return result;
}

vector<unsigned int> MemoryDatabase::GetEmployeeNums_(const multimap<string, unsigned int>& map, const string key) {
	vector<unsigned int> result;
	for (auto it = map.lower_bound(key); it != map.upper_bound(key); it++)
	{
		result.push_back(it->second);
	}
	return result;
}

vector<EmployeeInfo> MemoryDatabase::ReadDB(TargetParam filter) {
	vector<EmployeeInfo> result;
	vector<unsigned int> nums;

	switch (filter.column) {
	case Column::EmployeeNum: {
		map<unsigned int, EmployeeInfo>::iterator employee = map_.mainDB_.find(stoul(filter.value, nullptr, 0));
		if (employee != map_.mainDB_.end()) {
			result.push_back(employee->second);
		}
		break;
	}
	case Column::Name:
		nums = GetEmployeeNums_(map_.fullName_Map_, filter.value);
		break;
	case Column::CareerLevel:
		nums = GetEmployeeNums_(map_.career_Map_, filter.value);
		break;
	case Column::PhoneNumber:
		nums = GetEmployeeNums_(map_.fullPhone_Map_, filter.value);
		break;
	case Column::Birthday:
		nums = GetEmployeeNums_(map_.birth_Map_, filter.value);
		break;
	case Column::Certi:
		nums = GetEmployeeNums_(map_.cert_Map_, filter.value);
		break;
	case Column::FirstName:
		nums =  GetEmployeeNums_(map_.firstName_Map_, filter.value);		
		break;
	case Column::LastName:
		nums = GetEmployeeNums_(map_.lastName_Map_, filter.value);
		break;
	case Column::MiddlePhoneNum:
		nums = GetEmployeeNums_(map_.midPhone_Map_, filter.value);
		break;
	case Column::LastPhoneNum:
		nums = GetEmployeeNums_(map_.lastPhone_Map_, filter.value);
		break;
	case Column::BirthdayYear:
		nums = GetEmployeeNums_(map_.birthYear_Map_, filter.value);
		break;
	case Column::BirthdayMonth:
		nums = GetEmployeeNums_(map_.birthMonth_Map_, filter.value);
		break;
	case Column::BirthdayDay:
		nums = GetEmployeeNums_(map_.birthDay_Map_, filter.value);
		break;
	default:
		break;
	}

	for (auto num : nums) {
		result.push_back(map_.mainDB_[num]);
	}
	return result;
}

void MemoryDatabase::EraseEmployee_(multimap<string, unsigned int>& map, const string key) {
	for (auto itr = map.lower_bound(key); itr != map.upper_bound(key);) {
		map.erase(itr++);
	}
}
vector<EmployeeInfo> MemoryDatabase::DeleteDB(TargetParam filter) {
	vector<EmployeeInfo> target = ReadDB(filter);
	if (target.size() == 0) {
		return target;
	}

	for (auto person : target) {
		map_.mainDB_.erase(person.num_);		

		EraseEmployee_(map_.fullName_Map_, person.GetFullName());
		EraseEmployee_(map_.firstName_Map_, person.firstName_);
		EraseEmployee_(map_.lastName_Map_, person.lastName_);

		EraseEmployee_(map_.birth_Map_, person.GetFullBirthday());
		EraseEmployee_(map_.birthYear_Map_, person.birthYear_);
		EraseEmployee_(map_.birthMonth_Map_, person.birthMonth_);
		EraseEmployee_(map_.birthDay_Map_, person.birthDay_);

		EraseEmployee_(map_.fullPhone_Map_, person.GetFullPhoneNum());
		EraseEmployee_(map_.midPhone_Map_, person.midPhoneNum_);
		EraseEmployee_(map_.lastPhone_Map_, person.lastPhoneNum_);

		EraseEmployee_(map_.cert_Map_, person.certi_);
		EraseEmployee_(map_.career_Map_, person.cl_);
	}
	return target;
}
