//
// Created by ofirn93 on 23/12/2019.
//

#ifndef EX3_DEFINEVARCOMMAND_H
#define EX3_DEFINEVARCOMMAND_H

#include "Command.h"

class DefineVarCommand: public Command {
public:
    // run on the lexer from the relevant index and decide how to define the var
    //returns the num of jumps for the next command in the lexer
    DefineVarCommand();
    int execute(vector<string> myLex);
};


#endif //EX3_DEFINEVARCOMMAND_H
