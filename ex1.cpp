//
// Created by ofirn93 on 19/12/2019.
//

#include "ex1.h"
#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <ctype.h>
#include <regex>
#include <map>
#include <cstring>
//#include "Expression.h"

using namespace std;

UnaryOperator:: UnaryOperator(Expression* exp): Expression() {
    this->e = exp;
}

UnaryOperator:: ~UnaryOperator() {
    delete e;
}

BinaryOperator:: BinaryOperator(Expression* left1, Expression* right1): Expression() {
    this->left = left1;
    this->right = right1;
}

BinaryOperator:: ~BinaryOperator() {
    delete left;
    delete right;
}

Plus:: Plus(Expression* left1, Expression* right1): BinaryOperator(left1, right1) {}
double Plus:: calculate() {
    return this->left->calculate() + this->right->calculate();
}

Minus:: Minus(Expression *left1, Expression *right1): BinaryOperator(left1, right1) {}
double Minus:: calculate() {
    return this->left->calculate() - this->right->calculate();
}

Mul:: Mul(Expression *left1, Expression *right1): BinaryOperator(left1, right1) {}
double Mul::calculate() {
    return this->left->calculate() * this->right->calculate();
}

Div::Div(Expression *left1, Expression *right1): BinaryOperator(left1, right1) {}
double Div::calculate() {
    if (this->right->calculate() != 0){
        return (this->left->calculate() / this->right->calculate());
    }
    else{
//       cout << "Can't Divide in 0!" << endl;
        throw ("Division by zero");
    }
}

UPlus::UPlus(Expression *exp) : UnaryOperator(exp){}
double UPlus::calculate() {
    return this->e->calculate();
}

UMinus::UMinus(Expression *exp) : UnaryOperator(exp) {}
double UMinus::calculate() {
    return (this->e->calculate()) * (-1);
}

Value:: Value(double val1) : val(val1) {}
double Value:: calculate() {
    return this->val;
}

Variable:: Variable(string name1, double value1): Expression() {
    this->name = name1;
    this->value = value1;
}
double Variable:: calculate(){
    return this->value;
}

Variable& Variable:: operator++(){
    this->value++;
    return *this;
}

Variable& Variable:: operator--(){
    this->value--;
    return *this;
}


Variable& Variable:: operator++(int){
    this->value++;
    return *this;
}

Variable& Variable:: operator--(int){
    this->value--;
    return *this;
}

Variable& Variable:: operator+=(double num) {
    double newVal = this->value + num;
    this->value = newVal;
    return *this;
}

Variable& Variable:: operator-=(double num) {
    double newVal = this->value - num;
    this->value = newVal;
    return *this;
}

//part II

Interpreter::Interpreter() {
//    this->queue;
}
void Interpreter::inf2post(string s) {
    unsigned int i = 0;
    string tmp = "";
    int flag = 0 ;
    // tells me if part of the string was the create we accept. if it doesn't, we throw error.
    bool been = false;
    while (i < s.length()){
        // number
        if (isdigit(s[i])) {
            // reset the flags and the tmp string
            been = true;
            flag = 0;
            tmp = "";
            while (isdigit(s[i]) && flag <= 1) {
                tmp += s[i];
                i++;
                if (s[i] == '.') {
                    tmp += s[i];
                    flag++;
                    i++;
                }
            }
            if (flag > 1) {
                throw "Invalid input";
            }
            // push it to the queue
            this->queue.push(tmp);
            tmp = "";
        }
        //operator
        if (s[i] == '+' || s[i] == '-' || s[i] == '/' || s[i] == '*') {
            been = true;
            if (s[i+1] == '+' || s[i+1] == '-' || s[i+1] == '/' || s[i+1] == '*') {
                throw "Invalid input";
            }
            // when it's an unary
            if (i == 0 || s[i-1] == '(') {
                if (s[i] == '-') {
                    this->strStack.push("!");
                }
                if (s[i] == '+'){
                    this->strStack.push("@");
                }
            }
                // when it's binary (from score = 1 or 2)
            else {
                // if (s[i] == ('/' || '*' || '+' )) {
                tmp += s[i];
                if (this->strStack.empty() || score(this->strStack.top()) < score(tmp)){
                    this->strStack.push(tmp);
                }
                else  {
                    while (!(this->strStack.empty()) && (score(this->strStack.top()) >= score(tmp))) {
                        this->queue.push(this->strStack.top());
                        this->strStack.pop();
                    }
                    this->strStack.push(tmp);
                }
            }
            tmp = "";
        }
        // brackets opener
        if (s[i] == '(') {
            been = true;
            this->strStack.push("(");
        }
        // brackets closure
        if (s[i] == ')') {
            been = true;
            while (this->strStack.top().compare("(")) {
                this->queue.push(this->strStack.top());
                this->strStack.pop();
            }
            if (this->strStack.empty()) {
                throw "Invalid input";
            }
            if ((this->strStack.top().compare("(")) + 1 == 1) {
                this->strStack.pop();
            }
        }
        // variable
        if (isalpha(s[i]) || s[i] == '_') {
            been = true;
            bool exist = false;
            while (isalpha(s[i]) || s[i] == '_') {
                tmp += s[i];
                i++;
            }
            i--;
            map<string, double>::iterator itr;
            for (itr = this->var_map.begin(); itr != this->var_map.end(); ++itr) {
                if (!(itr->first.compare(tmp))) {
                    exist = true;
                    this->queue.push(itr->first);
                }
            }
            if (exist == false){
                throw "Error!";
            }
            tmp = "";
        }
        if (been == false) {
            throw "Invalid input";
        }
        tmp = "";
        i++;
        flag = 0;
        been = false;
    }
    if (!(this->strStack.empty())){
        this->queue.push(this->strStack.top());
        this->strStack.pop();
    }
}

int Interpreter::score(string str) {
    if (!(str.compare("("))){
        return 0;
    }
    if ((!(str.compare("+"))) || (!(str.compare("-")))){
        return 1;
    }
    if ((!(str.compare("*"))) || (!(str.compare("/")))){
        return 2;
    }
    if (!(str.compare(")"))) {
        return 3;
    }
    if ((!(str.compare("!"))) || (!(str.compare("@")))){
        return 4;
    }
        // in case of invalid input
    else {
        return -1;
    }
}

Expression* Interpreter:: rpn(std::queue<string> rpn_queue) {
    while (!(rpn_queue.empty())) {
        // number
        if (isdigit(rpn_queue.front()[0])) {
            double val = stod(rpn_queue.front());
            this->expStack.push(new Value(val));
            rpn_queue.pop();
        }
        // Binary op
        if (rpn_queue.front()[0] == '+' || rpn_queue.front()[0] == '-' || rpn_queue.front()[0] == '*' || rpn_queue.front()[0] == '/') {
            if (this->expStack.size() < 2) {
                throw "Invalid input";
            }
            Expression* r = this->expStack.top();
            this->expStack.pop();
            Expression* l = this->expStack.top();
            this->expStack.pop();
            if (!(rpn_queue.empty()) && rpn_queue.front()[0] == '+') {
                Expression* toPush = new Plus(l, r);
                this->expStack.push(toPush);
            }
            if (!(rpn_queue.empty()) && rpn_queue.front()[0] == '-') {
                Expression* toPush = new Minus(l, r);
                this->expStack.push(toPush);
            }
            if (!(rpn_queue.empty()) && rpn_queue.front()[0] == '/') {
                Expression* toPush = new Div(l, r);
                this->expStack.push(toPush);
            }
            if (!(rpn_queue.empty()) && rpn_queue.front()[0] == '*') {
                Expression* toPush = new Mul(l, r);
                this->expStack.push(toPush);
            }
            // else - throw error
            if (!(rpn_queue.empty())) {
                rpn_queue.pop();
            }
        }
        // Unary op
        if (!(rpn_queue.empty()) && (rpn_queue.front()[0] == '!' || rpn_queue.front()[0] == '@')) {
            if (this->expStack.size() < 1) {
                throw "Invalid input";
            }
            Expression* insider = this->expStack.top();
            this->expStack.pop();
            if (rpn_queue.front()[0] == '!') {
                this->expStack.push(new UMinus(insider));
            }
            else {
                this->expStack.push(new UPlus(insider));
            }
            if (!(rpn_queue.empty())) {
                rpn_queue.pop();
            }
        }
        // Var
        if (!(rpn_queue.empty()) && (rpn_queue.front()[0] == '_' || isalpha(rpn_queue.front()[0]))) {
            Expression* e1 = findInMap(rpn_queue.front());
            this->expStack.push(e1);
            rpn_queue.pop();
        }
    }
    Expression* result = this->expStack.top();
    this->expStack.pop();
    return result;
}

void Interpreter::setVariables(string s) {
    if (this->isValid(s)){
        // if it has no delimiter
        if (s.find(";") == string::npos){
            s += ';';
            this->send2Map(s);
        }
        else {
            unsigned int i = 0;
            string subStr = "";
            if (s[s.length() - 1] != ';'){
                s += ';';
            }
            while (i < s.length()) {
                subStr += s[i];
                if (s[i] == ';') {
                    this->send2Map(subStr);
                    subStr = "";
                }
                i++;
            }
        }
    }
    else {
        throw "Invalid Input!";
    }
}


bool Interpreter:: isValid(string s) {
    // with a little help from https://stackoverflow.com/questions/12643009/regular-expression-for-floating-point-numbers
    regex r("([_[:alnum:]]+=([0-9]+[.])?[[:digit:]]+;{0,1})+");
    // if the input string is valid
    if (regex_match(s, r)) {
        return true;
    }
    return false;
}

void Interpreter::send2Map(string s) {
    int i = 0;
    string token = "";
    string tokenVal = "";
    while (s[i] != '='){
        token += s[i];
        i++;
    }
    i++;
    while (s[i] != ';'){
        tokenVal += s[i];
        i++;
    }
    redefineValInMap(token, tokenVal);
    this->var_map.insert(pair<string, double>(token, stod(tokenVal)));
}

Expression* Interpreter::findInMap(string s) {
    map<string, double>::iterator itr;
    for (itr = this->var_map.begin(); itr != this->var_map.end(); ++itr) {
        if (!(itr->first.compare(s))) {
            string varName = itr->first;
            double varVal = itr->second;
            return new Variable(varName, varVal);
        }
    }
    throw "Not in Map!";
}

Expression* Interpreter:: interpret(string s) {
    this->inf2post(s);
    return this->rpn(this->queue);
}

void Interpreter::redefineValInMap(string tok, string val) {
    map<string, double>::iterator itr = this->var_map.find(tok);
    if (itr != this->var_map.end()) {
        itr->second = stod(val);
    }
}
