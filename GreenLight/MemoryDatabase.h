#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "IDatabase.h"

using namespace std;

class MemoryDatabase : IDatabase {
public:
	vector<EmployeeInfo> CreateDB(EmployeeInfo info) override;
	vector<EmployeeInfo> ReadDB(TargetParam filter) override;
	vector<EmployeeInfo> UpdateDB(TargetParam filter, TargetParam update) override;
	vector<EmployeeInfo> DeleteDB(TargetParam filter) override;

private:
	map<unsigned int, EmployeeInfo> mainDB_;
	multimap<string, unsigned int> firstName_Map_;
	multimap<string, unsigned int> lastName_Map_;
	multimap<string, unsigned int> midPhone_Map_;
	multimap<string, unsigned int> lastPhone_Map_;
	multimap<unsigned int, unsigned int> birthYear_Map_;
	multimap<unsigned int, unsigned int> birthMonth_Map_;
	multimap<unsigned int, unsigned int> birthDay_Map_;
	multimap<CareerLevel, unsigned int> career_Map_;
	multimap<CertLevel, unsigned int> cert_Map_;

};