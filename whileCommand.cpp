//
// Created by ofirn93 on 03/01/2020.
//

#include "whileCommand.h"
#include "CommandDB.h"
#include "DefineVarCommand.h"

int whileCommand::runCondition(vector<string> arr, int ind) {
    int i = ind;
//    CommandDB* CDB = CommandDB::getInstance();
    Command* c;
    while (arr.at(i) != "}") {
        if (arr.at(i + 1).find("=") != string::npos) {
            c = CommandDB::getInstance()->getCommand("var");
        } else {
            c = CommandDB::getInstance()->getCommand(arr.at(i));
        }
        i += c->execute(arr, i);
    }
    // extra jump to skip the "}" sign
//    ind++;
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
    ind++;
    return ind - i;
}
