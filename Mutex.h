//
// Created by avichai on 06/01/2020.
//

#ifndef EX3_MUTEX_H
#define EX3_MUTEX_H

#include <mutex>

class Mutex {

private:
    static Mutex* instance;
public:
    std::mutex mutex_lock;
    static Mutex* getInstance() {
        if (instance == nullptr) {
            instance = new Mutex();
        }
        return instance;
    }
};


#endif //EX3_MUTEX_H
