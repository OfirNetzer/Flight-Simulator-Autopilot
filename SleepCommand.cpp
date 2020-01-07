//
// Created by ofirn93 on 02/01/2020.
//

#include <thread>
#include "SleepCommand.h"

int SleepCommand::execute(vector<string> myLex, int i) {
    if (myLex.at(i) == "Sleep") {
        int val = stoi(myLex.at(i+1));
//        this_thread::sleep_for(chrono::milliseconds(val)); //todo get back to this after debugging
        this_thread::sleep_for(chrono::milliseconds(60000));
    }
    return 2;
}
