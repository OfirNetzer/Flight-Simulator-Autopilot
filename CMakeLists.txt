cmake_minimum_required(VERSION 3.15)
<<<<<<< HEAD
project(ex3)

set(CMAKE_CXX_STANDARD 14)

add_executable(ex3 main.cpp Expression.h ex1.cpp ex1.h Command.h OpenServerCommand.cpp OpenServerCommand.h DefineVarCommand.cpp DefineVarCommand.h symTable.cpp symTable.h Var.h Var.cpp Parser.cpp Parser.h)
=======
project(ex3a)

set(CMAKE_CXX_STANDARD 14)

add_executable(ex3 main.cpp ex1.cpp ex1.h Expression.h
        DefineVarCommand.h DefineVarCommand.cpp OpenServerCommand.cpp OpenServerCommand.h connectCommand.cpp connectCommand.h Lexer.cpp Lexer.h)
>>>>>>> origin/master
