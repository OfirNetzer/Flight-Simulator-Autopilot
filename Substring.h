//
// Created by avichai on 31/12/2019.
//

#ifndef EX3A_SUBSTRING_H
#define EX3A_SUBSTRING_H

#include <string>
using namespace std;

class Substring {
public:

    static bool isOperator(char c) {
        return c == '<' || c == '>' || c == '=' || c == '+' || c == '-' || c == '{';
    }

    static string create(char delim, string line, int *i) {
        string stri;
        //'v' means this is called from Exp class, and checks if string is a variable
        if (delim == 'v') {
            while (((*i < line.length()) && isalnum(line[*i])) || line[*i] == '_') {
                stri += line[*i];
                (*i)++;
            }
        } else {
            if (!isOperator(line[*i])) { // if string is not an operator or a sign
                while ((line[*i] != delim) && (*i < line.length())/* && !isOperator(line[*i])*/) {
                    stri += line[*i];
                    (*i)++;
                }
            } else { //if string is an operator or a sign
                while ((line[*i] != delim) && (*i < line.length()) && (line[*i] != ' ') &&
                       (!isalnum(line[*i]) && line[*i] != '_')) {
                    stri += line[*i];
                    (*i)++;
                }
            }
        }
//todo change in ex1.cpp that -x will be valid (meaning without '(' after the '-' )
/*        int k = *i;
        char c = line[k];
        char d = line[++k];
        //if after the substring comes <=/>=/=</=> then move the index i one place down
        if (((c == '=') && ((d == '<') || (d == '>'))) || // => or =<
            (((c == '<') || (c == '>') || (c == '+') || (c == '-')) && (d == '=')) || c == '{' ||
            (stri == "<=" || stri == "=>" || stri == "-=" || stri == "+=")) { // >= or <= or += or -=
            //todo stri == "-=" || stri == "+=" this part is for the change of equalReg in Lexer
            (*i)--;ז
        }*/
        return stri;
    }

    static string create2(char delim, char delim2, string line, int *i) {
        string stri;
        while ((line[*i] != delim) && (line[*i] != delim2) && *i < line.length()) {
            stri += line[*i];
            (*i)++;
        }
        return stri;
    }
};


#endif //EX3A_SUBSTRING_H
