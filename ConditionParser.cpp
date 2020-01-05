//
// Created by ofirn93 on 02/01/2020.
//

#include "ConditionParser.h"
#include "Exp.h"
#include "BoolExp.h"

using namespace std;

int ConditionParser::execute(vector<string> arr, int ind) {
    while (arr.at(ind + 1) != "{"){
        this->myCondition.push_back(arr.at(ind + 1));
        ind++;
    }
    int jumps = arr.size() - ind;
    // checks if the condition is satisfied
    bool cCheck = cSatisfied(this->myCondition);
    if (cCheck) {
        jumps += runCondition(arr, ind);
    } else {
        while (arr.at(ind) != "}") {
            ind++;
            jumps++;
        }
    }
    return jumps;
}

bool ConditionParser::cSatisfied(vector<string> arr) {
    int i = 0;
    double left, right;
    string sign;
    /*while (i < arr.size()) {
        left = Exp::inter(arr.at(i));
        sign = Exp::inter(arr.at(i + 1));
        right = Exp::inter(arr.at(i + 2));
    }*/
    left = Exp::inter(arr.at(i));
    sign = arr.at(i + 1);
    right = Exp::inter(arr.at(i + 2));
    Value* l = new Value(left);
    Value* r = new Value(right);
    BoolExp* e = new BoolExp(l, sign, r);
    if (e->calculate() == 1) {
        return true;
    } else {
        return false;
    }
}
