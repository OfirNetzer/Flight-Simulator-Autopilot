//
// Created by ofirn93 on 31/12/2019.
//

#include "CommandDB.h"

const map<string, Command *> &CommandDB::getCommandTable() const {
    return commandTable;
}

// update or add command into map
void CommandDB::addCommand(string varName, Command *command) {
    this->commandTable[varName] = command;
}

Command *CommandDB::getCommand(const string &CommandName) {
    if (this->commandTable.count(CommandName) == 1)
        return this->commandTable[CommandName];
    else
        return nullptr;
}