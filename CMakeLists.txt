cmake_minimum_required(VERSION 3.15)

project(ex3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(ex3 main.cpp Expression.h ex1.cpp ex1.h Command.h OpenServerCommand.cpp OpenServerCommand.h
        DefineVarCommand.cpp DefineVarCommand.h symTable.cpp symTable.h Var.h Var.cpp Parser.cpp Parser.h
        connectCommand.cpp connectCommand.h Lexer.cpp Lexer.h Substring.h Queue.cpp Queue.h Flag.h CommandDB.h
        CommandDB.cpp PrintCommand.cpp PrintCommand.h SleepCommand.cpp SleepCommand.h ConditionParser.h
        ConditionParser.cpp Exp.h BoolExp.cpp BoolExp.h ifCommand.cpp ifCommand.h whileCommand.cpp whileCommand.h Mutex.cpp Mutex.h)
