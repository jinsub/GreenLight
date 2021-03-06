#include "CommandParser.h"
#include <fstream>
#include "StrSplitter.h"

using namespace std;

vector<string> CommandParser::ParseFile(const string inputFile) {
    vector<string> result;

    string buf;
    ifstream file(inputFile);
    while (getline(file, buf)) {
        result.push_back(buf);
    }

    return result;
}

vector<Command> CommandParser::ParseLine(vector<string>& lines) {
    vector<Command> result;

    for (auto line : lines) {
        auto strs = StrSplitter::Split(line, ',');
        auto command = MakeCommand_(strs);
        result.push_back(command);
    }

    return result;
}

Command CommandParser::MakeCommand_(const vector<string>& str) {
    Command result;
    result.type_ = GetCommandType_(str[static_cast<int>(CmdIndex::CmdType)]);
    if (result.type_ == CommandType::INVALID) { return result; }

    if (result.type_ == CommandType::ADD) {
        result.filterOption_ = FilterOption::None;
    } else {
        auto filterOption = str[static_cast<int>(CmdIndex::Opt2)];
        auto filterField = str[static_cast<int>(CmdIndex::Filter)];
        result.filterOption_ = GetFilterOption_(filterOption, filterField);
    }

    result.printOption_ = GetPrintOption_(str[static_cast<int>(CmdIndex::Opt1)]);

    for (int index = static_cast<int>(CmdIndex::ArgStart); index < str.size(); index++) {
        result.arguments_.push_back(str[index]);
    }

    return result;
}

CommandType CommandParser::GetCommandType_(const string& commandType) {
    if (commandType == "ADD") { return CommandType::ADD; }
    if (commandType == "DEL") { return CommandType::DEL; }
    if (commandType == "SCH") { return CommandType::SCH; }
    if (commandType == "MOD") { return CommandType::MOD; }

    // TODO : logging code here
    return CommandType::INVALID;
}

PrintOption CommandParser::GetPrintOption_(const string& printOption) {
    if (printOption == " ") { return PrintOption::PrintCount; }
    if (printOption == "-p") { return PrintOption::PrintLines; }

    // TODO : logging code here
    return PrintOption::Invalid;
}

FilterOption CommandParser::GetFilterOption_(const string& filterOption, const string& filterField) {
    if (filterOption == " ") { return FilterOption::None; }

    if (filterOption == "-f" && filterField == "name") { return FilterOption::FirstName; }
    if (filterOption == "-l" && filterField == "name") { return FilterOption::LastName; }
    if (filterOption == "-m" && filterField == "phoneNum") { return FilterOption::MiddlePhoneNum; }
    if (filterOption == "-l" && filterField == "phoneNum") { return FilterOption::LastPhoneNum; }
    if (filterOption == "-y" && filterField == "birthday") { return FilterOption::BirthdayYear; }
    if (filterOption == "-m" && filterField == "birthday") { return FilterOption::BirthdayMonth; }
    if (filterOption == "-d" && filterField == "birthday") { return FilterOption::BirthdayDay; }

    // TODO : logging code here
    return FilterOption::Invalid;
}
