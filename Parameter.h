//
// Created by zconlin on 2/8/2023.
//

#ifndef CS236PROJECT2_DATALOGPARSER_PARAMETER_H
#define CS236PROJECT2_DATALOGPARSER_PARAMETER_H

#include <string>

using namespace std;

class Parameter
{
public:
    Parameter(string value, bool isID): value(value), isID(isID){}

    string value;
    bool isID;
};

#endif //CS236PROJECT2_DATALOGPARSER_PARAMETER_H
