//
// Created by ofirn93 on 24/12/2019.
//

#ifndef EX3_SYMTABLE_H
#define EX3_SYMTABLE_H
using namespace std;
#include <unordered_map>
#include "Var.h"

//singleton thread safe pattern is from: https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
// todo - change the static to fit
class symTable {
    //in case 1
//    static symTable& instance;
    //in case 2
    static symTable* instance;
    unordered_map<string, Var*> uiMap;
    unordered_map<string, Var*> siMap;
    // todo in parser
    string location[36];
public:
    // case 1
    /*
    static symTable& getInstance() {
        static  symTable instance;
        return instance;
    }*/
    // case 2
    static symTable* getInstance() {
        if (instance == nullptr) {
            instance = new symTable();
        }
        return instance;
    }
    void addVar(string n, string s, string d, double v);
    void getVar(string n, double v);
};

#endif //EX3_SYMTABLE_H
