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

using namespace std;

/*
 * the constructor of our parser, initializes the index and create instances of
 * every command we might face during parsing over the lexer vector
 * */
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

/*
 * the parser runs over every command in the vector, and matches between a string to a command
 * once it has the right command, it will run it's execute function
 * the function (int type) will return the number of "jumps" our index should do in order
 * to get to the next command in the vector
 * */
void Parser::run(vector <string> lexerCommands) {
    while (this->ind < lexerCommands.size()) {
        Command *c;
        if (lexerCommands.at(this->ind + 1).find("=") != string::npos) {
            c = CommandDB::getInstance()->getCommand("var");
        } else {
            c = CommandDB::getInstance()->getCommand(lexerCommands.at(this->ind));
        }
//        int i = this->ind;
        this->ind += c->execute(lexerCommands, this->ind);
    }
    close(symTable::getInstance()->clientSocketFD);
}



