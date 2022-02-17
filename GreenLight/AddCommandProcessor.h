#pragma once
#include "CommandProcessor.h"

class AddCommandProcessor : public CommandProcessor {
public:
	AddCommandProcessor(void) = delete;
	AddCommandProcessor(IDatabase* database);
	void Process(Command& command) override;

private:
	EmployeeInfo MakeEmployeeInfo_(const vector<string>& args);

	IDatabase* const database_;
};