#pragma once
#include "CommandProcessor.h"

class ModCommandProcessor : public CommandProcessor {
public:
	ModCommandProcessor(void) = delete;
	ModCommandProcessor(IDatabase* database, IPrinter* printer);
	void Process(Command& command) override;

private:
	IPrinter* const printer_;
	IDatabase* const database_;
};
