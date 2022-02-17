#include "DelCommandProcessor.h"

DelCommandProcessor::DelCommandProcessor(IDatabase* database, IPrinter* printer)
	: database_(database), printer_(printer), CommandProcessor()
{
}

void DelCommandProcessor::Process(Command& command) {
	TargetParam filter;
	filter.column = GetFilterColumn_(command.filterOption_, command.arguments_[0]);
	filter.value = GetColumnValue_(filter.column, command.arguments_[1]);

	printer_->Print(CommandType::DEL, command.printOption_, database_->DeleteDB(filter));

	return;
}
