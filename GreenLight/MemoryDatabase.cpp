#include "MemoryDatabase.h"
#include <vector>
#include <string>
using namespace std;

vector<unsigned int> MemoryDatabase::GetEmployeeNums_(const multimap<string, unsigned int>& map, const string key) {
	vector<unsigned int> result;
	for (auto it = map.lower_bound(key); it != map.upper_bound(key); it++) {
		result.push_back(it->second);
	}
	return result;
}

void MemoryDatabase::SetEmployeeInfo_(multimap<string, unsigned int>& map, const vector<unsigned int> nums, string oldParam, string newParam) {
	multimap<string, unsigned int>::iterator iter;
	int iCount;
	iCount = (int)map.count(oldParam);
	iter = map.find(oldParam);
	for (int i = 0; i < iCount; ++i) {
		for (auto num : nums) {
			if (iter->second == num) {
				iter = map.erase(iter++);
				map.insert({ newParam,num });
				break;
			}
			iter++;
		}
	}
}

vector<string> MemoryDatabase::Split_(string str, char delimiter) {
	vector<string> answer;
	stringstream ss(str);
	string buffer;
	while (getline(ss, buffer, delimiter)) {
		answer.push_back(buffer);
	}
	return answer;
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

	result.push_back(info);

	return result;
}

vector<EmployeeInfo> MemoryDatabase::GetUpdateMainDB_(DataBaseMap& map, const vector<unsigned int> nums, TargetParam filter, TargetParam update) {

	vector<EmployeeInfo> result;
	vector<string> split_filter = Split_(filter.value, ' ');
	vector<string> split_update = Split_(update.value, ' ');

	switch (update.column) {
	case Column::Name:
		for (auto num : nums) {
			map.mainDB_[num].firstName_ = split_update[0];
			map.mainDB_[num].lastName_ = split_update[1];
		}
		SetEmployeeInfo_(map.firstName_Map_, nums, split_filter[0], split_update[0]);
		SetEmployeeInfo_(map.lastName_Map_, nums, split_filter[1], split_update[1]);
		SetEmployeeInfo_(map.fullName_Map_, nums, filter.value, update.value);
		break;
	case Column::Birthday:
		for (auto num : nums) {
			map.mainDB_[num].birthYear_ = split_update[0];
			map.mainDB_[num].birthMonth_ = split_update[1];
			map.mainDB_[num].birthDay_ = split_update[2];
		}
		SetEmployeeInfo_(map.birthYear_Map_, nums, split_filter[0], split_update[0]);
		SetEmployeeInfo_(map.birthMonth_Map_, nums, split_filter[1], split_update[1]);
		SetEmployeeInfo_(map.birthDay_Map_, nums, split_filter[2], split_update[2]);
		SetEmployeeInfo_(map.birth_Map_, nums, filter.value, update.value);
		break;
	case Column::PhoneNumber:
		for (auto num : nums) {
			map.mainDB_[num].firstName_ = split_update[0];
			map.mainDB_[num].lastName_ = split_update[1];
		}
		SetEmployeeInfo_(map.midPhone_Map_, nums, split_filter[0], split_update[0]);
		SetEmployeeInfo_(map.lastPhone_Map_, nums, split_filter[1], split_update[1]);
		SetEmployeeInfo_(map.fullPhone_Map_, nums, filter.value, update.value);
		break;
	case Column::CareerLevel:
		for (auto num : nums) {
			map.mainDB_[num].cl_ = update.value;
		}
		SetEmployeeInfo_(map.career_Map_, nums, filter.value, update.value);
		break;
	case Column::Certi:
		for (auto num : nums) {
			map.mainDB_[num].certi_ = update.value;
		}
		SetEmployeeInfo_(map.cert_Map_, nums, filter.value, update.value);
		break;
	case Column::FirstName:
		for (auto num : nums) {
			map.mainDB_[num].firstName_ = update.value;
		}
		SetEmployeeInfo_(map.firstName_Map_, nums, filter.value, update.value);
		map.fullName_Map_.clear();
		for (auto iter = map.mainDB_.begin(); iter != map.mainDB_.end(); iter++) {
			map.fullName_Map_.insert({ iter->second.GetFullName(), iter->second.num_ });
		}
		break;
	case Column::LastName:
		for (auto num : nums) {
			map.mainDB_[num].lastName_ = update.value;
		}
		SetEmployeeInfo_(map.lastName_Map_, nums, filter.value, update.value);
		map.fullName_Map_.clear();
		for (auto iter = map.mainDB_.begin(); iter != map.mainDB_.end(); iter++) {
			map.fullName_Map_.insert({ iter->second.GetFullName(), iter->second.num_ });
		}
		break;
	case Column::MiddlePhoneNum:
		for (auto num : nums) {
			map.mainDB_[num].midPhoneNum_ = update.value;
		}
		SetEmployeeInfo_(map.midPhone_Map_, nums, filter.value, update.value);
		map.fullPhone_Map_.clear();
		for (auto iter = map.mainDB_.begin(); iter != map.mainDB_.end(); iter++) {
			map.fullPhone_Map_.insert({ iter->second.GetFullPhoneNum(), iter->second.num_ });
		}
		break;
	case Column::LastPhoneNum:
		for (auto num : nums) {
			map.mainDB_[num].lastPhoneNum_ = update.value;
		}
		SetEmployeeInfo_(map.lastPhone_Map_, nums, filter.value, update.value);
		map.fullPhone_Map_.clear();
		for (auto iter = map.mainDB_.begin(); iter != map.mainDB_.end(); iter++) {
			map.fullPhone_Map_.insert({ iter->second.GetFullPhoneNum(), iter->second.num_ });
		}
		break;
	case Column::BirthdayYear:
		for (auto num : nums) {
			map.mainDB_[num].birthYear_ = update.value;
		}
		SetEmployeeInfo_(map.birthYear_Map_, nums, filter.value, update.value);
		map.birth_Map_.clear();
		for (auto iter = map.mainDB_.begin(); iter != map.mainDB_.end(); iter++) {
			map.birth_Map_.insert({ iter->second.GetFullBirthday(), iter->second.num_ });
		}
		break;
	case Column::BirthdayMonth:
		for (auto num : nums) {
			map.mainDB_[num].birthMonth_ = update.value;
		}
		SetEmployeeInfo_(map.birthMonth_Map_, nums, filter.value, update.value);
		map.birth_Map_.clear();
		for (auto iter = map.mainDB_.begin(); iter != map.mainDB_.end(); iter++) {
			map.birth_Map_.insert({ iter->second.GetFullBirthday(), iter->second.num_ });
		}
		break;
	case Column::BirthdayDay:
		for (auto num : nums) {
			map.mainDB_[num].birthDay_ = update.value;
		}
		SetEmployeeInfo_(map.birthDay_Map_, nums, filter.value, update.value);
		map.birth_Map_.clear();
		for (auto iter = map.mainDB_.begin(); iter != map.mainDB_.end(); iter++) {
			map.birth_Map_.insert({ iter->second.GetFullBirthday(), iter->second.num_ });
		}
		break;
	default:
		break;
	}
	for (auto num : nums) {
		result.push_back(map.mainDB_[num]);
	}

	return result;
}

vector<EmployeeInfo> MemoryDatabase::UpdateDB(TargetParam filter, TargetParam update) {
	vector<EmployeeInfo> result;
	vector<unsigned int> nums;


	switch (filter.column) {
	case Column::EmployeeNum:
		break;
	case Column::Name:
		nums = GetEmployeeNums_(map_.fullName_Map_, filter.value);
		result = GetUpdateMainDB_(map_, nums, filter, update);
		break;
	case Column::CareerLevel:
		nums = GetEmployeeNums_(map_.career_Map_, filter.value);
		result = GetUpdateMainDB_(map_, nums, filter, update);
		break;
	case Column::PhoneNumber:
		nums = GetEmployeeNums_(map_.fullPhone_Map_, filter.value);
		result = GetUpdateMainDB_(map_, nums, filter, update);
		break;
	case Column::Birthday:
		nums = GetEmployeeNums_(map_.birth_Map_, filter.value);
		result = GetUpdateMainDB_(map_, nums, filter, update);
		break;
	case Column::Certi:
		nums = GetEmployeeNums_(map_.cert_Map_, filter.value);
		result = GetUpdateMainDB_(map_, nums, filter, update);
		break;
	case Column::FirstName:
		nums = GetEmployeeNums_(map_.firstName_Map_, filter.value);
		result = GetUpdateMainDB_(map_, nums, filter, update);
		break;
	case Column::LastName:
		nums = GetEmployeeNums_(map_.lastName_Map_, filter.value);
		result = GetUpdateMainDB_(map_, nums, filter, update);
		break;
	case Column::MiddlePhoneNum:
		nums = GetEmployeeNums_(map_.midPhone_Map_, filter.value);
		result = GetUpdateMainDB_(map_, nums, filter, update);
		break;
	case Column::LastPhoneNum:
		nums = GetEmployeeNums_(map_.lastPhone_Map_, filter.value);
		result = GetUpdateMainDB_(map_, nums, filter, update);
		break;
	case Column::BirthdayYear:
		nums = GetEmployeeNums_(map_.birthYear_Map_, filter.value);
		result = GetUpdateMainDB_(map_, nums, filter, update);
		break;
	case Column::BirthdayMonth:
		nums = GetEmployeeNums_(map_.birthMonth_Map_, filter.value);
		result = GetUpdateMainDB_(map_, nums, filter, update);
		break;
	case Column::BirthdayDay:
		nums = GetEmployeeNums_(map_.birthDay_Map_, filter.value);
		result = GetUpdateMainDB_(map_, nums, filter, update);
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
