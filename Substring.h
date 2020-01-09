//
// Created by avichai on 31/12/2019.
//

#ifndef EX3A_SUBSTRING_H
#define EX3A_SUBSTRING_H

#include <string>

/**Create a substring with a given delimiter.
 * case 1: each substring is a valid variable name
 * case 2: if given string[i] is a word or number, the substring will be the whole word/number
 * case 3: if it's in operator, the substring will be the whole
 * case 4 (create2): 2 delimiters are being sent
 */
using namespace std;

class Substring {
public:

    static bool isOperator(char c) {
        return c == '<' || c == '>' || c == '=' || c == '+' || c == '-' || c == '{';
    }

    //return a substring delimited by a given delimiter
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
        return stri;
    }

    //create a substring with 2 possible delimiters
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
