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
        return c == '<' || c == '>' || c == '=' || c == '+' || c == '-';
     }
    static string create(char delim, string line, int* i) {
        string stri;
        while ((line[*i] != delim) && (line[*i] != '\n') && !isOperator(line[*i])) {
            stri += line[*i];
            (*i)++;
        }
        return stri;
    }
};


#endif //EX3A_SUBSTRING_H
