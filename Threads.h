//
// Created by avichai on 02/01/2020.
//

#ifndef THREADTEST_THREADS_H
#define THREADTEST_THREADS_H

#include <thread>
#include <mutex>
using namespace std;
//mutex mutex_lock;

class Threads {
private:
    static Threads* instance;
public:
    thread server;
    static Threads* getInstance() {
//        mutex_lock.lock();
        if (instance == nullptr) {
            instance = new Threads();
        }
//        mutex_lock.unlock();
        return instance;
    }
};


#endif //THREADTEST_THREADS_H
