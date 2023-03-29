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
                result = result.join(result);
                cout << "Yes(" << result.getTuples().size() << ")" << endl;
                cout << result.toString();
            } else {
                cout << "Yes(" << result.getTuples().size() << ")" << endl;
            }
        }
        return result;
    }

    // call this after schemes and facts, but before queries
    void evaluateAllQueries() {
        for (auto &query : dl.Queries) {
            evaluateQuery(query);
        }
    }

    Relation evaluateFact(Predicate &predicate) {
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

    void evaluateAllFacts() {
        int numPasses = 0;
        int sizeBefore = 0;
        int sizeAfter = 0;

        //debug
//        cout << "\n///////////////"
//                "\nshould be:\n"
//                "b(y) :- a(y).\n"
//                "  y='1'\n"
//                "  y='2'\n"
//                "  y='4'\n"
//                "b(y) :- a(y).\n"
//                "//////////////\n\n";

        for (auto &fact : dl.Facts) {
            ++numPasses;
            evaluateFact(fact);
        }
        
        cout << endl << "Schemes populated after " << numPasses
        << " passes through the Rules." << endl << endl;
        // debug; I dont think this actually goes here but now I can see if it runs
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
