//
// Created by avichai on 02/01/2020.
//

#ifndef EX3_EXP_H
#define EX3_EXP_H

#include <string>
#include <iostream>
#include <regex>
#include "ex1.h"
#include "symTable.h"

using namespace std;

class Exp {
public:
    static double inter(string str) {
        auto in = new Interpreter();
        Expression* e = nullptr;
        vector<string> vars;
        string variables;
        //parse string into variables and push them into a vector
        for (int j=0; j<str.length(); j++) {
            string token = Substring::create('v', str, &j);
            if (regex_match(token, regex("[a-zA-Z]"))) {
                vars.push_back(token);
            }
        }
        //create a string that contains the variables with their values, e.g. "x=3;y=4;"
        for (string s : vars) {
            string string1 = s + '=' + to_string(symTable::getInstance()->uiMap.at(s)->getVal()) + ';';
            variables += s;
        }
        //give the variables a meaning in the Interpreter object "in"
        in->setVariables(variables);
        try {
            //interpret the whole string, and return it's final value as a double
            e = in->interpret(str);
            double ans = e->calculate();
            delete in;
            delete e;
            return ans;
        } catch (const char* e) {
            cerr << "Problem while interpreting from Exp class" << endl;
            if (e != nullptr) {
                delete e;
            }
        }
        return 0;
    }
};


#endif //EX3_EXP_H
