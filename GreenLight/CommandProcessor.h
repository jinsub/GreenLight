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
	IDatabase* const database_;
	IPrinter* const printer_;
};
