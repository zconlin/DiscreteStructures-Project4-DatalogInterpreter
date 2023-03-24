//
// Created by zacco on 3/3/2023.
//

#ifndef CS236PROJECT4_DATALOGINTERPRETER_TUPLE_H
#define CS236PROJECT4_DATALOGINTERPRETER_TUPLE_H

#include <vector>
#include "token.h"

class Tuple : public vector<string> {
public:
    Tuple(vector<string> values) : vector<string>(values) { }

    string toString(const Scheme& scheme) const {
        Tuple values = Tuple(*this);
        stringstream out;

        string save = values.back();
        values.pop_back();

        out << "  ";
        for (unsigned int i = 0; i < values.size(); ++i) {
            out << scheme.at(i);
            out << "=";
            out << values.at(i);
//            if (i < scheme.size() - 1) {
                out << ", ";
//            }
        }
        out << scheme.at(values.size()) << "=" << save;
        return out.str();
    }
};

#endif //CS236PROJECT4_DATALOGINTERPRETER_TUPLE_H
