#include "Printer.h"

void Printer::Print(const CommandType commandType, const PrintOption printOption, const std::vector<EmployeeInfo>& info)
{
	vector<EmployeeInfo> result = sorter_->Sort(info);

	if (printOption == PrintOption::PrintLines) {
		output_->Show(commandType, result);
	}
	else if (printOption == PrintOption::PrintCount) {
		output_->Show(commandType, result.size());
	}

	return;
}