#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "IDatabase.h"

using namespace std;

class MemoryDatabase : IDatabase {
public:
	vector<EmployeeInfo> CreateDB() override;
	vector<EmployeeInfo> ReadDB(FilterOptionType opt, Parameter param) override;
	vector<EmployeeInfo> UpdateDB(FilterOptionType opt, Parameter paramOld, Parameter paramNew) override;
	vector<EmployeeInfo> DeleteDB(FilterOptionType opt, Parameter param) override;

private:
	map<unsigned int, EmployeeInfo> mainDB_;
	multimap<string, unsigned int> firstName_Map_;
	multimap<string, unsigned int> lastName_Map_;
	multimap<string, unsigned int> midPhone_Map_;
	multimap<string, unsigned int> lastPhone_Map_;
	multimap<string, unsigned int> birthYear_Map_;
	multimap<string, unsigned int> birthMonth_Map_;
	multimap<string, unsigned int> birthDay_Map_;
	multimap<CareerLevel, unsigned int> career_Map_;
	multimap<CertLevel, unsigned int> cert_Map_;

};