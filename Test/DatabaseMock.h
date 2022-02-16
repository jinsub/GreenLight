#pragma once
#include "gmock/gmock.h"
#include "../GreenLight/IDatabase.h"

class DatabaseMock : public IDatabase {
public:
	MOCK_METHOD(vector<EmployeeInfo>, CreateDB, (EmployeeInfo info), (override));
	MOCK_METHOD(vector<EmployeeInfo>, ReadDB, (TargetParam filter), (override));
	MOCK_METHOD(vector<EmployeeInfo>, UpdateDB, (TargetParam filter, TargetParam update), (override));
	MOCK_METHOD(vector<EmployeeInfo>, DeleteDB, (TargetParam filter), (override));
};