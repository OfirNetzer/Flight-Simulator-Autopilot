//
// Created by ofirn93 on 02/01/2020.
//

#ifndef EX3_CONDITIONPARSER_H
#define EX3_CONDITIONPARSER_H


#include "Command.h"

class ConditionParser: public Command {
protected:
    vector<string> myCondition;
public:
    int execute(vector<string> arr, int ind) override ;
    // checks if my condition is satisfied
    bool cSatisfied(vector<string> arr);
    // a virtual method that runs the inner commands of the while/if condition
    virtual int runCondition(vector<string> arr, int ind) = 0;
};


#endif //EX3_CONDITIONPARSER_H
