//
// Created by Avichai Geldzahler on 11/11/2019.
//

#include <stdexcept>
#include <stack>
#include <cstring>
#include <vector>
#include <iostream>
#include "ex1.h"

using namespace std;

/** Part 1 */

BinaryOperator::BinaryOperator(Expression *left1, Expression *right1) : left(left1), right(right1) {}

UnaryOperator::UnaryOperator(Expression *exp1) : exp(exp1) {}

double Value::calculate() {
    return val;
}

double Value::getVal() const {
    return val;
}

Value::Value(double val1) : val(val1) {}

double Variable::calculate() {
    return this->value;
}

Variable::Variable(const string &name1, double value1) : name(name1), value(value1) {}

Variable &Variable::operator++() {
    this->value++;
    return *this;
}

Variable &Variable::operator--() {
    this->value--;
    return *this;
}

Variable &Variable::operator-=(double num) {
    this->value -= num;
    return *this;
}

Variable &Variable::operator+=(double num) {
    this->value += num;
    return *this;
}

Variable &Variable::operator++(int) {
    this->value++;
    return *this;
}

Variable &Variable::operator--(int) {
    this->value--;
    return *this;
}

const string &Variable::getName() const {
    return name;
}

void Variable::setValue(double valueV) {
    Variable::value = valueV;
}

double Plus::calculate() {
    return left->calculate() + right->calculate();
}

Plus::Plus(Expression *left1, Expression *right1) : BinaryOperator(left1, right1) {}

Plus::~Plus() {
    if (this->left != nullptr)
        delete(left);
    if (this->right != nullptr)
        delete(right);
}

double Minus::calculate() {
    return left->calculate() - right->calculate();
}

Minus::Minus(Expression *left1, Expression *right1) : BinaryOperator(left1, right1) {}

Minus::~Minus() {
    if (this->left != nullptr)
        delete(left);
    if (this->right != nullptr)
        delete(right);
}

double Mul::calculate() {
    return left->calculate() * right->calculate();
}

Mul::Mul(Expression *left1, Expression *right1) : BinaryOperator(left1, right1) {}

Mul::~Mul() {
    if (this->left != nullptr)
        delete(left);
    if (this->right != nullptr)
        delete(right);
}

double Div::calculate() {
    if (right->calculate() == 0) {
        throw ("division by 0 error");
    } else {
        return left->calculate() / right->calculate();
    }
}

Div::Div(Expression *left1, Expression *right1) : BinaryOperator(left1, right1) {}

Div::~Div() {
    if (this->left != nullptr)
        delete(left);
    if (this->right != nullptr)
        delete(right);
}

double UPlus::calculate() {
    return exp->calculate();
}

UPlus::UPlus(Expression *expp) : UnaryOperator(expp) {}

UPlus::~UPlus() {
    if (this->exp != nullptr)
        delete(exp);
}

double UMinus::calculate() {
    return -(exp->calculate());
}

UMinus::UMinus(Expression *expp) : UnaryOperator(expp) {}

UMinus::~UMinus() {
    if (this->exp != nullptr)
        delete(this->exp);
}

/** Part 2 */

Expression *Interpreter::interpret(const string infix) {
    string temp;
    char lastChar = 0;

    if (!infixIsValid(infix)) {
        throw ("Input is invalid");
    }

    for (unsigned long i=0;  i < infix.length(); i++) {
        char c = infix[i];
        if (c == '_' || isalpha(c)) { // if current token is a variable
            while (infix[i] == '_' || isalpha(infix[i]) || isdigit(infix[i])) {//put the var chars into temp
                temp += infix[i];
                i++;
            }
            i--;
            for (auto& v : varMap) { //find the variable in the variable map, and push its value into the stack
                if (v.first == temp)
                {
                    nums.push(v.second);
                    break;
                }
            }
            temp.clear();
        } else if (isdigit(c) || (c == '.' && isdigit(lastChar))) { //if current token is a number
            while (isdigit(infix[i]) || infix[i] == '.') {
                temp += infix[i];
                i++;
            }
            i--;
            nums.push(stod(temp)); //push the number into the stack
            temp.clear();
        } else { // if current token is an operator
            if (c == ')') { // if current token is ')', calculate everything between that and the closest '('
                while (!opers.empty() && opers.top()!='(') {
                    calc();
                }
                opers.pop(); //pop out the closest '('
            } else if ((i == 0 || lastChar == '(' || lastChar == '/') && (c == '-' || c == '+')) {
                //if '-' or '+' is at the beginning of the infix or after a '(' it's unary
                if (c == '-') {
                    opers.push('$');
                } else { // c == '+'
                    opers.push('#');
                }
            }
            else if (isHigherPrec(c) || c == '(' || opers.empty()) { //last operator was '(' or operator of higher precedence
                opers.push(c);
            } else { // operator is of lesser precedence, calculate last two numbers with last operator
                calc();
                opers.push(c);
            }
        }
        lastChar = c;
    } //end of for loop

    while (!opers.empty()) { // no more chars to search, calculate rest of expression
        calc();
    }

    return new Value(nums.top());
}

void Interpreter::setVariables(string var) {
    bool isValid = true;
    string vName;
    string vValue;
    int pFlag = 0;
    int digFlag = 0;

    if (!varsAreValid(var)) {
        throw ("Invalid Input");
    }

    for (unsigned long i=0; i < var.length(); i++) {
        //parse the string into name and value, and if all is valid, insert to map
        while (var[i] != '=') {
            vName += var[i];
            i++;
        }
        i++;
        if (var[i] == '=') { //meanning there's more than 1 '='
            isValid = false;
            break;
        }
        while (var[i] != ';' && i < var.length()) {
            vValue += var[i];
            i++;
        }

        //if var name starts with number,if value starts with point, or if it's empty - invalid
        if (vValue.empty() || isdigit(vName[0]) || vValue[0] == '.') {
            isValid = false;
            break;
        }
        //check that the right side of the '=' is a double
        for (char t : vValue) {
            if (t == '.') {
                pFlag++;
            } else if (isdigit(t)) {
                digFlag++;
            }
        }
        if (pFlag > 1 || digFlag == 0) {
            isValid = false;
        }

        if (!isValid) {
            break;
        }

        for (auto& j : varMap) { //if var already exists, change its value
            if (j.first == vName) {
                j.second = stod(vValue);
            }
        }

        varMap.insert({vName, stod(vValue)});
        vName.clear();
        vValue.clear();
        pFlag = 0;
        digFlag = 0;
    }

    if (!isValid) {
        throw ("Invalid Input");
    }
}

bool Interpreter::infixIsValid(string infix) {
    int braces = 0;
    char lastChar = 0;
    bool isValid = true;
    for (char i : infix) {
        // if there's any char other than numbers, letters, operators and '_', it isn't valid
        if (!isdigit(i) && !isalpha(i) && !isOperator(i) && !isValidSign(i)) {
            isValid = false;
        } else if (twoOpsInaRow(i, lastChar)) { //two operators can't come one after the other
            isValid = false;
        }
        if (i == '(' || i == ')') {
            braces++;
        } else if ((!isdigit(i) && lastChar == '.') || (i == '.' && !isdigit(lastChar))) { //'.' has to be middle of num
            isValid = false;
        }
        lastChar = i;
    }
    if (braces%2 != 0) { // an odd number of braces means there isn't a ')' for every '(' and vice versa
        isValid = false;
    }
    if (!isValid) {
        throw ("Invalid Input");
    } else {
        return true;
    }
}

bool Interpreter::varsAreValid(string var){
    for (char m : var) {
        if (!isdigit(m) && !isalpha(m) && !isOperator(m) && !isValidSign(m) && m != ';' && m != '=') {
            return false;
        }
    }
    return true;
}

bool Interpreter::isHigherPrec(char c) {
    if (opers.empty()) {
        return true;
    }
    char op = opers.top();
    if (c == '+' || c == '-') {
        if (op == '+' || op == '-' || op == '*' || op == '/' || op == '$' || op == '#') {
            return false;
        } else {
            return true;
        }
    } else if (c == '*' || c == '/') {
        if (op == '*' || op == '/') {
            return false;
        } else {
            return true;
        }
    } else {
        return true;
    }
}

void Interpreter::calc() {
    double rightLocal = 0;
    double leftLocal = 0;
    char opera = opers.top();
    opers.pop();
    if (opera == '$' || opera == '#') { // if operator is unary minus or unary plus
        rightLocal = nums.top();
        nums.pop();
        nums.push(calcUn(rightLocal, opera));
    } else { // if operator is binary
        rightLocal = nums.top();
        nums.pop();

        leftLocal = nums.top();
        nums.pop();

        nums.push(calcBin(leftLocal, rightLocal, opera));
    }
}

double Interpreter::calcUn(double num, char opera) {
    if (opera == '$') {
        return -num;
    } else { // opera == '#'
        return num;
    }
}

double Interpreter::calcBin(double numA, double numB, char opera) {
    if (opera == '+') {
        return numA + numB;
    } else if (opera == '-') {
        return numA - numB;
    } else if (opera == '*') {
        return numA * numB;
    } else { //opera == '/'
        if (numB == 0) {
            throw ("division by 0");
        }
        return numA / numB;
    }
}

bool Interpreter::isOperator(char c) {
    if (c == '-' || c == '+' || c == '/' || c == '*') {
        return true;
    } else {
        return false;
    }
}

bool Interpreter::isValidSign(char c) {
    if (c == '.' || c == '(' || c == ')' || c== '_') {
        return true;
    } else {
        return false;
    }
}

bool Interpreter::twoOpsInaRow(char current, char last) {
    return (current == '+' || current == '-' || current == '*' || current == '/') &&
    (last == '+' || last == '-' || last == '*' || last == '/');
}

Interpreter::~Interpreter() = default;