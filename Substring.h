//
// Created by avichai on 31/12/2019.
//

#ifndef EX3A_SUBSTRING_H
#define EX3A_SUBSTRING_H

#include <string>
using namespace std;

class Substring {
public:
    string create(char delim, string line, int* i) {
        string stri = "";
        while (line[*i] != delim) {
            stri += line[*i];
            (*i)++;
        }
        return stri;
    }
};


#endif //EX3A_SUBSTRING_H
