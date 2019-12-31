#include <string>
#include "ex1.h"
#include "Lexer.h"
#include "Queue.h"
#include "Parser.h"
symTable* symTable:: instance = nullptr;
CommandDB* CommandDB:: instance = nullptr;

using namespace std;

int main(int argc, char *argv[]) {
    Lexer* lexer = new Lexer();
    vector<string> lexArr = lexer->mainLex(argv);
    int i = 0;
    Parser* parser = new Parser();
    parser->run(lexArr);
    ///queue test
//    connectCommand* co = new connectCommand();
//    co->execute(lexArr, 0);
//    OpenServerCommand* op = new OpenServerCommand();
//    op->execute(lexArr, 0); //todo change 0 to index

    //todo join thread1 (client) and thread2 (server) at the end. Probably inside the parser
    delete lexer;
    return 0;
}
