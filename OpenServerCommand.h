//
// Created by avichai on 27/12/2019.
//

#ifndef EX3A_OPENSERVERCOMMAND_H
#define EX3A_OPENSERVERCOMMAND_H

#include <vector>
#include <string>
#include "Command.h"


using namespace std;

class OpenServerCommand : public Command {
    string loc[36];
public:
    OpenServerCommand();
    int execute(vector<string> arr, int ind) override;
    void createLoc();
};


#endif //EX3A_OPENSERVERCOMMAND_H
