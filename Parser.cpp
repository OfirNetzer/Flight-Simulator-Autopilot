//
// Created by ofirn93 on 30/12/2019.
//

#include <iostream>
#include <unistd.h>
#include "Parser.h"
#include "ex1.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#include "whileCommand.h"
#include "ifCommand.h"
#include "Flag.h"
#include "Threads.h"

using namespace std;

Parser::Parser() {
    this->ind = 0;
    OpenServerCommand* osc =new OpenServerCommand();
    DefineVarCommand* dvc = new DefineVarCommand();
    connectCommand* cc = new connectCommand();
    PrintCommand* pc = new PrintCommand();
    SleepCommand* sc = new SleepCommand();
    whileCommand* wc = new whileCommand();
    ifCommand* ic = new ifCommand();
    CommandDB::getInstance();
    CommandDB::getInstance()->addCommand("openDataServer", osc);
    CommandDB::getInstance()->addCommand("var", dvc);
    CommandDB::getInstance()->addCommand("connectControlClient", cc);
    CommandDB::getInstance()->addCommand("Print", pc);
    CommandDB::getInstance()->addCommand("Sleep", sc);
    CommandDB::getInstance()->addCommand("if", ic);
    CommandDB::getInstance()->addCommand("while", wc);
}

void Parser::run(vector <string> lexerCommands) {
//    CommandDB::getInstance()->getCommand(lexerCommands.at(this->ind));
    while (this->ind < lexerCommands.size()) {
        Command *c;
        /*
        // here we check what kind of command should we use.
        // the only command we can't handle by using a key is update variable so we check the next string
        // if the next string is "=" we will match it to var command that updates the variable value
        // otherwise, we will match our commands using keys.
        if (lexerCommands.at(this->ind + 1) == "+=") {
            // send float right = lexerCommands.at(this->ind + 2) to Exp.h
            // left is the old val of the var
//            float right =
            float left = symTable::getInstance()->uiMap.at(lexerCommands.at(this->ind))->getVal();
            // float newVal = left + right (the interpreted value of the expression)
            // symTable::getInstance()->uiMap.at(lexerCommands.at(this->ind))->setVal(newVal);
            this->ind += 3;
        }*/
        if (lexerCommands.at(this->ind + 1).find("=") != string::npos) {
            c = CommandDB::getInstance()->getCommand("var");
        } else {
            c = CommandDB::getInstance()->getCommand(lexerCommands.at(this->ind));
        }
//        int i = this->ind;
        this->ind += c->execute(lexerCommands, this->ind);
    }
    Flag::getInstance()->threadFlag = false;
    if (Threads::getInstance()->server.joinable()) {
        Threads::getInstance()->server.join();
    }
    close(symTable::getInstance()->clientSocketFD);
}



