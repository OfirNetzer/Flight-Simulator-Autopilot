//
// Created by ofirn93 on 24/12/2019.
//
using namespace std;
#include "symTable.h"
symTable* symTable::instance = nullptr;

void symTable::addVar(string n, string s, string d, double v) {
    Var* var = new Var(n,s,d,v);
    this->uiMap.insert({n,var});
    // if direction is not "=" then it is ->|<- , insert it to the siMap
    if (d.compare("=") != 0) {
        this->siMap.insert({s,var});
    }
    //todo maybe delet evar
}

void symTable::getVar(string n, double v) {
    // todo - go to the var in the map, and just set its new value.
    bool inMapFlag = false;
    if (this->uiMap.at(n) != nullptr) {
        this->uiMap.at(n)->setVal(v);
        inMapFlag = true;
    }
    if (this->siMap.at(n) != nullptr) {
        this->siMap.at(n)->setVal(v);
        inMapFlag = true;
    }
    if (!inMapFlag) {
        throw runtime_error("var: " + n + "not exists");
    }

    /*
    // if direction is "<-" then it  means the var i am looking for is in siMap, otherwise its in uiMap
    if (!(d.compare("<-"))) {
        // find the string n in the si map
    } else {

    }*/
}
