//
// Created by avichai on 30/12/2019.
//

#ifndef EX3A_LEXER_H
#define EX3A_LEXER_H

#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include "ex1.h"
#include <unordered_map>
#include "Command.h"
#include "OpenServerCommand.h"
#include "connectCommand.h"


class Lexer {
public:
    Lexer();
    void createLexer(string line, vector<string> &lexArr);
    void pushStr(string str, vector<string> &lexArr);
    static bool ifOrWhile(string str);
    vector<string> mainLex(char **file);
    int countEndPars(string);
    int findLastPar(string line, int pars);
    void splitFuncWords(string, vector<string>);
};


#endif //EX3A_LEXER_H
