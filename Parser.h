//
// Created by ofirn93 on 30/12/2019.
//

#ifndef EX3_PARSER_H
#define EX3_PARSER_H

using namespace std;
#include "symTable.h"
#include <vector>
#include <unordered_map>
#include "Command.h"
#include "CommandDB.h"
#include "OpenServerCommand.h"
#include "DefineVarCommand.h"
#include "connectCommand.h"

class Parser {
//    unordered_map<string, Command*> key2Command;
    int ind;
public:
    // func that matches keys (that should come from the lexer) to a command (that we wrote)
    // it is basically initializes the map once the parser is being created
    Parser();
    void run(vector<string> lexerCommands);
};


#endif //EX3_PARSER_H
