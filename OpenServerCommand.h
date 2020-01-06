//
// Created by avichai on 27/12/2019.
//

#ifndef EX3A_OPENSERVERCOMMAND_H
#define EX3A_OPENSERVERCOMMAND_H

#include <vector>
#include <string>
#include "Command.h"
#include <mutex>

using namespace std;

class OpenServerCommand : public Command {
public:
    static vector<string> createLoc();

    OpenServerCommand();
    int execute(vector<string> lexer, int ind) override;
};


#endif //EX3A_OPENSERVERCOMMAND_H
