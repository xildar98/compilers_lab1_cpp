cmake_minimum_required(VERSION 3.12)
project(compilers_hw1)

set(CMAKE_CXX_STANDARD 14)

add_executable(main main.cpp tokenizer.cpp lex.cpp parser.cpp)

add_executable(testing my_test.cpp)