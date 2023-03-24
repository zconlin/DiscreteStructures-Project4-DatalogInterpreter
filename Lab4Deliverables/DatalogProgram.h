//
// Created by zconlin on 2/8/2023.
//

#ifndef CS236PROJECT2_DATALOGPARSER_DATALOGPROGRAM_H
#define CS236PROJECT2_DATALOGPARSER_DATALOGPROGRAM_H

#include <vector>
#include <set>
#include "Rule.h"
#include "Predicate.h"

using namespace std;

class DatalogProgram
{
public:
    DatalogProgram(vector<Predicate> Schemes, vector<Predicate> Facts, vector<Predicate> Queries, vector<Rule> Rules):
    Schemes(Schemes), Facts(Facts), Queries(Queries), Rules(Rules) {
        Domain = set<string>();
        for (const Predicate &predicate : Facts) {
            for (const Parameter &parameter : predicate.parameterList) {
                if (!parameter.isID) {
                    Domain.insert(parameter.value);
                }
            }
        }
    }
    DatalogProgram(){}
    ~DatalogProgram(){}

    vector<Predicate> Schemes;
    vector<Predicate> Facts;
    vector<Predicate> Queries;
    vector<Rule> Rules;
    set<string> Domain;

    void toString() {
        cout << "Schemes(" << (Schemes.size()) << "):\n";
        for(auto & Scheme : Schemes) {
            cout << "  " << Scheme.toString() << "\n";
        }
        cout << "Facts(" << (Facts.size()) <<  "):\n";
        for(auto & Fact : Facts) {
            cout << "  " << Fact.toString() << ".\n";
        }
        cout << "Rules(" << (Rules.size()) << "):\n";
        for(auto & Rule : Rules) {
            cout << "  " << Rule.toString() << ".\n";
        }
        cout << "Queries(" << (Queries.size()) << "):\n";
        for(auto & Query : Queries) {
            cout << "  " << Query.toString() << "?\n";
        }
        cout << "Domain(" << (Domain.size()) << "):\n";
        for(const string& domainString : Domain) {
                cout << "  " << domainString << "\n";
        }
    }
};

#endif //CS236PROJECT2_DATALOGPARSER_DATALOGPROGRAM_H
