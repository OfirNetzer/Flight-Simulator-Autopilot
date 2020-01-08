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
    float val;
public:
    float getVal() const;

    Value(float val1);

    float calculate();
};

class Variable: public Expression {
private:
    string name;
    float value;

public:
    Variable(const string &name1, float value1);
    void setValue(float valueV);
    const string &getName() const;
    float calculate();
    Variable& operator ++ ();
    Variable& operator -- ();
    Variable& operator -= (float);
    Variable& operator += (float);
    Variable& operator ++ (int);
    Variable& operator -- (int);
};

class Plus : public BinaryOperator {
public:
    Plus(Expression *left1, Expression *right1);

    virtual ~Plus();

    float calculate();
};

class Minus : public BinaryOperator {
public:
    Minus(Expression *left1, Expression *right1);

    virtual ~Minus();

    float calculate();
};

class Mul : public BinaryOperator {
public:
    Mul(Expression *left1, Expression *right1);

    virtual ~Mul();

    float calculate();
};

class Div : public BinaryOperator {
public:
    Div(Expression *left1, Expression *right1);

    virtual ~Div();

    float calculate();
};

class UPlus : public UnaryOperator {
public:
    UPlus(Expression *exp);

    virtual ~UPlus();

    float calculate();
};

class UMinus : public UnaryOperator {
public:
    UMinus(Expression *exp);

    virtual ~UMinus();

    float calculate();
};

/** Part 2 */

class Interpreter {
public:
    virtual ~Interpreter();

private:
    stack <char> opers;
    stack <float> nums;
    map<string, float> varMap;
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
    float calcBin(float numA, float numB, char opera);
    float calcUn(float num, char opera);
};

#endif //EX1B_EX1_H