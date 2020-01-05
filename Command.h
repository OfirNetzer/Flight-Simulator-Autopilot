//
// Created by ofirn93 on 23/12/2019.
//

#ifndef EX3_COMMAND_H
#define EX3_COMMAND_
#pragma once

#include <string>
#include <vector>

using namespace std;

class Command {
public:
    virtual int execute(vector<string> arr, int ind) = 0;
    virtual ~Command() = default;
};
#endif //EX3_COMMAND_H
