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

vector<Command> CommandParser::ParseLine(vector<string> lines) {
    vector<Command> result;
    return result;
}

vector<string> CommandParser::_Split(string str, char separator) {
    istringstream iss(str);
    string buffer;
    vector<string> result;

    while (getline(iss, buffer, separator)) {
        result.push_back(buffer);
    }

    return result;
}