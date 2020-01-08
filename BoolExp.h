//
// Created by ofirn93 on 02/01/2020.
//

#ifndef EX3_BOOLEXP_H
#define EX3_BOOLEXP_H


#include "ex1.h"

class BoolExp: public BinaryOperator {
    string myOperator;
public:
    BoolExp(Expression* left1, string conditionOp, Expression* right1);
    float calculate();

};


#endif //EX3_BOOLEXP_H
