//
// Created by ofirn93 on 24/12/2019.
//

#ifndef EX3_SYMTABLE_H
#define EX3_SYMTABLE_H
using namespace std;
#include <unordered_map>
#include "Var.h"
//#include "Mutex.h"
#include <mutex>

//singleton thread safe pattern is from: https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
// todo - change the static to fit
class symTable {
private:
    static symTable* instance;
    mutex mutexx;
public:
    int clientSocketFD;

public:
    unordered_map<string, Var*> siMap;
    unordered_map<string, Var*> uiMap;
    static symTable* getInstance() {
        if (instance == nullptr) {
            instance = new symTable();
        }
        return instance;
    }
    void addVar(string n, string s, string d, double v);
    void setVar(string n, double v);
    void command2client(Var* var);
    Var* getSiVar(string key);
};

#endif //EX3_SYMTABLE_H
