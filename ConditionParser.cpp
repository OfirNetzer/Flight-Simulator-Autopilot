//
// Created by ofirn93 on 02/01/2020.
//

#include "ConditionParser.h"
#include "Exp.h"
#include "BoolExp.h"

using namespace std;

// execution of every Condition Based command (in our code while/if)
int ConditionParser::execute(vector<string> arr, int ind) {
    int i = ind;
    while (arr.at(ind + 1) != "{"){
        this->myCondition.push_back(arr.at(ind + 1));
        ind++;
    }
    ind += 2;
    int jumps = ind - i;
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
    // because we want to get the next value in vector after "}"
    jumps++;
    this->myCondition.clear();
    return jumps;
}


/* a boolean func that checks if the condition of the command is satisfied
 * it returns true if it does, and false otherwise.
 * for example in while loop, it checks if the while condition is satisfied */
bool ConditionParser::cSatisfied(vector<string> arr) {
    int i = 0;
    float left, right;
    string sign, leftStr, rightStr;
    leftStr = arr.at(i);
    rightStr = arr.at(i + 2);
//    if left expression is in the map
    if (symTable::getInstance()->uiMap.find(leftStr) != symTable::getInstance()->uiMap.cend()) {
        left = symTable::getInstance()->uiMap.at(leftStr)->getVal();
    } else {
        left = Exp::inter(leftStr);
    }
    //    if right expression is in the map
    if (symTable::getInstance()->uiMap.find(rightStr) != symTable::getInstance()->uiMap.cend()) {
        right = symTable::getInstance()->uiMap.at(rightStr)->getVal();
    } else {
        right = Exp::inter(rightStr);
    }
    sign = arr.at(i + 1);
    Value* l = new Value(left);
    Value* r = new Value(right);
    BoolExp* e = new BoolExp(l, sign, r);
    if (e->calculate() == 1) {
        return true;
    } else {
        return false;
    }
}
