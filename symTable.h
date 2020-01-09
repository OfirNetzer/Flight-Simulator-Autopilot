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
public:
    // we keep the client socket as a member
    int clientSocketFD;
public:
    /* two maps that stores our same variables with different keys
     * siMap keys are the sim which is the location of each variable in the server
     * uiMap keys are the name of each variable.*/
    unordered_map<string, Var*> siMap;
    unordered_map<string, Var*> uiMap;
    // singleton instance
    static symTable* getInstance() {
        if (instance == nullptr) {
            instance = new symTable();
        }
        return instance;
    }
    // a function that creates a new var and send it to the maps
    void addVar(string n, string s, string d, float v);
    // a function that updates an existing variable value
    void setVar(string n, float v);
    // a function that send the command to update a variable value in the server
    void command2client(Var* var);
    // a function that returns a var from siMap using given a relevant key
    Var* getSiVar(string key);

};

#endif //EX3_SYMTABLE_H