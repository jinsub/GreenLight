#include "MemoryDatabase.h"
#include "StrSplitter.h"
#include <vector>
#include <string>
using namespace std;

vector<unsigned int> MemoryDatabase::GetEmployeeNums_(const Column column, const string key) {
	vector<unsigned int> result;
	if (column >= Column::None) {
		return result;
	}

	if (column == Column::EmployeeNum) {
		auto it = map_.mainDB_.find(stoul(key, nullptr, 0));
		if (it != map_.mainDB_.end()) {
			result.push_back(it->first);			
		}
		return result;
	}

	multimap<string, unsigned int>* map = nullptr;
	switch (column) {
	case Column::Name:
		map = &map_.fullName_Map_;
		break;
	case Column::FirstName:
		map = &map_.firstName_Map_;
		break;
	case Column::LastName:
		map = &map_.lastName_Map_;
		break;
	case Column::PhoneNumber:
		map = &map_.fullPhone_Map_;
		break;
	case Column::MiddlePhoneNum:
		map = &map_.midPhone_Map_;
		break;
	case Column::LastPhoneNum:
		map = &map_.lastPhone_Map_;
		break;
	case Column::Birthday:
		map = &map_.birth_Map_;
		break;
	case Column::BirthdayYear:
		map = &map_.birthYear_Map_;
		break;
	case Column::BirthdayMonth:
		map = &map_.birthMonth_Map_;
		break;
	case Column::BirthdayDay:
		map = &map_.birthDay_Map_;
		break;
	case Column::CareerLevel:
		map = &map_.career_Map_;
		break;
	case Column::Certi:
		map = &map_.cert_Map_;
		break;
	}

	if (map == nullptr) {
		return result;
	}
		
	for (auto it = map->lower_bound(key); it != map->upper_bound(key); it++) {
		result.push_back(it->second);
	}
	return result;
}

void MemoryDatabase::SetEmployeeInfo_(multimap<string, unsigned int>& map, unsigned int num, string oldParam, string newParam) {
	multimap<string, unsigned int>::iterator iter;
	int iCount;
	iCount = (int)map.count(oldParam);
	iter = map.find(oldParam);
	for (int i = 0; i < iCount; ++i) {
		if (iter->second == num) {
			iter = map.erase(iter++);
			map.insert({ newParam,num });
			break;
		}
		iter++;
	}
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

vector<EmployeeInfo> MemoryDatabase::GetUpdateMainDB_(const vector<unsigned int> nums, TargetParam update) {

	vector<EmployeeInfo> result;
	vector<string> split_update;

	string update_year;
	string update_month;
	string update_day;

	EmployeeInfo info;

	for (auto num : nums) {
		if (map_.mainDB_.count(num) == 1) {
			result.push_back(map_.mainDB_[num]);
		}
	}

	switch (update.column) {
	case Column::EmployeeNum:
		for (auto num : nums) {
			if (map_.mainDB_.count(num) == 1) {
				map_.mainDB_[num].num_ = stoi(update.value);

        info = map_.mainDB_[num];

        map_.mainDB_.insert({ stoi(update.value), info });
				map_.mainDB_.erase(num);
			}
		}
		break;
	case Column::Name:
		split_update = StrSplitter::Split(update.value, ' ');
		for (auto num : nums) {
			if (map_.mainDB_.count(num) == 1) {
				map_.mainDB_[num].firstName_ = split_update[0];
				map_.mainDB_[num].lastName_ = split_update[1];
			}
		}
		map_.firstName_Map_.clear();
		map_.lastName_Map_.clear();
		map_.fullName_Map_.clear();
		for (auto iter = map_.mainDB_.begin(); iter != map_.mainDB_.end(); iter++) {
			map_.firstName_Map_.insert({ iter->second.firstName_,iter->second.num_ });
			map_.lastName_Map_.insert({ iter->second.lastName_,iter->second.num_ });
			map_.fullName_Map_.insert({ iter->second.GetFullName(), iter->second.num_ });
		}
		break;
	case Column::Birthday:
		update_year = update.value.substr(0, 4);
		update_month = update.value.substr(4, 2);
		update_day = update.value.substr(6, 2);
		for (auto num : nums) {
			if (map_.mainDB_.count(num) == 1) {
				map_.mainDB_[num].birthYear_ = update_year;
				map_.mainDB_[num].birthMonth_ = update_month;
				map_.mainDB_[num].birthDay_ = update_day;
			}
		}
		map_.birthYear_Map_.clear();
		map_.birthMonth_Map_.clear();
		map_.birthDay_Map_.clear();
		map_.birth_Map_.clear();
		for (auto iter = map_.mainDB_.begin(); iter != map_.mainDB_.end(); iter++) {
			map_.birthYear_Map_.insert({ iter->second.birthYear_,iter->second.num_ });
			map_.birthMonth_Map_.insert({ iter->second.birthMonth_,iter->second.num_ });
			map_.birthDay_Map_.insert({ iter->second.birthDay_, iter->second.num_ });
			map_.birth_Map_.insert({ iter->second.GetFullBirthday(), iter->second.num_ });
		}
		break;
	case Column::PhoneNumber:
		split_update = StrSplitter::Split(update.value, '-');
		for (auto num : nums) {
			if (map_.mainDB_.count(num) == 1) {
				map_.mainDB_[num].midPhoneNum_ = split_update[1];
				map_.mainDB_[num].lastPhoneNum_ = split_update[2];
			}
		}
		map_.midPhone_Map_.clear();
		map_.lastPhone_Map_.clear();
		map_.fullPhone_Map_.clear();
		for (auto iter = map_.mainDB_.begin(); iter != map_.mainDB_.end(); iter++) {
			map_.midPhone_Map_.insert({ iter->second.midPhoneNum_,iter->second.num_ });
			map_.lastPhone_Map_.insert({ iter->second.lastPhoneNum_,iter->second.num_ });
			map_.fullPhone_Map_.insert({ iter->second.GetFullPhoneNum(), iter->second.num_});
		}
		break;
	case Column::CareerLevel:
		for (auto num : nums) {
			if (map_.mainDB_.count(num) == 1) {
				map_.mainDB_[num].cl_ = update.value;
			}
		}
		map_.career_Map_.clear();
		for (auto iter = map_.mainDB_.begin(); iter != map_.mainDB_.end(); iter++) {
			map_.career_Map_.insert({ iter->second.cl_,iter->second.num_ });
		}
		break;
	case Column::Certi:
		for (auto num : nums) {
			if (map_.mainDB_.count(num) == 1) {
				map_.mainDB_[num].certi_ = update.value;
			}
		}
		map_.cert_Map_.clear();
		for (auto iter = map_.mainDB_.begin(); iter != map_.mainDB_.end(); iter++) {
			map_.cert_Map_.insert({ iter->second.certi_,iter->second.num_ });
		}
		break;
	case Column::FirstName:
		for (auto num : nums) {
			if (map_.mainDB_.count(num) == 1) {
				map_.mainDB_[num].firstName_ = update.value;
			}
		}
		map_.firstName_Map_.clear();
		map_.fullName_Map_.clear();
		for (auto iter = map_.mainDB_.begin(); iter != map_.mainDB_.end(); iter++) {
			map_.firstName_Map_.insert({ iter->second.firstName_, iter->second.num_ });
			map_.fullName_Map_.insert({ iter->second.GetFullName(), iter->second.num_ });
		}
		break;
	case Column::LastName:
		for (auto num : nums) {
			if (map_.mainDB_.count(num) == 1) {
				map_.mainDB_[num].lastName_ = update.value;
			}
		}
		map_.lastName_Map_.clear();
		map_.fullName_Map_.clear();
		for (auto iter = map_.mainDB_.begin(); iter != map_.mainDB_.end(); iter++) {
			map_.lastName_Map_.insert({ iter->second.lastName_, iter->second.num_ });//
			map_.fullName_Map_.insert({ iter->second.GetFullName(), iter->second.num_ });
		}
		break;
	case Column::MiddlePhoneNum:
		for (auto num : nums) {
			if (map_.mainDB_.count(num) == 1) {
				map_.mainDB_[num].midPhoneNum_ = update.value;
			}
		}
		map_.midPhone_Map_.clear();
		map_.fullPhone_Map_.clear();
		for (auto iter = map_.mainDB_.begin(); iter != map_.mainDB_.end(); iter++) {
			map_.midPhone_Map_.insert({ iter->second.midPhoneNum_, iter->second.num_ });
			map_.fullPhone_Map_.insert({ iter->second.GetFullPhoneNum(), iter->second.num_ });
		}
		break;
	case Column::LastPhoneNum:
		for (auto num : nums) {
			if (map_.mainDB_.count(num) == 1) {
				map_.mainDB_[num].lastPhoneNum_ = update.value;
			}
		}
		map_.lastPhone_Map_.clear();//
		map_.fullPhone_Map_.clear();
		for (auto iter = map_.mainDB_.begin(); iter != map_.mainDB_.end(); iter++) {
			map_.lastPhone_Map_.insert({ iter->second.lastPhoneNum_, iter->second.num_ });
			map_.fullPhone_Map_.insert({ iter->second.GetFullPhoneNum(), iter->second.num_ });
		}
		break;
	case Column::BirthdayYear:
		for (auto num : nums) {
			if (map_.mainDB_.count(num) == 1) {
				map_.mainDB_[num].birthYear_ = update.value;
			}
		}
		map_.birthYear_Map_.clear();
		map_.birth_Map_.clear();
		for (auto iter = map_.mainDB_.begin(); iter != map_.mainDB_.end(); iter++) {
			map_.birthYear_Map_.insert({ iter->second.birthYear_, iter->second.num_ });
			map_.birth_Map_.insert({ iter->second.GetFullBirthday(), iter->second.num_ });
		}
		break;
	case Column::BirthdayMonth:
		for (auto num : nums) {
			if (map_.mainDB_.count(num) == 1) {
				map_.mainDB_[num].birthMonth_ = update.value;
			}
		}
		map_.birthMonth_Map_.clear();
		map_.birth_Map_.clear();
		for (auto iter = map_.mainDB_.begin(); iter != map_.mainDB_.end(); iter++) {
			map_.birthMonth_Map_.insert({ iter->second.birthMonth_, iter->second.num_ });
			map_.birth_Map_.insert({ iter->second.GetFullBirthday(), iter->second.num_ });
		}
		break;
	case Column::BirthdayDay:
		for (auto num : nums) {
			if (map_.mainDB_.count(num) == 1) {
				map_.mainDB_[num].birthDay_ = update.value;
			}
		}
		map_.birthDay_Map_.clear();
		map_.birth_Map_.clear();
		for (auto iter = map_.mainDB_.begin(); iter != map_.mainDB_.end(); iter++) {
			map_.birthDay_Map_.insert({ iter->second.birthDay_, iter->second.num_ });
			map_.birth_Map_.insert({ iter->second.GetFullBirthday(), iter->second.num_ });
		}
		break;
	default:
		break;
	}

	return result;
}

vector<EmployeeInfo> MemoryDatabase::UpdateDB(TargetParam filter, TargetParam update) {
	vector<EmployeeInfo> result;	

	if (filter.column >= Column::None) {
		return result;
	}


	vector<unsigned int> nums = GetEmployeeNums_(filter.column, filter.value);
	if (nums.size()) {
		return GetUpdateMainDB_(nums, update);
	}

	return result;
}

vector<EmployeeInfo> MemoryDatabase::ReadDB(TargetParam filter) {
	vector<EmployeeInfo> result;

	if (filter.column >= Column::None) {
		return result;
	}

	if (filter.column == Column::EmployeeNum) {
		map<unsigned int, EmployeeInfo>::iterator employee = map_.mainDB_.find(stoul(filter.value, nullptr, 0));
		if (employee != map_.mainDB_.end()) {
			result.push_back(employee->second);
			return result;
		}
	}

	for (auto num : GetEmployeeNums_(filter.column, filter.value)) {
		result.push_back(map_.mainDB_[num]);
	}
	return result;
}

void MemoryDatabase::EraseEmployee_(multimap<string, unsigned int>& map, const string key, const unsigned int num) {
	for (auto itr = map.lower_bound(key); itr != map.upper_bound(key); itr++) {
		if (itr->second == num) {
			map.erase(itr);
			return;
		}
	}
}

vector<EmployeeInfo> MemoryDatabase::DeleteDB(TargetParam filter) {
	vector<EmployeeInfo> target = ReadDB(filter);
	if (target.size() == 0) {
		return target;
	}

	for (auto person : target) {
		map_.mainDB_.erase(person.num_);		

		EraseEmployee_(map_.fullName_Map_, person.GetFullName(), person.num_);
		EraseEmployee_(map_.firstName_Map_, person.firstName_, person.num_);
		EraseEmployee_(map_.lastName_Map_, person.lastName_, person.num_);

		EraseEmployee_(map_.birth_Map_, person.GetFullBirthday(), person.num_);
		EraseEmployee_(map_.birthYear_Map_, person.birthYear_, person.num_);
		EraseEmployee_(map_.birthMonth_Map_, person.birthMonth_, person.num_);
		EraseEmployee_(map_.birthDay_Map_, person.birthDay_, person.num_);

		EraseEmployee_(map_.fullPhone_Map_, person.GetFullPhoneNum(), person.num_);
		EraseEmployee_(map_.midPhone_Map_, person.midPhoneNum_, person.num_);
		EraseEmployee_(map_.lastPhone_Map_, person.lastPhoneNum_, person.num_);

		EraseEmployee_(map_.cert_Map_, person.certi_, person.num_);
		EraseEmployee_(map_.career_Map_, person.cl_, person.num_);
	}
	return target;
}
