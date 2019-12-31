//
// Created by avichai on 31/12/2019.
//

#include "Queue.h"
Queue* Queue::instance = nullptr;

const queue<string> &Queue::getQueue() const {
    return q;
}
