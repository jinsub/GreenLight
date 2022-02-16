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
		break;
	case CommandType::SCH:
		break;
	case CommandType::MOD:
		break;
	}
	return;
}

void CommandProcessor::ProcessAdd_(vector<string> args) {
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

	auto result = database_->CreateDB(info);

	return;
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
