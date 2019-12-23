//
// Created by ofirn93 on 19/12/2019.
//

#ifndef EX3_EX1_H
#define EX3_EX1_H
//
// Created by ofirn93 on 18/11/2019.
//

#ifndef TEST1_EX1_H
#define TEST1_EX1_H

#pragma once
#include "Expression.h"
#include <string>
#include <stack>
#include <queue>
#include <map>

using namespace std;

class UnaryOperator:public Expression {
protected:
    Expression* e;
public:
    UnaryOperator(Expression* exp);
    ~UnaryOperator();

};

class BinaryOperator:public Expression {
protected:
    Expression* left;
    Expression* right;
public:
    BinaryOperator(Expression* left1, Expression* right1);
    ~BinaryOperator();

};

class Plus: public BinaryOperator{
public:
    Plus(Expression* left1, Expression* right1);
    double calculate();

};

class Minus: public BinaryOperator{
public:
    Minus(Expression* left1, Expression* right1);
    double calculate();

};

class Mul: public BinaryOperator{
public:
    Mul(Expression* left1, Expression* right1);
    double calculate();

};

class Div: public BinaryOperator{
public:
    Div(Expression* left1, Expression* right1);
    double calculate();

};

class UPlus: public UnaryOperator{
public:
    UPlus(Expression* exp);
    double calculate();

};

class UMinus: public UnaryOperator{
public:
    UMinus(Expression* exp);
    double calculate();

};


class Value: public Expression {
private:
    double val;
public:
    Value (double val1);
    double calculate();
};

class Variable: public Expression {
private:
    string name;
    double value;
public:
    Variable(string name1, double value1);
    double calculate();
    Variable& operator++();
    Variable& operator++(int);
    Variable& operator--();
    Variable& operator--(int);
    Variable& operator+=(double num);
    Variable& operator-=(double num);
};

// part II


class Interpreter {
    stack<string> strStack;
    std:: queue<string> queue;
    stack<Expression*> expStack;
    map<string, double> var_map;
public:
    Interpreter();
    void inf2post(string s);
    int score(string str);
    Expression* rpn(std::queue<string> queue);
    void setVariables(string s);
    bool isValid(string s);
    void send2Map(string s);
    Expression* findInMap(string s);
    Expression* interpret(string s);
    void redefineValInMap(string tok, string val);
};

#endif //TEST1_EX1_H
#endif //EX3_EX1_H
