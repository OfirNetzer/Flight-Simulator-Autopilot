//
// Created by avichai on 02/01/2020.
//

#ifndef THREADTEST_THREADS_H
#define THREADTEST_THREADS_H

#include <thread>
using namespace std;

class Threads {
private:
    static Threads* instance;
public:
    thread server;
    thread client;
    static Threads* getInstance() {
        if (instance == nullptr) {
            instance = new Threads();
        }
        return instance;
    }
};


#endif //THREADTEST_THREADS_H
