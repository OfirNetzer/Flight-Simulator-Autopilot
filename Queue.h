//
// Created by avichai on 31/12/2019.
//

#ifndef EX3_QUEUE_H
#define EX3_QUEUE_H

#include <queue>
#include <string>

using namespace std;

class Queue {
private:
    static Queue* instance;
public:
    queue<string> q;
    static Queue* getInstance() {
        if (instance == nullptr) {
            instance = new Queue();
        }
        return instance;
    }
};


#endif //EX3_QUEUE_H
