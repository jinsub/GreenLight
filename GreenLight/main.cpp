#include <iostream>
#include "CommandParser.h"
#include "CommandProcessor.h"
#include "Printer.h"
#include "AscendingEmployeeNumber.h"
#include "FileOutput.h"

using namespace std;

class DummyDatabase : public IDatabase {
	vector<EmployeeInfo> CreateDB(EmployeeInfo info) override { return vector<EmployeeInfo>{}; }
	vector<EmployeeInfo> ReadDB(TargetParam filter) override { return vector<EmployeeInfo>{}; }
	vector<EmployeeInfo> UpdateDB(TargetParam filter, TargetParam update) override { return vector<EmployeeInfo>{}; }
	vector<EmployeeInfo> DeleteDB(TargetParam filter) override { return vector<EmployeeInfo>{}; }
};

class DummyPrinter : public IPrinter {
	void Print(const CommandType commandType, const PrintOption printOption, const std::vector<EmployeeInfo>& info) override { return; }
};

int main(int argc, char* argv[])
{
	cout << argv[1] << endl;
	cout << argv[2] << endl;

	auto database = new DummyDatabase();
	auto printer = new Printer(new AscendingEmployeeNumber(), new FileOutput(argv[2]));
	auto parser = CommandParser();
	auto processor = CommandProcessor(database, printer);

	vector<string>&& lines = parser.ParseFile(argv[1]);
	vector<Command>&& commands = parser.ParseLine(lines);

	for (auto command : commands) {
		processor.Process(command);
	}

	return 0;
}
