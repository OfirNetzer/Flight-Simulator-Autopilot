//
// Created by Avichai Geldzahler on 11/11/2019.
//

#ifndef EX1B_EX1_H
#define EX1B_EX1_H

#include "Expression.h"
#include "stdio.h"
#include <string>
#include <map>
#include <stack>
#include <vector>

using namespace std;

/** Part 1 */

class BinaryOperator : public Expression {
protected:
    Expression* left;
    Expression* right;
public:
    BinaryOperator(Expression *left1, Expression *right1);
};

class UnaryOperator : public Expression {
protected:
    Expression* exp;
public:
    UnaryOperator(Expression *exp1);
};

class Value : public Expression {
    double val;
public:
    double getVal() const;

    Value(double val1);

    double calculate();
};

class Variable: public Expression {
private:
    string name;
    double value;

public:
    Variable(const string &name1, double value1);
    void setValue(double valueV);
    const string &getName() const;
    double calculate();
    Variable& operator ++ ();
    Variable& operator -- ();
    Variable& operator -= (double);
    Variable& operator += (double);
    Variable& operator ++ (int);
    Variable& operator -- (int);
};

class Plus : public BinaryOperator {
public:
    Plus(Expression *left1, Expression *right1);

    virtual ~Plus();

    double calculate();
};

class Minus : public BinaryOperator {
public:
    Minus(Expression *left1, Expression *right1);

    virtual ~Minus();

    double calculate();
};

class Mul : public BinaryOperator {
public:
    Mul(Expression *left1, Expression *right1);

    virtual ~Mul();

    double calculate();
};

class Div : public BinaryOperator {
public:
    Div(Expression *left1, Expression *right1);

    virtual ~Div();

    double calculate();
};

class UPlus : public UnaryOperator {
public:
    UPlus(Expression *exp);

    virtual ~UPlus();

    double calculate();
};

class UMinus : public UnaryOperator {
public:
    UMinus(Expression *exp);

    virtual ~UMinus();

    double calculate();
};

/** Part 2 */

class Interpreter {
public:
    virtual ~Interpreter();

private:
    stack <char> opers;
    stack <double> nums;
    map<string, double> varMap;
public:
    Expression* interpret(const string infix);
    void setVariables(string vars);
    bool infixIsValid(string infix);
    bool varsAreValid(string var);
    bool isHigherPrec(char c);
    bool isOperator(char c);
    bool isValidSign(char c);
    bool twoOpsInaRow(char current, char last);
    void calc();
    double calcBin(double numA, double numB, char opera);
    double calcUn(double num, char opera);
};

#endif //EX1B_EX1_H