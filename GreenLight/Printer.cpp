#include "Printer.h"

Printer::Printer(ISorter* sorter, IOutput* output)
{
	sorter_ = sorter;
	output_ = output;
}

void Printer::Print(const PrintOption printOption, const std::vector<EmployeeInfo>& info)
{
	vector<EmployeeInfo> result = sorter_->Sort(info);
	output_->Show(printOption, result);

	return;
}