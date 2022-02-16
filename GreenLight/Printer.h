#pragma once
#include "IPrinter.h"
#include "ISorter.h"
#include "IOutput.h"

class Printer : public IPrinter {
public:
	Printer(ISorter* sorter, IOutput* output) :
		sorter_(sorter),
		output_(output)
	{}

	void Print(const PrintOption printOption, const std::vector<EmployeeInfo>& info) override;

private:
	ISorter* sorter_;
	IOutput* output_;
};