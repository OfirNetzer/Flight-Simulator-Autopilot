//
// Created by ofirn93 on 23/12/2019.
//
using namespace std;
#include "DefineVarCommand.h"
#include "symTable.h"

/* before this in the parser:
 * i'll iterate over the lexer vector.
 * i'll generate a new vector that starts (vector[0]) from the current var
 * https://stackoverflow.com/questions/421573/best-way-to-extract-a-subvector-from-a-vector
 * and send it to this func
 * in this func i'll decide what kind of var is it (var -> || var = )
 * this way i'll treat the vars i have the right way
 * */
int DefineVarCommand::execute(vector<string> myLex, int i) {
    // if the vector starts with var, it's var -> type
    if (!(myLex.at(i).compare("var"))) {
        string name = myLex.at(i+1);
        string direction = myLex.at(i+2);
        string sim = myLex.at(i+4);
        symTable::getInstance()->addVar(name, sim, direction, 0);
        return 5;
    }
    // if it's not starting with "var" it should be already exist
    if (((myLex.at(i).compare("var") != 0 ) && (myLex.at(i+1).compare("=") == 0))) {
        string name = myLex.at(i);
        string strVal = myLex.at(i+2);
        double val = stod(strVal);
        symTable::getInstance()->setVar(name, val);
        return 3;
    }
    // todo handle info that comes from the server (like the XML)
    return 0;
}

