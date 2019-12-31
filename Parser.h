//
// Created by ofirn93 on 30/12/2019.
//

#ifndef EX3_PARSER_H
#define EX3_PARSER_H

#include "symTable.h"
#include <vector>
#include <unordered_map>
#include "Command.h"


class Parser {
    unordered_map<string, Command *> commandMap;
public:
    void run(vector<string> lexerCommands);
};


#endif //EX3_PARSER_H
