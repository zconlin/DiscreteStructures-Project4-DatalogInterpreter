//
// Created by zacco on 3/3/2023.
//

#ifndef CS236PROJECT4_DATALOGINTERPRETER_SCHEME_H
#define CS236PROJECT4_DATALOGINTERPRETER_SCHEME_H

#include <vector>
#include <set>

class Scheme : public vector<string> {

public:

    Scheme(vector<string> names) : vector<string>(names) {}

    Scheme insertScheme(const Scheme &leftScheme, const Scheme &rightScheme) {
        set<string> values;
        values.insert(leftScheme.begin(), leftScheme.end());
        values.insert(rightScheme.begin(), rightScheme.end());

        Scheme returnScheme;
        returnScheme.insert(returnScheme.end(), values.begin(), values.end());
        return returnScheme;
    };
};
#endif //CS236PROJECT4_DATALOGINTERPRETER_SCHEME_H
