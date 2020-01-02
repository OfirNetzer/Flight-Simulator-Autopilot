cmake_minimum_required(VERSION 3.15)

project(ex3)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(ex3 main.cpp Expression.h ex1.cpp ex1.h Command.h OpenServerCommand.cpp OpenServerCommand.h DefineVarCommand.cpp DefineVarCommand.h symTable.cpp symTable.h Var.h Var.cpp Parser.cpp Parser.h connectCommand.cpp connectCommand.h Lexer.cpp Lexer.h Substring.h Queue.cpp Queue.h Flag.h CommandDB.h CommandDB.cpp Exp.h)
