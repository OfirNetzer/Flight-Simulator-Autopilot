//
// Created by ofirn93 on 02/01/2020.
//

#ifndef EX3_SLEEPCOMMAND_H
#define EX3_SLEEPCOMMAND_H


#include "Command.h"

class SleepCommand: public Command {
public:
    // see explanation in cpp file
    int execute(vector<string> myLex, int i) override;
};


#endif //EX3_SLEEPCOMMAND_H
