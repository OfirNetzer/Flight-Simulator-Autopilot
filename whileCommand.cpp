//
// Created by ofirn93 on 03/01/2020.
//

#include "whileCommand.h"
#include "CommandDB.h"
#include "DefineVarCommand.h"


// the execution of a loop command
int whileCommand::runCondition(vector<string> arr, int ind) {
    int i = ind;
    Command* c;
    // first of all we run the inner commands till the end 1 time so we can know how many jumps we will
    // have to make after we finish the loop
    while (arr.at(i) != "}") {
        if (arr.at(i + 1).find("=") != string::npos) {
            c = CommandDB::getInstance()->getCommand("var");
        } else {
            c = CommandDB::getInstance()->getCommand(arr.at(i));
        }
        i += c->execute(arr, i);
    }
    // the number of jumps
    int innerCmdJumps = i - ind;
    // then' we run the loop until the condition is not satisfied
    while (cSatisfied(this->myCondition)) {
        if (arr.at(i) == "}") {
            i = ind;
        }
        if (arr.at(i + 1).find("=") != string::npos) {
            c = CommandDB::getInstance()->getCommand("var");
        } else {
            c = CommandDB::getInstance()->getCommand(arr.at(i));
        }
        i += c->execute(arr, i);
    }
    return innerCmdJumps;
}
