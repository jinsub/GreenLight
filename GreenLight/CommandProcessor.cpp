#include "CommandProcessor.h"
#include <sstream>

int CommandProcessor::GetExtendedEmplyeeNum_(const string employeeNumStr) {
	constexpr int YearThreshold = 50000000;
	constexpr int TwentyCentry = 1900000000;
	constexpr int TwentyOneCentry = 2000000000;
	auto employeeNum = atoi(employeeNumStr.c_str());
	
	if (employeeNum < YearThreshold)
	{
		return employeeNum + TwentyOneCentry;
	}
	return employeeNum + TwentyCentry;
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

string CommandProcessor::GetColumnValue_(Column column, string value) {
	if (column == Column::EmployeeNum) {
		return to_string(GetExtendedEmplyeeNum_(value));
	}
	return value;
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
