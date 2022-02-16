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

vector<unsigned int> MemoryDatabase::getEmployeeNums(multimap<string, unsigned int> map, string key) {
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
	case Column::EmployeeNum:
		result.push_back(map_.mainDB_[stoul(filter.value, nullptr, 0)]);
		break;
	case Column::Name:
		nums = getEmployeeNums(map_.fullName_Map_, filter.value);
		break;
	case Column::CareerLevel:
		nums = getEmployeeNums(map_.career_Map_, filter.value);
		break;
	case Column::PhoneNumber:
		nums = getEmployeeNums(map_.fullPhone_Map_, filter.value);
		break;
	case Column::Birthday:
		nums = getEmployeeNums(map_.birth_Map_, filter.value);
		break;
	case Column::Certi:
		nums = getEmployeeNums(map_.cert_Map_, filter.value);
		break;
	case Column::FirstName:
		nums =  getEmployeeNums(map_.firstName_Map_, filter.value);		
		break;
	case Column::LastName:
		nums = getEmployeeNums(map_.lastName_Map_, filter.value);
		break;
	case Column::MiddlePhoneNum:
		nums = getEmployeeNums(map_.midPhone_Map_, filter.value);
		break;
	case Column::LastPhoneNum:
		nums = getEmployeeNums(map_.lastPhone_Map_, filter.value);
		break;
	case Column::BirthdayYear:
		nums = getEmployeeNums(map_.birthYear_Map_, filter.value);
		break;
	case Column::BirthdayMonth:
		nums = getEmployeeNums(map_.birthMonth_Map_, filter.value);
		break;
	case Column::BirthdayDay:
		nums = getEmployeeNums(map_.birthDay_Map_, filter.value);
		break;
	default:
		break;
	}

	for (auto num : nums) {
		result.push_back(map_.mainDB_[num]);
	}
	return result;
}


vector<EmployeeInfo> MemoryDatabase::DeleteDB(TargetParam filter) {
	vector<EmployeeInfo> result;

	return result;
}
