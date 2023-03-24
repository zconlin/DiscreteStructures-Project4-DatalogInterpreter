//
// Created by zconlin on 3/10/2023.
//

#ifndef CS236PROJECT4_DATALOGINTERPRETER_DATABASE_H
#define CS236PROJECT4_DATALOGINTERPRETER_DATABASE_H

#include <map>
#include "Relation.h"
#include "Interpreter.h"

class Database {
public:
    Database(){}
    ~Database(){}

    map<string, Relation> relations;

    Database(vector<Predicate> schemes, vector<Predicate> facts) {
        for (auto &scheme : schemes) {
            vector<string> headers;
            for (auto &parameter: scheme.getParameterList()) {
                headers.push_back(parameter.value);
            }
            Relation relation(scheme.getName(), headers);
            for (auto &fact : facts) {
                if (fact.getName() == scheme.getName()) {
                    vector<string> values;
                    for (auto &parameter : fact.getParameterList()) {
                        values.push_back(parameter.value);
                    }
                    relation.addTuple(values);
                }
            }
            relations[scheme.getName()] = relation;
        }
    }
};

#endif //CS236PROJECT4_DATALOGINTERPRETER_DATABASE_H
