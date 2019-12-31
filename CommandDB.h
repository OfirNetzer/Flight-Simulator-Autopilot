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
    static CommandDB* instance;
    unordered_map<string, Command*> commandTable;

public:
    static CommandDB* getInstance() {
        if (instance == nullptr) {
            instance = new CommandDB();
        }
        return instance;
    }

    void addCommand(string varName, Command* command);

    Command* getCommand(string CommandName);

};


#endif //EX3_COMMANDDB_H
