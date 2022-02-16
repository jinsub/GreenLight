#include "CommandProcessor.h"

CommandProcessor::CommandProcessor(IDatabase* database, IPrinter* printer)
	: database_(database), printer_(printer)
{
}

void CommandProcessor::Process(Command& command) {
	return;
}