#include <string>
#include "ex1.h"
#include "Lexer.h"
#include "Parser.h"


using namespace std;

/*
unordered_map<string, Command> createMap(vector<string> lexArr) {
    unordered_map<string, Command> map;
    for (string s : lexArr) {
        if (s == "openDataServer") {
            map.insert(s, new OpenServerCommand());
        } else if (s == "connectControlClient") {
            map.insert(s, )
        }
    }
}*/

int main(int argc, char *argv[]) {
    Lexer* lexer = new Lexer();
    vector<string> lexArr = lexer->mainLex(argv);
    Parser* parser = new Parser();
//    connectCommand* co = new connectCommand();
//    co->execute(lexArr);
//    OpenServerCommand* op = new OpenServerCommand();
//    op->execute(lexArr);
    //todo join thread1 (client) and thread2 (server) at the end. Probably inside the parser
//    unordered_map<string, Command> map = createMap(lexArr);
    return 0;
}
