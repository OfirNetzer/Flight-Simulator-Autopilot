//
// Created by ofirn93 on 02/01/2020.
//

#ifndef EX3_PRINTCOMMAND_H
#define EX3_PRINTCOMMAND_H


#include "Command.h"

class PrintCommand: public Command {
public:
    int execute(vector<string> myLex, int i) override;
};


#endif //EX3_PRINTCOMMAND_H
