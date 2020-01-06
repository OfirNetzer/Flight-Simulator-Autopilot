//
// Created by avichai on 27/12/2019.
//

#ifndef EX3A_CONNECTCOMMAND_H
#define EX3A_CONNECTCOMMAND_H

#include <vector>
#include <string>
#include "Command.h"


using namespace std;

class connectCommand : public Command {
public:
    connectCommand();
    int execute(vector<string> lexer, int ind) override;};


#endif //EX3A_CONNECTCOMMAND_H
