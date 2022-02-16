#pragma once
#include "IDatabase.h"
#include "IPrinter.h"
#include "ControlTypes.h"

class CommandProcessor {
public:
	CommandProcessor(void) = delete;
	CommandProcessor(IDatabase* database, IPrinter* printer);
	void Process(Command& command);

private:
	void ProcessAdd_(const vector<string>& args);
	void ProcessDel_(const FilterOption filterOption, const PrintOption printOption, const vector<string>& args);
	void ProcessSch_(const FilterOption filterOption, const PrintOption printOption, const vector<string>& args);

	EmployeeInfo MakeEmployeeInfo_(const vector<string>& args);
	Column GetFilterColumn_(FilterOption filterOption, string columnName);
	Column GetColumn_(string columnName);
	vector<string> Split_(string str, const char separator);

	IDatabase* const database_;
	IPrinter* const printer_;
};
