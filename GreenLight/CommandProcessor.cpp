#include "CommandProcessor.h"
#include <sstream>

CommandProcessor::CommandProcessor(IDatabase* database, IPrinter* printer)
	: database_(database), printer_(printer)
{
}

void CommandProcessor::Process(Command& command) {
	switch (command.type_) {
	case CommandType::ADD:
		ProcessAdd_(command.arguments_);
		break;
	case CommandType::DEL:
		ProcessDel_(command.filterOption_, command.printOption_, command.arguments_);
		break;
	case CommandType::SCH:
		ProcessSch_(command.filterOption_, command.printOption_, command.arguments_);
		break;
	case CommandType::MOD:
		ProcessMod_(command.filterOption_, command.printOption_, command.arguments_);
		break;
	}
	return;
}

void CommandProcessor::ProcessAdd_(const vector<string>& args) {
	auto result = database_->CreateDB(MakeEmployeeInfo_(args));
	return;
}

void CommandProcessor::ProcessDel_(const FilterOption filterOption, const PrintOption printOption, const vector<string>& args) {
	TargetParam filter;
	filter.column = GetFilterColumn_(filterOption, args[0]);
	filter.value = args[1];

	printer_->Print(printOption, database_->DeleteDB(filter));

	return;
}

void CommandProcessor::ProcessSch_(const FilterOption filterOption, const PrintOption printOption, const vector<string>& args) {
	TargetParam filter;
	filter.column = GetFilterColumn_(filterOption, args[0]);
	filter.value = args[1];

	printer_->Print(printOption, database_->ReadDB(filter));

	return;
}

void CommandProcessor::ProcessMod_(const FilterOption filterOption, const PrintOption printOption, const vector<string>& args) {
	TargetParam filter;
	filter.column = GetFilterColumn_(filterOption, args[0]);
	filter.value = args[1];
	TargetParam update;
	update.column = GetColumn_(args[2]);
	update.value = args[3];

	printer_->Print(printOption, database_->UpdateDB(filter, update));

	return;
}

EmployeeInfo CommandProcessor::MakeEmployeeInfo_(const vector<string>& args) {
	EmployeeInfo info;
	info.num_ = atoi(args[0].c_str());
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

Column CommandProcessor::GetColumn_(string columnName) {
	if (columnName == "employeeNum") { return Column::EmployeeNum; }
	if (columnName == "name") { return Column::Name; }
	if (columnName == "cl") { return Column::CareerLevel; }
	if (columnName == "phoneNum") { return Column::PhoneNumber; }
	if (columnName == "birthday") { return Column::Birthday; }
	if (columnName == "certi") { return Column::Certi; }

	return Column::Invalid;
}

Column CommandProcessor::GetFilterColumn_(FilterOption filterOption, string columnName) {
	if (filterOption == FilterOption::None) {
		return GetColumn_(columnName);
	}
	if (filterOption == FilterOption::FirstName && columnName == "name") { return Column::FirstName; }
	if (filterOption == FilterOption::LastName && columnName == "name") { return Column::LastName; }
	if (filterOption == FilterOption::MiddlePhoneNum && columnName == "phoneNum") { return Column::MiddlePhoneNum; }
	if (filterOption == FilterOption::LastPhoneNum && columnName == "phoneNum") { return Column::LastPhoneNum; }
	if (filterOption == FilterOption::BirthdayYear && columnName == "birthday") { return Column::BirthdayYear; }
	if (filterOption == FilterOption::BirthdayMonth && columnName == "birthday") { return Column::BirthdayMonth; }
	if (filterOption == FilterOption::BirthdayDay && columnName == "birthday") { return Column::BirthdayDay; }

	return Column::Invalid;
}

vector<string> CommandProcessor::Split_(string str, const char separator) {
	istringstream iss(str);
	string buffer;
	vector<string> result;

	while (getline(iss, buffer, separator)) {
		result.push_back(buffer);
	}

	return result;
}
