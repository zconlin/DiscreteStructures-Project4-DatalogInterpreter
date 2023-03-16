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

int main() {

    Scheme scheme1( { "A", "B" } );
    Scheme scheme2( { "B", "C" } );
    Scheme scheme3( { "X", "Y" } );
    Scheme scheme4( { "X", "Y", "Z" } );

    Tuple tuple1( {"'1'", "'2'"} );
    Tuple tuple2( {"'3'", "'4'"} );
    Tuple tuple3( {"'1'", "'4'"} );
    Tuple tuple4( {"'1'", "'2'", "'4'"} );

    cout << Relation::joinable(scheme1, scheme2, tuple1, tuple2) << endl << endl;
    cout << Relation::joinable(scheme2, scheme3, tuple1, tuple2) << endl << endl;
    cout << Relation::joinable(scheme3, scheme4, tuple1, tuple4) << endl << endl;
    cout << Relation::joinable(scheme3, scheme4, tuple3, tuple4) << endl;

}

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
