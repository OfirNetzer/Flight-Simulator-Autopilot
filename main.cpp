#include <string>
#include "ex1.h"
#include "Lexer.h"
#include "Queue.h"

using namespace std;

int main(int argc, char *argv[]) {
    Lexer* lexer = new Lexer();
    vector<string> lexArr = lexer->mainLex(argv);
    int i = 0;
    ///queue test
    connectCommand* co = new connectCommand();
    co->execute(lexArr, 0);
//    OpenServerCommand* op = new OpenServerCommand();
//    op->execute(lexArr, 0); //todo change 0 to index

    //todo join thread1 (client) and thread2 (server) at the end. Probably inside the parser
    delete lexer;
    return 0;
}
