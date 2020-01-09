//
// Created by ofirn93 on 02/01/2020.
//

#include "BoolExp.h"

BoolExp::BoolExp(Expression* left1, string conditionOp, Expression* right1): BinaryOperator(left1, right1) {
    this->left = left1;
    this->right = right1;
    this->myOperator = conditionOp;
}

/*
 * this function calculates two sides of a boolean expression and returns an iterpreted boolean expression
 * otherwise it raises an error
 * */
float BoolExp::calculate() {
    if (this->myOperator == "==") {
        return left->calculate() == right->calculate();
    }
    if (this->myOperator == "!=") {
        return left->calculate() != right->calculate();
    }
    if (this->myOperator == ">") {
        return left->calculate() > right->calculate();
    }
    if (this->myOperator == "<") {
        return left->calculate() < right->calculate();
    }
    if (this->myOperator == "<=") {
        return left->calculate() <= right->calculate();
    }
    if (this->myOperator == ">=") {
        return left->calculate() >= right->calculate();
    }
    else {
        throw runtime_error(this->myOperator + " Operator is invalid");
    }
}

