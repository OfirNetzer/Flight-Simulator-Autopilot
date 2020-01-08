//
// Created by ofirn93 on 02/01/2020.
//

#include <iostream>
#include "PrintCommand.h"
#include "Exp.h"

using namespace std;

int PrintCommand::execute(vector<string> myLex, int i) {
    if (myLex.at(i) == "Print") {
        if (myLex.at(i + 1)[0] == '"') {
            cout << myLex.at(i + 1) << endl;
        } else {
            float val = Exp::inter(myLex.at(i + 1));
            cout << val << endl;
        }
    }
    return 2;
}
