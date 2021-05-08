#pragma once

#ifndef UTILS_H
#define UTILS_H

#endif // UTILS_H

#include <string>
#include <sstream>
#include <vector>

using namespace std;

namespace utils {

    vector<string> split(string s, char delimiter){
        vector<string> tokens;
        string token;
        istringstream tokenStream(s);
        while (getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

}
