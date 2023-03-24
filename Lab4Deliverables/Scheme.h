//
// Created by zacco on 3/3/2023.
//

#ifndef CS236PROJECT4_DATALOGINTERPRETER_SCHEME_H
#define CS236PROJECT4_DATALOGINTERPRETER_SCHEME_H

#include <vector>

class Scheme : public vector<string> {

public:
    Scheme() = default;
    Scheme(vector<string> names) : vector<string>(names) { }

//    void setName(int index, string newName) {
//        this-> names.at(index) = newName;
//    }
};

#endif //CS236PROJECT4_DATALOGINTERPRETER_SCHEME_H
