#pragma once
#include "gmock/gmock.h"
#include "../GreenLight/IPrinter.h"

class PrinterMock : public IPrinter {
public:
	MOCK_METHOD(void, Print, (const CommandType commandType, const PrintOption printOption, const std::vector<EmployeeInfo>& info), (override));
};