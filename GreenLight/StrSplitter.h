#pragma once
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class StrSplitter {
public:
	static vector<string> Split(const string str, const char separator) {
        istringstream iss(str);
        string buffer;
        vector<string> result;

        while (getline(iss, buffer, separator)) {
            result.push_back(buffer);
        }

        return result;
	}
};