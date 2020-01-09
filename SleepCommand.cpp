//
// Created by ofirn93 on 02/01/2020.
//

#include <thread>
#include "SleepCommand.h"

// a function that force the thread that reach to it to sleep for certain number of milliseconds
int SleepCommand::execute(vector<string> myLex, int i) {
    if (myLex.at(i) == "Sleep") {
        int val = stoi(myLex.at(i+1));
        this_thread::sleep_for(chrono::milliseconds(val));
    }
    return 2;
}
