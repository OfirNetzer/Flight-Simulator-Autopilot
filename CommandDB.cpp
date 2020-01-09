//
// Created by ofirn93 on 31/12/2019.
//

#include "CommandDB.h"

// func that adds a command to the map with a string key that represent the command
// (for example key = "Print", Command = PrintCommand)
void CommandDB::addCommand(string varName, Command *command) {
    this->commandTable[varName] = command;
}

// func that get a command name and returns pointer to this command, if it exists in the map.
// otherwise in reutrns null
Command *CommandDB::getCommand(string CommandName) {
    if (this->commandTable.count(CommandName) == 1) {
        return this->commandTable[CommandName];
    }
    else{
        return nullptr;
    }
}
