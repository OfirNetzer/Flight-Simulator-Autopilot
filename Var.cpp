//
// Created by ofirn93 on 27/12/2019.
//
using namespace std;
#include <string>
#include "Var.h"
#include "Mutex.h"

/*
 * var name, sim is the directory that comes after the word "sim"
 * dir is the direction and value is the var value
 */
Var::Var(string n, string s, string d, float v) {
    this->name = n;
    this->sim = s;
    this->dir = d;
    setVal(v);
}

/*
 * a func that changes the current value of a variable with a new value
 * */
void Var::setVal(float v) {
    Mutex::getInstance()->mutex_lock.try_lock();
    this->value = v;
    Mutex::getInstance()->mutex_lock.unlock();
}

// variable name getter
string Var::getName() {
    return this->name;
}

// variable sim (location in the server) getter
string Var::getSim() {
    return this->sim;
}

// variable direction getter
string Var::getDir() {
    return this->dir;
}

// variable value getter
float Var::getVal() {
    return this->value;
}




