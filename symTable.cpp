//
// Created by ofirn93 on 24/12/2019.
//
using namespace std;
#include "symTable.h"
#include "OpenServerCommand.h"
#include "Mutex.h"
#include <mutex>
#include <sys/socket.h>
#include <iostream>
mutex mutexx;

/*
 * a function that creates a new variable and stores it in the two maps
 * by name and by sim (which is the location of each variable in the server.
 * */
void symTable::addVar(string n, string s, string d, float v) {
    symTable* symTable = symTable::getInstance();
    Var* var = new Var(n,s,d,v);
    symTable->uiMap.insert({n,var});
    // if direction is not "=" then it is ->|<- , insert it to the siMap
    if (d != "=") {
        symTable->siMap.insert({s,var});
    }
    if (d == "->" || d == "=") {
        symTable::command2client(var);
    }

}

/*
 * a function that updates an existing variable value with a new value.
 * we are using mutex so only one thread will be able to reach it at a time.
 * */
void symTable::setVar(string n, float v) {
    mutexx.try_lock();
    bool inMapFlag = false;
    if (this->uiMap.find(n) != this->uiMap.cend()) {
        this->uiMap.find(n)->second->setVal(v);
        this->uiMap[n]->setVal(v);
        inMapFlag = true;
    }
    auto end = this->uiMap.cend();
    if (this->siMap.find(n) != end) {
        this->siMap[n]->setVal(v);
        inMapFlag = true;
    }
    if (!inMapFlag) {
        throw runtime_error("var: " + n + "not exists");
    }
    mutexx.unlock();
}

// a function that send the command to update a variable value in the server
void symTable::command2client(Var *var) {
    string c2cStr = "set ";
    c2cStr.append(var->getSim() + " " +  to_string(var->getVal()) + "\r\n");
    int is_sent = send(this->clientSocketFD, c2cStr.c_str(), c2cStr.length(), 0);
    if (is_sent == -1) {
        cout << "Error while sending data to simulator from client" << endl;
    }
}

// a function that returns a var from siMap using given a relevant key
Var* symTable::getSiVar(string key) {
    auto it = this->siMap.find(key);
    if (it != this->siMap.cend()){
        return this->siMap.at(key);
    }
    return nullptr;
}