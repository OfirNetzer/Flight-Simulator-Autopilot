//
// Created by ofirn93 on 31/12/2019.
//

#include "CommandDB.h"
CommandDB* CommandDB:: instance = nullptr;

void CommandDB::addCommand(string varName, Command *command) {
    this->commandTable[varName] = command;
}

Command *CommandDB::getCommand(string CommandName) {
    if (this->commandTable.count(CommandName) == 1) {
        return this->commandTable[CommandName];
    }
    else{
        return nullptr;
    }
}
