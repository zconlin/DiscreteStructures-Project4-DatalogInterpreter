//
// Created by zconlin on 3/10/2023.
//

#ifndef CS236PROJECT4_DATALOGINTERPRETER_INTERPRETER_H
#define CS236PROJECT4_DATALOGINTERPRETER_INTERPRETER_H

#include "Database.h"
#include "parser.h"
#include "Predicate.h"

class Interpreter {
public:
    Interpreter(){}

    Interpreter(const DatalogProgram &program) : dl(program) {
        db = Database(program.Schemes, program.Facts);
    }

    ~Interpreter(){}

    DatalogProgram dl;
    Database db;

    Relation evaluateQuery(Predicate &predicate) {
        Relation rel = db.relations[predicate.getName()];
        map<string, int> mapping;
        vector<string> ordering;
        Relation result = Relation(rel);
        int index = 0;
        for (auto &p: predicate.parameterList) {
            if (!p.isID) {
                result = result.select(index, p.value);
            } else {
                if (mapping.count(p.value)) {
                    int baselineIndex = mapping[p.value];
                    result = result.matchSelect(baselineIndex, index);
                } else {
                    ordering.push_back(p.value);
                    mapping[p.value] = index;
                }
            }
            ++index;
        }
        cout << predicate.toString() << "? ";

        if (result.getTuples().empty()) {
            cout << "No" << endl;
        } else {
            if (!ordering.empty()) {
                Scheme returnScheme = Scheme();
                for (auto &item: ordering) {
                    returnScheme.push_back(rel.scheme.at(mapping[item]));
                }
                result = result.project(returnScheme);
                result = result.rename(Scheme(ordering));
                cout << "Yes(" << result.getTuples().size() << ")" << endl;
                cout << result.toString();
            } else {
                cout << "Yes(" << result.getTuples().size() << ")" << endl;
            }
        }
        return result;
    }

    void evaluateAllQueries() {
        for (auto &query : dl.Queries) {
            evaluateQuery(query);
        }
    }

//    string checkForConstant() { // I think I do this already with isID
//        // test if the first character is a ', if it is then that makes it a constant,
//        // if not it is a variable
//    }

//    Interpreter (const DatalogProgram &dl) : dl(dl) {
//
//    }
};

#endif //CS236PROJECT4_DATALOGINTERPRETER_INTERPRETER_H
