//
// Created by ofirn93 on 24/12/2019.
//
using namespace std;
#include "symTable.h"
#include "Queue.h"
#include "OpenServerCommand.h"
#include "Mutex.h"
#include <mutex>
#include <sys/socket.h>
#include <iostream>


void symTable::addVar(string n, string s, string d, double v) {
//    Mutex::getInstance()->mutex_lock.try_lock();
    mutexx.try_lock();
    symTable* symTable = symTable::getInstance();
    Var* var = new Var(n,s,d,v);
    symTable->uiMap.insert({n,var});
    mutexx.unlock();
    mutexx.try_lock();
    // if direction is not "=" then it is ->|<- , insert it to the siMap
    if (d != "=") {
        symTable->siMap.insert({s,var});
    }
    if (d == "->" || d == "=") {
        symTable::command2client(var);
    }
//    Mutex::getInstance()->mutex_lock.unlock();
    //todo maybe delete var
    mutexx.unlock();
}

void symTable::setVar(string n, double v) {
//    Mutex::getInstance()->mutex_lock.try_lock();
    mutexx.try_lock();
    bool inMapFlag = false;
    if (this->uiMap.find(n) != this->uiMap.cend()) {
        this->uiMap.find(n)->second->setVal(v);
        this->uiMap[n]->setVal(v);
        inMapFlag = true;
    }
    mutexx.unlock();
    mutexx.try_lock();
    if (this->siMap.find(n) != this->uiMap.cend()) {
        this->siMap[n]->setVal(v);
        inMapFlag = true;
    }
    if (!inMapFlag) {
        throw runtime_error("var: " + n + "not exists");
    }
//    Mutex::getInstance()->mutex_lock.unlock();
    mutexx.unlock();
}

void symTable::command2client(Var *var) {
//    Mutex::getInstance()->mutex_lock.try_lock();
    mutexx.try_lock();
    string c2cStr = "set ";
    c2cStr.append(var->getSim().substr(1, var->getSim().size()-2) + " " +  to_string(var->getVal()) + "\r\n");
    cout << c2cStr << endl;
    int is_sent = send(this->clientSocketFD, c2cStr.c_str(), c2cStr.length(), 0);
    if (is_sent == -1) {
        cout << "Error while sending data to simulator from client" << endl;
    }
//    Mutex::getInstance()->mutex_lock.unlock();
    mutexx.unlock();
}

Var* symTable::getSiVar(string key) {
    auto it = this->siMap.find(key);
    if (it != this->siMap.end()){
        return new Var("not in map", "not in map", "not in map", -1);
    }
    return this->siMap.at(key);
}
