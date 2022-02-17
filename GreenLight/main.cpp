#include <iostream>
#include "CommandParser.h"
#include "CommandProcessor.h"
#include "Printer.h"
#include "AscendingEmployeeNumber.h"
#include "FileOutput.h"
#include "MemoryDatabase.h"

using namespace std;

class DummyDatabase : public IDatabase {
	vector<EmployeeInfo> CreateDB(EmployeeInfo info) override { return vector<EmployeeInfo>{}; }
	vector<EmployeeInfo> ReadDB(TargetParam filter) override { return vector<EmployeeInfo>{}; }
	vector<EmployeeInfo> UpdateDB(TargetParam filter, TargetParam update) override { return vector<EmployeeInfo>{}; }
	vector<EmployeeInfo> DeleteDB(TargetParam filter) override { return vector<EmployeeInfo>{}; }
};

int main(int argc, char* argv[])
{
	auto database = new MemoryDatabase();
	auto printer = new Printer(new AscendingEmployeeNumber(), new FileOutput(argv[2]));
	auto parser = CommandParser();
	auto processor = CommandProcessor((IDatabase *)database, printer);

	vector<string>&& lines = parser.ParseFile(argv[1]);
	vector<Command>&& commands = parser.ParseLine(lines);

	for (auto command : commands) {
		processor.Process(command);
	}

	return 0;
}
