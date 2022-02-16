#include "MemoryDatabase.h"
#include <vector>
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
		break;
	case Column::Name:
		break;
	case Column::CareerLevel:
		break;
	case Column::PhoneNumber:
		break;
	case Column::Birthday:
		break;
	case Column::Certi:
		break;
	case Column::FirstName:
		nums =  getEmployeeNums(map_.firstName_Map_, filter.value);
		for (auto num : nums) {
			result.push_back(map_.mainDB_[num]);
		}
		break;
	case Column::LastName:
		break;
	case Column::MiddlePhoneNum:
		break;
	case Column::LastPhoneNum:
		break;
	case Column::BirthdayYear:
		break;
	case Column::BirthdayMonth:
		break;
	case Column::BirthdayDay:
		break;
	default:
		break;
	}
	return result;
}


vector<EmployeeInfo> MemoryDatabase::DeleteDB(TargetParam filter) {
	vector<EmployeeInfo> result;

	return result;
}
