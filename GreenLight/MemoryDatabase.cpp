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
		auto it = map_.mainDB_.find(stoul(key));
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

void MemoryDatabase::CreateEmploy_(const EmployeeInfo& info, const Column column) {
	if (column > Column::None) {
		return;
	}

	map_.mainDB_.insert({ info.num_, info });

	switch (column) {
	case Column::Name:
	case Column::FirstName:
	case Column::LastName:
		map_.fullName_Map_.insert({ info.GetFullName(), info.num_ });
		map_.firstName_Map_.insert({ info.firstName_, info.num_ });
		map_.lastName_Map_.insert({ info.lastName_, info.num_ });
		break;
	case Column::Birthday:
	case Column::BirthdayYear:
	case Column::BirthdayMonth:
	case Column::BirthdayDay:
		map_.birth_Map_.insert({ info.GetFullBirthday(), info.num_ });
		map_.birthYear_Map_.insert({ info.birthYear_, info.num_ });
		map_.birthMonth_Map_.insert({ info.birthMonth_, info.num_ });
		map_.birthDay_Map_.insert({ info.birthDay_, info.num_ });
		break;
	case Column::PhoneNumber:
	case Column::MiddlePhoneNum:
	case Column::LastPhoneNum:
		map_.fullPhone_Map_.insert({ info.GetFullPhoneNum(), info.num_ });
		map_.midPhone_Map_.insert({ info.midPhoneNum_, info.num_ });
		map_.lastPhone_Map_.insert({ info.lastPhoneNum_, info.num_ });
		break;
	case Column::CareerLevel:
		map_.career_Map_.insert({ info.cl_, info.num_ });
		break;
	case Column::Certi:
		map_.cert_Map_.insert({ info.certi_, info.num_ });
		break;
	case Column::None:
		map_.fullName_Map_.insert({ info.GetFullName(), info.num_ });
		map_.firstName_Map_.insert({ info.firstName_, info.num_ });
		map_.lastName_Map_.insert({ info.lastName_, info.num_ });
		map_.birth_Map_.insert({ info.GetFullBirthday(), info.num_ });
		map_.birthYear_Map_.insert({ info.birthYear_, info.num_ });
		map_.birthMonth_Map_.insert({ info.birthMonth_, info.num_ });
		map_.birthDay_Map_.insert({ info.birthDay_, info.num_ });
		map_.fullPhone_Map_.insert({ info.GetFullPhoneNum(), info.num_ });
		map_.midPhone_Map_.insert({ info.midPhoneNum_, info.num_ });
		map_.lastPhone_Map_.insert({ info.lastPhoneNum_, info.num_ });
		map_.career_Map_.insert({ info.cl_, info.num_ });
		map_.cert_Map_.insert({ info.certi_, info.num_ });
		break;
	}
}
vector<EmployeeInfo> MemoryDatabase::CreateDB(EmployeeInfo info) {
	//cout << "CreateDB" << endl;
	vector<EmployeeInfo> result;


	CreateEmploy_(info);

	result.push_back(info);

	return result;
}

vector<EmployeeInfo> MemoryDatabase::GetUpdateMainDB_(const vector<unsigned int> nums, TargetParam update) {
	vector<EmployeeInfo> result;

	if (nums.size() == 0) {
		return result;
	}
	if (update.column >= Column::None) {
		return result;
	}

	for (auto num : nums) {
		result.push_back(map_.mainDB_[num]);

	}

	if (update.column == Column::EmployeeNum) {
		for (auto num : nums) {
			auto it = map_.mainDB_.find(stoul(update.value));
			if (num != stoul(update.value) && it != map_.mainDB_.end()) {
				result.clear();
				return result;
			}
			EmployeeInfo info = map_.mainDB_[num];
			DeleteEmploy_(info);
			info.num_ = stoul(update.value);
			CreateEmploy_(info);
		}
		return result;
	}

	switch (update.column) {
	case Column::Name:
		for (auto num : nums) {
			EmployeeInfo info = map_.mainDB_[num];
			DeleteEmploy_(info, update.column);

			info.firstName_ = Split_(update.value, ' ')[0];
			info.lastName_ = Split_(update.value, ' ')[1];

			CreateEmploy_(info, update.column);
		}
		break;
	case Column::FirstName:
		for (auto num : nums) {
			EmployeeInfo info = map_.mainDB_[num];
			DeleteEmploy_(info, update.column);

			info.firstName_ = update.value;

			CreateEmploy_(info, update.column);
		}
		break;
	case Column::LastName:
		for (auto num : nums) {
			EmployeeInfo info = map_.mainDB_[num];
			DeleteEmploy_(info, update.column);

			info.lastName_ = update.value;

			CreateEmploy_(info, update.column);
		}
		break;
	case Column::Birthday:
		for (auto num : nums) {
			EmployeeInfo info = map_.mainDB_[num];
			DeleteEmploy_(info, update.column);

			info.birthYear_ = update.value.substr(0, 4);
			info.birthMonth_ = update.value.substr(4, 2);
			info.birthDay_ = update.value.substr(6, 2);

			CreateEmploy_(info, update.column);
		}
		break;
	case Column::BirthdayYear:
		for (auto num : nums) {
			EmployeeInfo info = map_.mainDB_[num];
			DeleteEmploy_(info, update.column);

			info.birthYear_ = update.value;

			CreateEmploy_(info, update.column);
		}
		break;
	case Column::BirthdayMonth:
		for (auto num : nums) {
			EmployeeInfo info = map_.mainDB_[num];
			DeleteEmploy_(info, update.column);

			info.birthMonth_ = update.value;

			CreateEmploy_(info, update.column);
		}
		break;
	case Column::BirthdayDay:
		for (auto num : nums) {
			EmployeeInfo info = map_.mainDB_[num];
			DeleteEmploy_(info, update.column);

			info.birthDay_ = update.value;

			CreateEmploy_(info, update.column);
		}
		break;
	case Column::PhoneNumber:
		for (auto num : nums) {
			EmployeeInfo info = map_.mainDB_[num];
			DeleteEmploy_(info, update.column);

			info.midPhoneNum_ = Split_(update.value, '-')[1];
			info.lastPhoneNum_ = Split_(update.value, '-')[2];

			CreateEmploy_(info, update.column);
		}
		break;
	case Column::MiddlePhoneNum:
		for (auto num : nums) {
			EmployeeInfo info = map_.mainDB_[num];
			DeleteEmploy_(info, update.column);

			info.midPhoneNum_ = update.value;

			CreateEmploy_(info, update.column);
		}
		break;
	case Column::LastPhoneNum:
		for (auto num : nums) {
			EmployeeInfo info = map_.mainDB_[num];
			DeleteEmploy_(info, update.column);

			info.lastPhoneNum_ = update.value;

			CreateEmploy_(info, update.column);
		}
		break;
	case Column::CareerLevel:
		for (auto num : nums) {
			EmployeeInfo info = map_.mainDB_[num];
			DeleteEmploy_(info, update.column);

			info.cl_ = update.value;

			CreateEmploy_(info, update.column);
		}
		break;
	case Column::Certi:
		for (auto num : nums) {
			EmployeeInfo info = map_.mainDB_[num];
			DeleteEmploy_(info, update.column);

			info.certi_ = update.value;

			CreateEmploy_(info, update.column);
		}
		break;
	}

	return result;
}

vector<EmployeeInfo> MemoryDatabase::UpdateDB(TargetParam filter, TargetParam update) {
	//cout << "UpdateDB" << endl;
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
	//cout << "ReadDB" << endl;
	vector<EmployeeInfo> result;


	if (filter.column >= Column::None) {
		return result;
	}

	if (filter.column == Column::EmployeeNum) {
		map<unsigned int, EmployeeInfo>::iterator employee = map_.mainDB_.find(stoul(filter.value));
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

void MemoryDatabase::DeleteEmploy_(const EmployeeInfo& info, const Column column) {
	if (column > Column::None) {
		return;
	}
	map_.mainDB_.erase(info.num_);

	switch (column) {
	case Column::Name:
	case Column::FirstName:
	case Column::LastName:
		EraseEmployee_(map_.fullName_Map_, info.GetFullName(), info.num_);
		EraseEmployee_(map_.firstName_Map_, info.firstName_, info.num_);
		EraseEmployee_(map_.lastName_Map_, info.lastName_, info.num_);
		break;
	case Column::Birthday:
	case Column::BirthdayYear:
	case Column::BirthdayMonth:
	case Column::BirthdayDay:
		EraseEmployee_(map_.birth_Map_, info.GetFullBirthday(), info.num_);
		EraseEmployee_(map_.birthYear_Map_, info.birthYear_, info.num_);
		EraseEmployee_(map_.birthMonth_Map_, info.birthMonth_, info.num_);
		EraseEmployee_(map_.birthDay_Map_, info.birthDay_, info.num_);
		break;
	case Column::PhoneNumber:
	case Column::MiddlePhoneNum:
	case Column::LastPhoneNum:
		EraseEmployee_(map_.fullPhone_Map_, info.GetFullPhoneNum(), info.num_);
		EraseEmployee_(map_.midPhone_Map_, info.midPhoneNum_, info.num_);
		EraseEmployee_(map_.lastPhone_Map_, info.lastPhoneNum_, info.num_);
		break;
	case Column::CareerLevel:
		EraseEmployee_(map_.career_Map_, info.cl_, info.num_);
		break;
	case Column::Certi:
		EraseEmployee_(map_.cert_Map_, info.certi_, info.num_);
		break;
	case Column::None:
		EraseEmployee_(map_.fullName_Map_, info.GetFullName(), info.num_);
		EraseEmployee_(map_.firstName_Map_, info.firstName_, info.num_);
		EraseEmployee_(map_.lastName_Map_, info.lastName_, info.num_);

		EraseEmployee_(map_.birth_Map_, info.GetFullBirthday(), info.num_);
		EraseEmployee_(map_.birthYear_Map_, info.birthYear_, info.num_);
		EraseEmployee_(map_.birthMonth_Map_, info.birthMonth_, info.num_);
		EraseEmployee_(map_.birthDay_Map_, info.birthDay_, info.num_);

		EraseEmployee_(map_.fullPhone_Map_, info.GetFullPhoneNum(), info.num_);
		EraseEmployee_(map_.midPhone_Map_, info.midPhoneNum_, info.num_);
		EraseEmployee_(map_.lastPhone_Map_, info.lastPhoneNum_, info.num_);

		EraseEmployee_(map_.cert_Map_, info.certi_, info.num_);
		EraseEmployee_(map_.career_Map_, info.cl_, info.num_);
		break;
	}
}
vector<EmployeeInfo> MemoryDatabase::DeleteDB(TargetParam filter) {
	//cout << "DeleteDB" << endl;
	vector<EmployeeInfo> target = ReadDB(filter);
	if (target.size() == 0) {
		return target;
	}

	for (auto person : target) {
		DeleteEmploy_(person);
	}
	return target;
}
