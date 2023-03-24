//
// Created by zconlin on 2/8/2023.
//

#ifndef CS236PROJECT2_DATALOGPARSER_RULE_H
#define CS236PROJECT2_DATALOGPARSER_RULE_H

#include "Predicate.h"

using namespace std;

class Rule
{
public:
    Rule(Predicate headPredicate, vector<Predicate> predicateList)
            : headPredicate(headPredicate), predicateList(predicateList) {}
    Rule(){}

    Predicate headPredicate;
    vector<Predicate> predicateList;

    string toString() {
        stringstream output;
        Predicate savedParameter = predicateList.back();
        predicateList.pop_back();
        output << headPredicate.toString() << " :- ";
        for(auto i : predicateList) {
            output << i.toString() + ",";
        }
        output << savedParameter.toString();

        return output.str();
    }

private:
    string value;
};

#endif //CS236PROJECT2_DATALOGPARSER_RULE_H
