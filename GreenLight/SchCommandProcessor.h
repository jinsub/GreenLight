#pragma once
#include "CommandProcessor.h"

class SchCommandProcessor : public CommandProcessor {
public:
	SchCommandProcessor(void) = delete;
	SchCommandProcessor(IDatabase* database, IPrinter* printer);
	void Process(Command& command) override;

private:
	IPrinter* const printer_;
	IDatabase* const database_;
};
