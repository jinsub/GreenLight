#include "ModCommandProcessor.h"

ModCommandProcessor::ModCommandProcessor(IDatabase* database, IPrinter* printer)
	: database_(database), printer_(printer), CommandProcessor()
{
}

void ModCommandProcessor::Process(Command& command) {
	TargetParam filter;
	filter.column = GetFilterColumn_(command.filterOption_, command.arguments_[0]);
	filter.value = GetColumnValue_(filter.column, command.arguments_[1]);
	TargetParam update;
	update.column = GetColumn_(command.arguments_[2]);
	update.value = GetColumnValue_(update.column, command.arguments_[3]);

	printer_->Print(CommandType::MOD, command.printOption_, database_->UpdateDB(filter, update));

	return;
}