//
// Created by ofirn93 on 02/01/2020.
//

#include <iostream>
#include "PrintCommand.h"
using namespace std;

int PrintCommand::execute(vector<string> myLex, int i) {
    if (myLex.at(i) == "Print") {
        cout << myLex.at(i + 1) << endl;
    }
    return 2;
}
