//
// Created by ofirn93 on 27/12/2019.
//
using namespace std;
#include <string>
#include "Var.h"
#include "Mutex.h"


Var::Var(string n, string s, string d, float v) {
    this->name = n;
    this->sim = s;
    this->dir = d;
    setVal(v);
}

void Var::setVal(float v) {
    Mutex::getInstance()->mutex_lock.try_lock();
    this->value = v;
    Mutex::getInstance()->mutex_lock.unlock();
}

string Var::getName() {
    return this->name;
}

string Var::getSim() {
    return this->sim;
}

string Var::getDir() {
    return this->dir;
}

float Var::getVal() {
    return this->value;
}




