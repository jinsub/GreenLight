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
	void ProcessAdd_(vector<string> args);
	vector<string> Split_(string str, const char separator);

	IDatabase* const database_;
	IPrinter* const printer_;
};
