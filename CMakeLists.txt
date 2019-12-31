cmake_minimum_required(VERSION 3.15)
project(ex3a)

set(CMAKE_CXX_STANDARD 14)

add_executable(ex3 main.cpp ex1.cpp ex1.h Expression.h
        DefineVarCommand.h DefineVarCommand.cpp OpenServerCommand.cpp OpenServerCommand.h connectCommand.cpp connectCommand.h Lexer.cpp Lexer.h)