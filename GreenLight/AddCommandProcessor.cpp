#include "AddCommandProcessor.h"

AddCommandProcessor::AddCommandProcessor(IDatabase* database)
	: database_(database), CommandProcessor()
{
}

void AddCommandProcessor::Process(Command& command) {
	auto result = database_->CreateDB(MakeEmployeeInfo_(command.arguments_));
	return;
}

EmployeeInfo AddCommandProcessor::MakeEmployeeInfo_(const vector<string>& args) {
	EmployeeInfo info;
	info.num_ = GetExtendedEmplyeeNum_(args[0]);
	info.firstName_ = Split_(args[1], ' ')[0];
	info.lastName_ = Split_(args[1], ' ')[1];
	info.cl_ = args[2];
	info.midPhoneNum_ = Split_(args[3], '-')[1];
	info.lastPhoneNum_ = Split_(args[3], '-')[2];
	info.birthYear_ = args[4].substr(0, 4);
	info.birthMonth_ = args[4].substr(4, 2);
	info.birthDay_ = args[4].substr(6, 2);
	info.certi_ = args[5];

	return info;
}
