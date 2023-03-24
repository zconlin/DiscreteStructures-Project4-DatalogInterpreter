//
// Created by zconlin on 1/27/2023.
//

#pragma once

#include "token.h"
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Scanner {
private:
    string input;
    int lineAt = 1;
    int pos = 0;

public:
    Scanner(const string &input) : input(input) {}

    Token keywordFinder(char startChar);

    Token scanToken() {
        if (input.empty()) {
            return {END, "", lineAt};
        }
        while (isspace(input.at(0))) {
            if (input.at(0) == '\n') {
                lineAt++;
            }
            input = input.substr(1);
            if (input.empty()) {
                return {END, "", lineAt};
            }
        }
        if (input.at(0) == ',') {
            input = input.substr(1);
            return {COMMA, ",", lineAt};
        } else if (input.at(0) == '.') {
            input = input.substr(1);
            return {PERIOD, ".", lineAt};
        } else if (input.at(0) == '?') {
            input = input.substr(1);
            return {Q_MARK, "?", lineAt};
        } else if (input.at(0) == '(') {
            input = input.substr(1);
            return {LEFT_PAREN, "(", lineAt};
        } else if (input.at(0) == ')') {
            input = input.substr(1);
            return {RIGHT_PAREN, ")", lineAt};
        } else if (input.at(0) == ':') {
            if (input.at(1) == '-') {
                input = input.substr(2);
                return {COLON_DASH, ":-", lineAt};
            } else {
                input = input.substr(1);
                return {COLON, ":", lineAt};
            }
        } else if (input.at(0) == '*') {
            input = input.substr(1);
            return {MULTIPLY, "*", lineAt};
        } else if (input.at(0) == '+') {
            input = input.substr(1);
            return {ADD, "+", lineAt};
        } else if (input.at(0) == '#') {
            pos = 0;
            string commentString = "";
            while (input.at(pos) != '\n') {
                commentString.push_back(input.at(pos));
                input = input.substr(pos + 1);
            }
            return {COMMENT, commentString, lineAt};
        } else if (input.at(0) == '\'') {
            pos = 0;
            int startLine = lineAt;
            string stringString = "";
            stringString.push_back(input.at(0));
            input = input.substr(1);
            while (input.at(0) != '\'') {
                if (input.at(0) == '\n') {
                    lineAt++;
                }
                stringString.push_back(input.at(0));
                input = input.substr(1);
                if (input.empty()) {
                    input.push_back(' ');
                    return {UNDEFINED, stringString, startLine};
                }
            }
            stringString.push_back(input.at(0));
            input = input.substr( 1);
            return {STRING, stringString, startLine};
        } else if (isalpha(input.at(0))) {
            char c = input.at(0);
            input = input.substr(1);
            return keywordFinder(c);
        }
        string v = input.substr(0, 1);
        input = input.substr(1);
        return {UNDEFINED, v, lineAt};
    }

    vector<Token> scanLoop() {
        vector<Token> vectorOfTokens;
        do {
            Token tmp = scanToken();
            if (tmp.getType() != COMMENT) {
                vectorOfTokens.push_back(tmp);
            }
        } while (input.length() != 0);
        return vectorOfTokens;
    }
};

Token Scanner::keywordFinder(char startChar) {
    char cursor = startChar;
    string keywordString;
    keywordString.push_back(cursor);

    if (!isalpha(cursor)) {
        return Token(UNDEFINED, keywordString, lineAt);
    }

    cursor = input.at(0);
    while (isalnum(cursor)) {
        keywordString.push_back(cursor);
        input = input.substr(1);
        cursor = input.at(0);
    }

    if (keywordString == "Schemes") {
        return Token(SCHEMES, keywordString, lineAt);
    }
    if (keywordString == "Facts") {
        return Token(FACTS, keywordString, lineAt);
    }
    if (keywordString == "Rules") {
        return Token(RULES, keywordString, lineAt);
    }
    if (keywordString == "Queries") {
        return Token(QUERIES, keywordString, lineAt);
    }
    return Token(ID, keywordString, lineAt);
}