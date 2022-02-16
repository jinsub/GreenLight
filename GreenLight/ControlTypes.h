#pragma once
#include "IPrinter.h"

enum class CommandType {
	ADD,
	DEL,
	SCH,
	MOD,
	INVALID
};

enum class FilterOption {
	FirstName,
	LastName,
	MiddlePhoneNum,
	LastPhoneNum,
	BirthdayYear,
	BirthdayMonth,
	BirthdayDay,
	None,
	Invalid
};

struct Command {
	CommandType type_;
	PrintOption printOption_;
	FilterOption filterOption_;
	std::vector<std::string> arguments_;
};