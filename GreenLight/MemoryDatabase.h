#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include "IDatabase.h"

using namespace std;

struct DataBaseMap {
	map<unsigned int, EmployeeInfo> mainDB_;
	multimap<string, unsigned int> fullName_Map_;
	multimap<string, unsigned int> firstName_Map_;
	multimap<string, unsigned int> lastName_Map_;
	multimap<string, unsigned int> fullPhone_Map_;
	multimap<string, unsigned int> midPhone_Map_;
	multimap<string, unsigned int> lastPhone_Map_;
	multimap<string, unsigned int> birth_Map_;
	multimap<string, unsigned int> birthYear_Map_;
	multimap<string, unsigned int> birthMonth_Map_;
	multimap<string, unsigned int> birthDay_Map_;
	multimap<string, unsigned int> career_Map_;
	multimap<string, unsigned int> cert_Map_;
};

class MemoryDatabase : IDatabase {
public:
	MemoryDatabase() {}
	MemoryDatabase(DataBaseMap map) :map_(map) {

	}
	vector<EmployeeInfo> CreateDB(EmployeeInfo info) override;
	vector<EmployeeInfo> ReadDB(TargetParam filter) override;
	vector<EmployeeInfo> UpdateDB(TargetParam filter, TargetParam update) override;
	vector<EmployeeInfo> DeleteDB(TargetParam filter) override;

	size_t GetDBSize(Column column) {
		switch (column)
		{
		case Column::EmployeeNum:
			return map_.mainDB_.size();
		case Column::Name:
			return map_.fullName_Map_.size();
		case Column::CareerLevel:
			return map_.career_Map_.size();
		case Column::PhoneNumber:
			return map_.fullPhone_Map_.size();
		case Column::Birthday:
			return map_.birth_Map_.size();
		case Column::Certi:
			return map_.cert_Map_.size();
		case Column::FirstName:
			return map_.firstName_Map_.size();
		case Column::LastName:
			return map_.lastName_Map_.size();
		case Column::MiddlePhoneNum:
			return map_.midPhone_Map_.size();
		case Column::LastPhoneNum:
			return map_.lastPhone_Map_.size();
		case Column::BirthdayYear:
			return map_.birthYear_Map_.size();
		case Column::BirthdayMonth:
			return map_.birthMonth_Map_.size();
		case Column::BirthdayDay:
			return map_.birthDay_Map_.size();
		case Column::None:			
			break;
		case Column::Invalid:
			break;
		default:
			break;
		}
		return 0;
	}

private:
	vector<unsigned int> GetEmployeeNums_(const multimap<string, unsigned int>& map, const string key);
	void EraseEmployee_(multimap<string, unsigned int>& map, const string key, const unsigned int num);
	void SetEmployeeInfo_(multimap<string, unsigned int>& map, const unsigned int num, string oldParam, string newParam);
	vector<string> Split_(string str, char delimiter);
	vector<EmployeeInfo> GetUpdateMainDB_(DataBaseMap& map, const vector<unsigned int> nums, TargetParam update);

	DataBaseMap map_;	
};