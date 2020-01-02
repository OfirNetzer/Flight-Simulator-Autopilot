//
// Created by ofirn93 on 30/12/2019.
//

#include <iostream>
#include "Parser.h"
#include "ex1.h"

Parser::Parser() {
    this->ind = 0;
    OpenServerCommand* osc =new OpenServerCommand();
    DefineVarCommand* dvc = new DefineVarCommand();
    connectCommand* cc = new connectCommand();
    CommandDB::getInstance()->addCommand("openDataServer", osc);
    CommandDB::getInstance()->addCommand("openDataServer", dvc);
    CommandDB::getInstance()->addCommand("var", cc);
    // todo: complete with 1.func 2. while 3.if once we build these commands
}

void Parser::run(vector <string> lexerCommands) {
//    CommandDB::getInstance()->getCommand(lexerCommands.at(this->ind));
    while (this->ind < lexerCommands.size()) {
        Command *c = CommandDB::getInstance()->getCommand(lexerCommands.at(this->ind));
        int i = this->ind;
        this->ind += c->execute(lexerCommands, this->ind);
//        this->ind++;
    }
}



