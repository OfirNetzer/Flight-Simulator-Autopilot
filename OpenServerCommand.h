//
// Created by ofirn93 on 23/12/2019.
//

#ifndef EX3_OPENSERVERCOMMAND_H
#define EX3_OPENSERVERCOMMAND_H

#include "Command.h"

class OpenServerCommand: public Command {
    int execute(vector<string> arr, int ind);
};

#endif //EX3_OPENSERVERCOMMAND_H
