//
// Created by ofirn93 on 23/12/2019.
//
using namespace std;
#include "DefineVarCommand.h"
#include "symTable.h"
#include "Exp.h"

/* before this in the parser:
 * i'll iterate over the lexer vector.
 * i'll generate a new vector that starts (vector[0]) from the current var
 * https://stackoverflow.com/questions/421573/best-way-to-extract-a-subvector-from-a-vector
 * and send it to this func
 * in this func i'll decide what kind of var is it (var -> || var = )
 * this way i'll treat the vars i have the right way
 * */
int DefineVarCommand::execute(vector<string> myLex, int i) {
    symTable* symTable = symTable::getInstance();
    // if the vector starts with var, it's var -> type
    if (!(myLex.at(i).compare("var"))) {
        string name = myLex.at(i+1);
        string direction = myLex.at(i+2);
        string sim = myLex.at(i+4);
        if (direction == "=") {
            double val = Exp::inter(sim);
            symTable::getInstance()->addVar(name, sim, "->", val);
            symTable::getInstance()->command2client(symTable->uiMap.at(name));
            return 4;
        }
        symTable::getInstance()->addVar(name, sim, direction, 0);
        symTable::getInstance()->command2client(symTable->uiMap.at(name));
        return 5;
    }
    // if it's not starting with "var" it should be already exist
    /*if (((myLex.at(i).compare("var") != 0 ) && (myLex.at(i+1).compare("=") == 0))) {
        string name = myLex.at(i);
        string strVal = myLex.at(i+2);
        // old execution
//        double val = stod(strVal);
        double val;
        if (symTable::getInstance()->uiMap.at(strVal)) {
            val = symTable::getInstance()->uiMap.at(strVal)->getVal();
        } else {
            val = Exp::inter(strVal);
        }
        symTable::getInstance()->setVar(name, val);
        return 3;
    }
    if (((myLex.at(i).compare("var") != 0 ) && (myLex.at(i+1).compare("+=") == 0))) {

    }
    if (((myLex.at(i).compare("var") != 0 ) && (myLex.at(i+1).compare("-=") == 0))) {

    }*/

    // if it's not starting with "var" it should be already exist
    if (myLex.at(i) != "var" ) {
        string name = myLex.at(i);
        string strRight = myLex.at(i+2);
        double right, var;
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
        /*if (myLex.at(i+1) == "+=") {
            var = symTable::getInstance()->uiMap.at(name)->getVal();
            var += right;
            symTable::getInstance()->setVar(name, var);
            return 3;
        }
        if (myLex.at(i+1) == "-=") {
            var = symTable::getInstance()->uiMap.at(name)->getVal();
            var -= right;
            symTable::getInstance()->setVar(name, var);
            return 3;
        }*/
    }
    // todo handle info that comes from the server (like the XML)
    return 0;
}

