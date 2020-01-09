//
// Created by ofirn93 on 23/12/2019.
//
using namespace std;
#include "DefineVarCommand.h"
#include "symTable.h"
#include "Exp.h"

/* a command that define what kind of var we are facing.
 * if it's starts with the word "var", then it's a new variable
 * if it doesn't, it's probably an update for an existing variable
 * */
int DefineVarCommand::execute(vector<string> myLex, int i) {
    symTable* symTable = symTable::getInstance();
    // if the vector starts with var, it's var -> type
    if (!(myLex.at(i).compare("var"))) {
        string name = myLex.at(i+1);
        string direction = myLex.at(i+2);
        string sim = myLex.at(i+4).substr(1, myLex.at(i+4).length()-2);
        // if the value of the new var is based on values of variables that already exist in our map
        if (direction == "=") {
            string right = myLex.at(i+3);
            float val = Exp::inter(right);
            symTable::getInstance()->addVar(name, right, "->", val);
            symTable::getInstance()->command2client(symTable->uiMap.at(name));
            return 4;
        }
        symTable::getInstance()->addVar(name, sim, direction, 0);
        symTable::getInstance()->command2client(symTable->uiMap.at(name));
        return 5;
    }

    // if it's not starting with "var", it should be already exist
    if (myLex.at(i) != "var" ) {
        string name = myLex.at(i);
        string strRight = myLex.at(i+2);
        float right, var;
        auto itr = symTable::getInstance()->uiMap.find(name);
        // if it is not in the map or we want to update its value
        if (itr == symTable->uiMap.end() || myLex.at(i+1) == "=") {
            right = Exp::inter(strRight);
        } else {
            right = symTable->uiMap.at(name)->getVal();
        }
        if (myLex.at(i+1) == "=") {
            symTable::getInstance()->setVar(name, right);
            symTable->command2client(symTable->uiMap.at(name));
            return 3;
        }
    }
    return 0;
}

