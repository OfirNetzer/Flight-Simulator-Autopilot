//
// Created by ofirn93 on 31/12/2019.
//

#ifndef EX3_COMMANDDB_H
#define EX3_COMMANDDB_H

#include <map>
#include <string>
#include <vector>
#include "Command.h"

using namespace std;


/*
 * class created in order to store var and their current values.
 */
class CommandDB {
    // db of the commands and their names.
    map<string, Command*> commandTable;

public:
    // getCommand
    const map<string, Command*> &getCommandTable() const;

    void addCommand(string varName, Command* command);

    Command* getCommand(const string &CommandName);


};


#endif //EX3_COMMANDDB_H
