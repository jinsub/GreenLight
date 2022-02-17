#pragma once
#include "CommandProcessor.h"

class DelCommandProcessor : public CommandProcessor {
public:
	DelCommandProcessor(void) = delete;
	DelCommandProcessor(IDatabase* database, IPrinter* printer);
	void Process(Command& command) override;

private:
	IPrinter* const printer_;
	IDatabase* const database_;
};
