#include "CommandParser.h"
#include <fstream>
#include <sstream>

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
        auto strs = Split_(line, ',');
        auto command = MakeCommand_(strs);
        result.push_back(command);
    }

    return result;
}

vector<string> CommandParser::Split_(string str, const char separator) {
    istringstream iss(str);
    string buffer;
    vector<string> result;

    while (getline(iss, buffer, separator)) {
        result.push_back(buffer);
    }

    return result;
}

Command CommandParser::MakeCommand_(vector<string>& str) {
    Command result;

    return result;
}

