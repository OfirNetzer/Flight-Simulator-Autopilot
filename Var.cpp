//
// Created by ofirn93 on 27/12/2019.
//
using namespace std;
#include <string>
#include "Var.h"


Var::Var(string n, string s, string d, double v) {
    this->name = n;
    this->sim = s;
    this->dir = d;
    setVal(v);
}

void Var::setVal(double v) {
    this->value = v;
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

double Var::getVal() {
    return this->value;
}




