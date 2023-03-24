//
// Created by zconlin on 1/27/2023.
//

#include "scanner.h"
#include "token.h"
#include "parser.h"
#include "Scheme.h"
#include "Tuple.h"
#include "Relation.h"
#include "Interpreter.h"
#include <iostream>
#include <fstream>

int main() { // Part 2
    Relation studentRelation("students", Scheme( {"ID", "Name", "Major"} ));
    vector<string> studentValues[] = {
            {"'42'", "'Ann'", "'CS'"},
            {"'64'", "'Ned'", "'EE'"},
    };
    studentRelation.join(studentRelation);

    Relation courseRelation("courses", Scheme( {"ID", "Course"} ));
    vector<string> courseValues[] = {
            {"'42'", "'CS 100'"},
            {"'32'", "'CS 232'"},
    };

    for (auto& value : studentValues)
        studentRelation.addTuple(Tuple(value));
    for (auto& value : courseValues)
        courseRelation.addTuple(Tuple(value));

    studentRelation.join(courseRelation);
}

//int main() { // Part 1
//
//    Scheme scheme1( { "A", "B" } );
//    Scheme scheme2( { "B", "C" } );
//    Scheme scheme3( { "X", "Y" } );
//    Scheme scheme4( { "X", "Y", "Z" } );
//
//    Tuple tuple1( {"'1'", "'2'"} );
//    Tuple tuple2( {"'3'", "'4'"} );
//    Tuple tuple3( {"'1'", "'4'"} );
//    Tuple tuple4( {"'1'", "'2'", "'4'"} );
//
//    cout << Relation::joinable(scheme1, scheme2, tuple1, tuple2) << endl << endl;
//    cout << Relation::joinable(scheme2, scheme3, tuple1, tuple2) << endl << endl;
//    cout << Relation::joinable(scheme3, scheme4, tuple1, tuple4) << endl << endl;
//    cout << Relation::joinable(scheme3, scheme4, tuple3, tuple4) << endl;
//}

//int main (int argc, char* argv[]) { // End of project 3
//    ifstream f;
//    f.open(argv[1]);
//
//    string content((istreambuf_iterator<char>(f)), (istreambuf_iterator<char>()));
//
//    Scanner s = Scanner(content);
//    vector<Token> t = s.scanLoop();
//
//    Parser p = Parser(t);
//
//    try {
//        DatalogProgram dp = p.datalogProgram();
//        Interpreter i = Interpreter(dp);
//
//        i.evaluateAllQueries();
//    }
//    catch (Token error) {
////        cout << "Failure!" << endl;
////        cout << "  " << error.toString() << endl;
//    }
//    return 0;
//}
//
