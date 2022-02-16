#include "MemoryDatabase.h"
#include <vector>
#include <sstream>
#include <string>
using namespace std;

vector<unsigned int> MemoryDatabase::getEmployeeNums(multimap<string, unsigned int> map, string key) {
	vector<unsigned int> result;
	for (auto it = map.lower_bound(key); it != map.upper_bound(key); it++)
	{
		result.push_back(it->second);
	}
	return result;
}

vector<EmployeeInfo> MemoryDatabase::CreateDB(EmployeeInfo info) {
	vector<EmployeeInfo> result;

	map_.mainDB_.insert({ info.num_, info });
	map_.fullName_Map_.insert({ info.GetFullName(), info.num_ });
	map_.firstName_Map_.insert({ info.firstName_, info.num_ });
	map_.lastName_Map_.insert({ info.lastName_, info.num_ });
	map_.fullPhone_Map_.insert({ info.GetFullPhoneNum(), info.num_ });
	map_.midPhone_Map_.insert({ info.midPhoneNum_, info.num_ });
	map_.lastPhone_Map_.insert({ info.lastPhoneNum_, info.num_ });
	map_.birth_Map_.insert({ info.GetFullBirthday(), info.num_ });
	map_.birthYear_Map_.insert({ info.birthYear_, info.num_ });
	map_.birthMonth_Map_.insert({ info.birthMonth_, info.num_ });
	map_.birthDay_Map_.insert({ info.birthDay_, info.num_ });
	map_.career_Map_.insert({ info.cl_, info.num_ });
	map_.cert_Map_.insert({ info.certi_, info.num_ });

	return result;
}


vector<string> Split(string str, char delimiter) {
	vector<string> answer;
	stringstream ss(str);
	string buffer;
	while (getline(ss, buffer, delimiter)) {
		answer.push_back(buffer);
	}
	return answer;
}

vector<EmployeeInfo> MemoryDatabase::UpdateDB(TargetParam filter, TargetParam update) {
	vector<EmployeeInfo> result;

	vector<unsigned int> nums;
	multimap<string, unsigned int>::iterator iter;
	int iCount;
	vector<string> split_filter = Split(filter.value, ' ');
	vector<string> split_update = Split(update.value, ' ');

	switch (filter.column) {

	case Column::EmployeeNum:
		break;
	case Column::Name:
		nums = getEmployeeNums(map_.fullName_Map_, filter.value);
		switch (update.column) {
		case Column::Name:
			for (auto num : nums) {
				map_.mainDB_[num].firstName_ = split_update[0];
				map_.mainDB_[num].lastName_ = split_update[1];
			}

			iCount = (int)map_.firstName_Map_.count(split_filter[0]);
			iter = map_.firstName_Map_.find(split_filter[0]);
			for (int i = 0; i < iCount; ++i) {
				for (auto num : nums) {
					if (iter->second == num)
					{
						iter = map_.firstName_Map_.erase(iter++);
						map_.firstName_Map_.insert({ split_update[0],num });
						break;
					}
					iter++;
				}
			}

			iCount = (int)map_.lastName_Map_.count(split_filter[1]);
			iter = map_.lastName_Map_.find(split_filter[1]);
			for (int i = 0; i < iCount; i++) {
				for (auto num : nums) {
					if (iter->second == num)
					{
						map_.lastName_Map_.erase(iter++);
						map_.lastName_Map_.insert({ split_update[1],num });
						break;
					}
					iter++;
				}
			}

			iCount = (int)map_.fullName_Map_.count(filter.value);
			iter = map_.fullName_Map_.find(filter.value);
			for (int i = 0; i < iCount; i++) {
				for (auto num : nums) {
					if (iter->second == num)
					{
						map_.fullName_Map_.erase(iter++);
						map_.fullName_Map_.insert({ update.value,num });
						break;
					}
					iter++;
				}
			}

			break;
		case Column::Birthday:
			break;
		case Column::PhoneNumber:
			break;
		case Column::CareerLevel:
			break;
		case Column::Certi:
			break;
		}
		for (auto num : nums) {
			result.push_back(map_.mainDB_[num]);
		}
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
