#include "Printer.h"

void Printer::Print(const PrintOption printOption, const std::vector<EmployeeInfo>& info)
{
	vector<EmployeeInfo> result = sorter_->Sort(info);

	if (printOption == PrintOption::PrintLines) {
		output_->Show(result);
	}
	else if (printOption == PrintOption::PrintCount) {
		output_->Show(result.size());
	}

	return;
}