//
// Created by ofirn93 on 03/01/2020.
//

#include "ifCommand.h"
#include "CommandDB.h"

// runs all the inner commands
int ifCommand::runCondition(vector<string> arr, int ind) {
    int i = ind;
    while (arr.at(ind) != "}") {
        Command *c = CommandDB::getInstance()->getCommand(arr.at(ind));
        ind += c->execute(arr, ind);
    }
    ind++;
    return ind - i;
}