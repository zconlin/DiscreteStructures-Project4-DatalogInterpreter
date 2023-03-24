cmake_minimum_required(VERSION 3.23)
project(CS236Project4-DatalogInterpreter)

set(CMAKE_CXX_STANDARD 17)

add_executable(CS236Project4-DatalogInterpreter main.cpp DatalogProgram.h Rule.h Predicate.h Parameter.h Scheme.h Tuple.h Relation.h Interpreter.h Database.h)