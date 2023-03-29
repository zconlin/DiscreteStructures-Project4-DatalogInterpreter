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

    // call this after schemes and facts, but before queries
    void evaluateAllQueries() {
        cout << "Query Evaluation" << endl;
        for (auto &query : dl.Queries) {
            evaluateQuery(query);
        }
    }

    Relation evaluateRule(Rule &rule) {
        vector<Relation> relations;
        for (auto &predicate : rule.predicateList) {
            relations.push_back(evaluate(predicate));
        }
        while (relations.size() > 1) {
            Relation first = relations.back();
            relations.pop_back();
            Relation second = relations.back();
            relations.pop_back();
            relations.push_back(first.join(second));
        }
        Relation result = relations.back();
        Scheme headScheme = Scheme();
        for(auto &p : rule.headPredicate.parameterList) {
            headScheme.push_back(p.value);
        }
        result = result.project(headScheme);
        Relation *existingRelation = &db.relations[rule.headPredicate.getName()];
        result = result.rename(existingRelation->scheme);

        Relation newTuples = Relation("newTuples", result.scheme);
        for (auto &t : result.getTuples()) {
            if (!existingRelation->getTuples().count(t)) {
                newTuples.addTuple(t);
            }
        }
        existingRelation->addTuples(newTuples.getTuples());
        cout << rule.toString() << "." << endl;
        for(auto &t : newTuples.getTuples()) {
            cout << t.toString(result.scheme) << endl;
        }
        return newTuples;
    }

    void evaluateAllRules() {
        int numPasses = 0;
        int sizeBefore = 0;
        int sizeAfter = 0;

        cout << "Rule Evaluation" << endl;
        do {
            sizeBefore = db.getSize();
            for (auto &rule : dl.Rules) {
                evaluateRule(rule);
                ++numPasses;
            }
            sizeAfter = db.getSize();
        } while (sizeBefore != sizeAfter);

//        for (auto &rule : dl.Rules) {
//            ++numPasses;
//            evaluateRule(rule);
//        }

        cout << endl << "Schemes populated after " << numPasses
        << " passes through the Rules." << endl << endl;
    }

    Relation evaluate (Predicate &predicate) {
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

        if (result.getTuples().empty()) {

        } else {
            if (!ordering.empty()) {
                Scheme returnScheme = Scheme();
                for (auto &item: ordering) {
                    returnScheme.push_back(rel.scheme.at(mapping[item]));
                }
                result = result.project(returnScheme);
                result = result.rename(Scheme(ordering));
            } else {

            }
        }
        return result;
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
