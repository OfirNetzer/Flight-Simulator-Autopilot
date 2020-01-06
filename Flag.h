//
// Created by avichai on 31/12/2019.
//

#ifndef EX3_FLAG_H
#define EX3_FLAG_H

#include <mutex>
#include "Mutex.h"

using namespace std;
//mutex mutex_lock;

class Flag {
private:
    static Flag* instance;
public:
    bool threadFlag = true;
    static Flag* getInstance() {
        Mutex::getInstance()->mutex_lock.lock();
        if (instance == nullptr) {
            instance = new Flag();
        }
        Mutex::getInstance()->mutex_lock.unlock();
        return instance;
    }
};


#endif //EX3_FLAG_H
