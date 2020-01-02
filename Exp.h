//
// Created by avichai on 02/01/2020.
//

#ifndef EX3_EXP_H
#define EX3_EXP_H

#include <string>
#include <iostream>
#include "ex1.h"

using namespace std;

class Exp {
public:
    static double inter(string str) {
        Interpreter* in = new Interpreter();
        Expression* e = nullptr;
        try {
            e = in->interpret(str);
            double ans = e->calculate();
            delete in;
            delete e;
            return ans;
        } catch (const char* e) {
            cerr << "Problem with interpreting" << endl;
            if (e != nullptr) {
                delete e;
            }
        }
        return 0;
    }
};


#endif //EX3_EXP_H
