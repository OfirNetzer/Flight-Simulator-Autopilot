//
// Created by ofirn93 on 27/12/2019.
//

#ifndef EX3_VAR_H
#define EX3_VAR_H
using namespace std;
#include <string>


class Var {
private:
    // var name, sim is the directory that comes after the word "sim"
    // dir is the direction and value is the var value
    string name;
    string sim;
    string dir;
    float value;
public:
    // see explanation in cpp
    Var(string n, string s, string d, float v);
    string getName();
    string getSim();
    string getDir();
    float getVal();
    void setVal(float v);
    ~Var() = default;
};


#endif //EX3_VAR_H
