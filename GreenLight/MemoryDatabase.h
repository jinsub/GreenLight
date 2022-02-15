#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "IDatabase.h"

using namespace std;


struct MemoryDatabase : IDatabase {

	vector<EmployeeInfo> createDB() override;
	vector<EmployeeInfo> readDB(FilterOptionType opt, Parameter param) override;
	vector<EmployeeInfo> updateDB(FilterOptionType opt, Parameter paramOld, Parameter paramNew) override;
	vector<EmployeeInfo> deleteDB(FilterOptionType opt, Parameter param) override;

	map<unsigned int, EmployeeInfo> MainDB;
	multimap<string, unsigned int> FirstName_Map;
	multimap<string, unsigned int> LastName_Map;
	multimap<string, unsigned int> MidPhone_Map;
	multimap<string, unsigned int> LastPhone_Map;
	multimap<string, unsigned int> BirthYear_Map;
	multimap<string, unsigned int> BirthMonth_Map;
	multimap<string, unsigned int> BirthDay_Map;
	multimap<CareerLevel, unsigned int> Carrer_Map;
	multimap<CertLevel, unsigned int> Cert_Map;
};