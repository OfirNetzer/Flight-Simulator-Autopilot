//
// Created by ofirn93 on 30/12/2019.
//

#include "Parser.h"



void Parser::run(vector <string> lexerCommands) {
//    CommandDB::getInstance()->getCommand(lexerCommands.at(this->ind));
    while (this->ind < lexerCommands.size()) {
        Command *c = CommandDB::getInstance()->getCommand(lexerCommands.at(this->ind));
        int i = this->ind;
        this->ind = c->execute(lexerCommands, i);
    }
}
