//
// Created by zconlin on 2/8/2023.
//

#ifndef CS236PROJECT2_DATALOGPARSER_PREDICATE_H
#define CS236PROJECT2_DATALOGPARSER_PREDICATE_H

#include <string>
#include <vector>
#include "Parameter.h"

using namespace std;

class Predicate
{
public:
    Predicate(string value, vector<Parameter> parameterList): parameterList(parameterList), name(value) {}
    Predicate() {}

    vector<Parameter> parameterList;
    string name;

//    void addParameter(Parameter param) {
//        parameterList.push_back(param);
//    }
//
//    void addParameter(vector<Parameter> params) {
//        parameterList.insert(parameterList.end(),params.begin(), params.end());
//    }
    string getName() {
        return name;
    };

    vector<Parameter> getParameterList() {
        return parameterList;
    }

    string toString() {
        stringstream output;
        Parameter savedParameter = parameterList.back();
        parameterList.pop_back();
        output << name << "(";
        for(const auto& i : parameterList) {
            output << i.value << ",";
        }
        output << savedParameter.value << ")";
        return output.str();
    }

};

#endif /* CS236PROJECT2_DATALOGPARSER_PREDICATE_H_ */