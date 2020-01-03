//
// Created by ofirn93 on 03/01/2020.
//

#include "whileCommand.h"
#include "CommandDB.h"

int whileCommand::runCondition(vector<string> arr, int ind) {
    int i = ind;
    while (arr.at(ind) != "}") {
        Command *c = CommandDB::getInstance()->getCommand(arr.at(ind));
        ind += c->execute(arr, ind);
    }
    // extra jump to skip the "}" sign
    ind++;
    while (cSatisfied(this->myCondition)) {
        if (arr.at(i) == "}") {
            i = ind;
        }
        Command *c = CommandDB::getInstance()->getCommand(arr.at(i));
        i += c->execute(arr, ind);
    }
    return ((int) arr.size() - ind);
}
