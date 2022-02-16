#include "MemoryDatabase.h"
#include <vector>
#include <sstream>
#include <string>
using namespace std;

vector<unsigned int> MemoryDatabase::getEmployeeNums(multimap<string, unsigned int> map, string key) {
	vector<unsigned int> result;
	for (auto it = map.lower_bound(key); it != map.upper_bound(key); it++){
		result.push_back(it->second);
	}
	return result;
}

void MemoryDatabase::setEmployeeInfo(multimap<string, unsigned int> map, vector<unsigned int> nums, string oldParam, string newParam) {
	multimap<string, unsigned int>::iterator iter;
	int iCount;
	iCount = (int)map.count(oldParam);
	iter = map.find(oldParam);
	for (int i = 0; i < iCount; ++i) {
		for (auto num : nums) {
			if (iter->second == num){
				iter = map.erase(iter++);
				map.insert({ newParam,num });
				break;
			}
			iter++;
		}
	}
}

vector<string> MemoryDatabase::Split(string str, char delimiter) {
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

vector<EmployeeInfo> MemoryDatabase::getUpdateMainDB(map<unsigned int, EmployeeInfo> map_,
	multimap<string, unsigned int> firstName_Map_, 
	multimap<string, unsigned int> lastName_Map_,
	multimap<string, unsigned int> fullName_Map_,
	multimap<string, unsigned int> birthYear_Map_,
	multimap<string, unsigned int> birthMonth_Map_,
	multimap<string, unsigned int> birthDay_Map_,
	multimap<string, unsigned int> birth_Map_,
	multimap<string, unsigned int> midPhone_Map_,
	multimap<string, unsigned int> lastPhone_Map_,
	multimap<string, unsigned int> fullPhone_Map_, 
	multimap<string, unsigned int> career_Map_,
	multimap<string, unsigned int> cert_Map_, vector<unsigned int> nums, TargetParam filter, TargetParam update){

	vector<EmployeeInfo> result;
	vector<string> split_filter = Split(filter.value, ' ');
	vector<string> split_update = Split(update.value, ' ');

	switch (update.column) {
	case Column::Name:
		for (auto num : nums) {
			map_[num].firstName_ = split_update[0];
			map_[num].lastName_ = split_update[1];
		}
		setEmployeeInfo(firstName_Map_, nums, split_filter[0], split_update[0]);
		setEmployeeInfo(lastName_Map_, nums, split_filter[1], split_update[1]);
		setEmployeeInfo(fullName_Map_, nums, filter.value, update.value);
		break;
	case Column::Birthday:
		for (auto num : nums) {
			map_[num].birthYear_ = split_update[0];
			map_[num].birthMonth_ = split_update[1];
			map_[num].birthDay_ = split_update[2];
		}
		setEmployeeInfo(birthYear_Map_, nums, split_filter[0], split_update[0]);
		setEmployeeInfo(birthMonth_Map_, nums, split_filter[1], split_update[1]);
		setEmployeeInfo(birthDay_Map_, nums, split_filter[2], split_update[2]);
		setEmployeeInfo(birth_Map_, nums, filter.value, update.value);
		break;
	case Column::PhoneNumber:
		for (auto num : nums) {
			map_[num].firstName_ = split_update[0];
			map_[num].lastName_ = split_update[1];
		}
		setEmployeeInfo(midPhone_Map_, nums, split_filter[0], split_update[0]);
		setEmployeeInfo(lastPhone_Map_, nums, split_filter[1], split_update[1]);
		setEmployeeInfo(fullPhone_Map_, nums, filter.value, update.value);
		break;
	case Column::CareerLevel:
		for (auto num : nums) {
			map_[num].cl_ = update.value;
		}
		setEmployeeInfo(career_Map_, nums, filter.value, update.value);
		break;
	case Column::Certi:
		for (auto num : nums) {
			map_[num].certi_ = update.value;
		}
		setEmployeeInfo(cert_Map_, nums, filter.value, update.value);
		break;
	case Column::FirstName:
		for (auto num : nums) {
			map_[num].firstName_ = update.value;
		}
		setEmployeeInfo(firstName_Map_, nums, filter.value, update.value);
		fullName_Map_.clear();
		for (auto iter = map_.begin(); iter != map_.end(); iter++) {
			fullName_Map_.insert({ iter->second.GetFullName(), iter->second.num_});
		}
		break;
	case Column::LastName:
		for (auto num : nums) {
			map_[num].lastName_ = update.value;
		}
		setEmployeeInfo(lastName_Map_, nums, filter.value, update.value);
		fullName_Map_.clear();
		for (auto iter = map_.begin(); iter != map_.end(); iter++) {
			fullName_Map_.insert({ iter->second.GetFullName(), iter->second.num_ });
		}
		break;
	case Column::MiddlePhoneNum:
		for (auto num : nums) {
			map_[num].midPhoneNum_ = update.value;
		}
		setEmployeeInfo(midPhone_Map_, nums, filter.value, update.value);
		fullPhone_Map_.clear();
		for (auto iter = map_.begin(); iter != map_.end(); iter++) {
			fullPhone_Map_.insert({ iter->second.GetFullPhoneNum(), iter->second.num_ });
		}
		break;
	case Column::LastPhoneNum:
		for (auto num : nums) {
			map_[num].lastPhoneNum_ = update.value;
		}
		setEmployeeInfo(lastPhone_Map_, nums, filter.value, update.value);
		fullPhone_Map_.clear();
		for (auto iter = map_.begin(); iter != map_.end(); iter++) {
			fullPhone_Map_.insert({ iter->second.GetFullPhoneNum(), iter->second.num_ });
		}
		break;
	case Column::BirthdayYear:
		for (auto num : nums) {
			map_[num].birthYear_ = update.value;
		}
		setEmployeeInfo(birthYear_Map_, nums, filter.value, update.value);
		birth_Map_.clear();
		for (auto iter = map_.begin(); iter != map_.end(); iter++) {
			birth_Map_.insert({ iter->second.GetFullBirthday(), iter->second.num_ });
		}
		break;
	case Column::BirthdayMonth:
		for (auto num : nums) {
			map_[num].birthMonth_ = update.value;
		}
		setEmployeeInfo(birthMonth_Map_, nums, filter.value, update.value);
		birth_Map_.clear();
		for (auto iter = map_.begin(); iter != map_.end(); iter++) {
			birth_Map_.insert({ iter->second.GetFullBirthday(), iter->second.num_ });
		}
		break;
	case Column::BirthdayDay:
		for (auto num : nums) {
			map_[num].birthDay_ = update.value;
		}
		setEmployeeInfo(birthDay_Map_, nums, filter.value, update.value);
		birth_Map_.clear();
		for (auto iter = map_.begin(); iter != map_.end(); iter++) {
			birth_Map_.insert({ iter->second.GetFullBirthday(), iter->second.num_ });
		}
		break;
	default:
		break;
	}
	for (auto num : nums) {
		result.push_back(map_[num]);
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
		nums = getEmployeeNums(map_.fullName_Map_, filter.value);
		result = getUpdateMainDB(map_.mainDB_, map_.
			firstName_Map_, map_.lastName_Map_, map_.firstName_Map_,
			map_.birthYear_Map_, map_.birthMonth_Map_, map_.birthDay_Map_, map_.birth_Map_,
			map_.midPhone_Map_, map_.lastPhone_Map_, map_.fullPhone_Map_,
			map_.career_Map_, map_.cert_Map_, nums, filter, update);
		break;
	case Column::CareerLevel:
		nums = getEmployeeNums(map_.career_Map_, filter.value);
		result = getUpdateMainDB(map_.mainDB_, map_.
			firstName_Map_, map_.lastName_Map_, map_.firstName_Map_,
			map_.birthYear_Map_, map_.birthMonth_Map_, map_.birthDay_Map_, map_.birth_Map_,
			map_.midPhone_Map_, map_.lastPhone_Map_, map_.fullPhone_Map_,
			map_.career_Map_, map_.cert_Map_, nums, filter, update);
		break;
	case Column::PhoneNumber:
		nums = getEmployeeNums(map_.fullPhone_Map_, filter.value);
		result = getUpdateMainDB(map_.mainDB_, map_.
			firstName_Map_, map_.lastName_Map_, map_.firstName_Map_,
			map_.birthYear_Map_, map_.birthMonth_Map_, map_.birthDay_Map_, map_.birth_Map_,
			map_.midPhone_Map_, map_.lastPhone_Map_, map_.fullPhone_Map_,
			map_.career_Map_, map_.cert_Map_, nums, filter, update);
		break;
	case Column::Birthday:
		nums = getEmployeeNums(map_.birth_Map_, filter.value);
		result = getUpdateMainDB(map_.mainDB_, map_.
			firstName_Map_, map_.lastName_Map_, map_.firstName_Map_,
			map_.birthYear_Map_, map_.birthMonth_Map_, map_.birthDay_Map_, map_.birth_Map_,
			map_.midPhone_Map_, map_.lastPhone_Map_, map_.fullPhone_Map_,
			map_.career_Map_, map_.cert_Map_, nums, filter, update);
		break;
	case Column::Certi:
		nums = getEmployeeNums(map_.cert_Map_, filter.value);
		result = getUpdateMainDB(map_.mainDB_, map_.
			firstName_Map_, map_.lastName_Map_, map_.firstName_Map_,
			map_.birthYear_Map_, map_.birthMonth_Map_, map_.birthDay_Map_, map_.birth_Map_,
			map_.midPhone_Map_, map_.lastPhone_Map_, map_.fullPhone_Map_,
			map_.career_Map_, map_.cert_Map_, nums, filter, update);
		break;
	case Column::FirstName:
		nums = getEmployeeNums(map_.firstName_Map_, filter.value);
		result = getUpdateMainDB(map_.mainDB_, map_.
			firstName_Map_, map_.lastName_Map_, map_.firstName_Map_,
			map_.birthYear_Map_, map_.birthMonth_Map_, map_.birthDay_Map_, map_.birth_Map_,
			map_.midPhone_Map_, map_.lastPhone_Map_, map_.fullPhone_Map_,
			map_.career_Map_, map_.cert_Map_, nums, filter, update);
		break;
	case Column::LastName:
		nums = getEmployeeNums(map_.lastName_Map_, filter.value);
		result = getUpdateMainDB(map_.mainDB_, map_.
			firstName_Map_, map_.lastName_Map_, map_.firstName_Map_,
			map_.birthYear_Map_, map_.birthMonth_Map_, map_.birthDay_Map_, map_.birth_Map_,
			map_.midPhone_Map_, map_.lastPhone_Map_, map_.fullPhone_Map_,
			map_.career_Map_, map_.cert_Map_, nums, filter, update);
		break;
	case Column::MiddlePhoneNum:
		nums = getEmployeeNums(map_.midPhone_Map_, filter.value);
		result = getUpdateMainDB(map_.mainDB_, map_.
			firstName_Map_, map_.lastName_Map_, map_.firstName_Map_,
			map_.birthYear_Map_, map_.birthMonth_Map_, map_.birthDay_Map_, map_.birth_Map_,
			map_.midPhone_Map_, map_.lastPhone_Map_, map_.fullPhone_Map_,
			map_.career_Map_, map_.cert_Map_, nums, filter, update);
		break;
	case Column::LastPhoneNum:
		nums = getEmployeeNums(map_.lastPhone_Map_, filter.value);
		result = getUpdateMainDB(map_.mainDB_, map_.
			firstName_Map_, map_.lastName_Map_, map_.firstName_Map_,
			map_.birthYear_Map_, map_.birthMonth_Map_, map_.birthDay_Map_, map_.birth_Map_,
			map_.midPhone_Map_, map_.lastPhone_Map_, map_.fullPhone_Map_,
			map_.career_Map_, map_.cert_Map_, nums, filter, update);
		break;
	case Column::BirthdayYear:
		nums = getEmployeeNums(map_.birthYear_Map_, filter.value);
		result = getUpdateMainDB(map_.mainDB_, map_.
			firstName_Map_, map_.lastName_Map_, map_.firstName_Map_,
			map_.birthYear_Map_, map_.birthMonth_Map_, map_.birthDay_Map_, map_.birth_Map_,
			map_.midPhone_Map_, map_.lastPhone_Map_, map_.fullPhone_Map_,
			map_.career_Map_, map_.cert_Map_, nums, filter, update);
		break;
	case Column::BirthdayMonth:
		nums = getEmployeeNums(map_.birthMonth_Map_, filter.value);
		result = getUpdateMainDB(map_.mainDB_, map_.
			firstName_Map_, map_.lastName_Map_, map_.firstName_Map_,
			map_.birthYear_Map_, map_.birthMonth_Map_, map_.birthDay_Map_, map_.birth_Map_,
			map_.midPhone_Map_, map_.lastPhone_Map_, map_.fullPhone_Map_,
			map_.career_Map_, map_.cert_Map_, nums, filter, update);
		break;
	case Column::BirthdayDay:
		nums = getEmployeeNums(map_.birthDay_Map_, filter.value);
		result = getUpdateMainDB(map_.mainDB_, map_.
			firstName_Map_, map_.lastName_Map_, map_.firstName_Map_,
			map_.birthYear_Map_, map_.birthMonth_Map_, map_.birthDay_Map_, map_.birth_Map_,
			map_.midPhone_Map_, map_.lastPhone_Map_, map_.fullPhone_Map_,
			map_.career_Map_, map_.cert_Map_, nums, filter, update);
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
