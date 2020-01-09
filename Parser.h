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
    // we keep the index of our iterations over the lexer vector as a member of our parser
    int ind;
public:
    // see explanation in the cpp file
    Parser();
    void run(vector<string> lexerCommands);
};


#endif //EX3_PARSER_H
