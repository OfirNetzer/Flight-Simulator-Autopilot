//
// Created by ofirn93 on 30/12/2019.
//

#ifndef EX3_PARSER_H
#define EX3_PARSER_H

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
public:
    // func that matches keys (that should come from the lexer) to a command (that we wrote)
    // it is basically initializes the map once the parser is being created
    Parser() {
        OpenServerCommand* osc =new OpenServerCommand();
        DefineVarCommand* dvc = new DefineVarCommand();
        connectCommand* cc = new connectCommand();
        CommandDB::getInstance()->addCommand("openDataServer", osc);
        CommandDB::getInstance()->addCommand("openDataServer", dvc);
        CommandDB::getInstance()->addCommand("var", cc);
    }
    void run(vector<string> lexerCommands);
};


#endif //EX3_PARSER_H
