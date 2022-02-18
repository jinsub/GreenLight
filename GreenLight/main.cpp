#include <iostream>
#include "CommandParser.h"
#include "AddCommandProcessor.h"
#include "DelCommandProcessor.h"
#include "SchCommandProcessor.h"
#include "ModCommandProcessor.h"
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

	vector<CommandProcessor*> processors;
	processors.reserve(static_cast<int>(CommandType::Count));
	processors.push_back(new AddCommandProcessor(database));
	processors.push_back(new DelCommandProcessor(database, printer));
	processors.push_back(new SchCommandProcessor(database, printer));
	processors.push_back(new ModCommandProcessor(database, printer));

	vector<string>&& lines = parser.ParseFile(argv[1]);
	vector<Command>&& commands = parser.ParseLine(lines);

	for (auto command : commands) {
		processors[static_cast<int>(command.type_)]->Process(command);
	}

	return 0;
}
