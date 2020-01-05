//
// Created by ofirn93 on 24/12/2019.
//
using namespace std;
#include "symTable.h"
#include "Queue.h"
#include <mutex>


mutex mutex_lock;

void symTable::addVar(string n, string s, string d, double v) {
    symTable* symTable = symTable::getInstance();
    mutex_lock.lock();
    Var* var = new Var(n,s,d,v);
    symTable->uiMap.insert({n,var});
    // if direction is not "=" then it is ->|<- , insert it to the siMap
    if (d.compare("=") != 0) {
        symTable->siMap.insert({s,var});
    }
    if (d == "->") {
        string c2cStr = this->command2client(var);
        Queue::getInstance()->q.push(c2cStr);
    }
    mutex_lock.unlock();
    //todo maybe delete var
}

void symTable::setVar(string n, double v) {
    mutex_lock.lock();
    // todo - go to the var in the map, and just set its new value.
    bool inMapFlag = false;
    if (this->uiMap.find(n) != this->uiMap.cend()) {
        this->uiMap.find(n)->second->setVal(v);
        inMapFlag = true;
    }
    if (this->siMap.find(n) != this->uiMap.cend()) {
        this->siMap.at(n)->setVal(v);
        inMapFlag = true;
    }
    if (!inMapFlag) {
        throw runtime_error("var: " + n + "not exists");
    }
    mutex_lock.unlock();
}

string symTable::command2client(Var *var) {
    string c2cStr = "set ";
    c2cStr.append(var->getSim() + " " +  to_string(var->getVal()) + "\r\n");
    return c2cStr;
}

