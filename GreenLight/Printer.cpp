#include "Printer.h"

void Printer::Print(const CommandType commandType, const PrintOption printOption, const std::vector<EmployeeInfo>& info)
{
	if (printOption == PrintOption::PrintLines) {
		//output_->Show(commandType, sorter_->Sort(info));
		output_->Show(commandType, sorter_->Sort_partial(info, MAX_PRINT_CNT));
		
	}
	else if (printOption == PrintOption::PrintCount) {
		output_->Show(commandType, info.size());
	}

	return;
}