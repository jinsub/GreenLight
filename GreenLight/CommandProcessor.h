#pragma once
#include "IDatabase.h"
#include "IPrinter.h"
#include "ControlTypes.h"

class CommandProcessor {
public:
	virtual void Process(Command& command) = 0;

protected:
	Column GetFilterColumn_(FilterOption filterOption, string columnName);
	Column GetColumn_(string columnName);
	string GetColumnValue_(Column column, string value);
	int GetExtendedEmplyeeNum_(const string employeeNum);
};
