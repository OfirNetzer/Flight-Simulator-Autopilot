//
// Created by ofirn93 on 31/12/2019.
//

#ifndef EX3_COMMANDDB_H
#define EX3_COMMANDDB_H

#include <unordered_map>
#include <string>
#include <vector>
#include "Command.h"

using namespace std;


/*
 * a singleton class, created in order to connect between string that represent
 * a command to an actual command instance.
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
