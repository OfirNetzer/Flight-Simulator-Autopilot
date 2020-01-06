#include <string>
#include "Lexer.h"
#include "Queue.h"
#include "symTable.h"
#include "CommandDB.h"
#include "Flag.h"
#include "Threads.h"
#include "Parser.h"
#include "Mutex.h"

symTable* symTable:: instance = nullptr;
CommandDB* CommandDB:: instance = nullptr;
Flag* Flag:: instance = nullptr;
Threads* Threads:: instance = nullptr;
Mutex* Mutex:: instance = nullptr;

using namespace std;

int main(int argc, char *argv[]) {

    ///lexer test
    auto lexer = new Lexer();
    vector<string> lexArr = lexer->mainLex(argv);
    auto parser = new Parser();
    parser->run(lexArr);
    delete lexer;
    delete parser;

    /*///test server
    vector<string> loc = OpenServerCommand::createLoc();
    for (int i = 0; i < 36; i++) {
        symTable::getInstance()->siMap.insert({loc[i], new Var("n", "s", "d", 5)});
    }
    auto op = new OpenServerCommand();
    op->execute(lexArr, 0); //todo change 0 to index

    ///say we finished parsing with the parser --- test

    ///test client
    auto co = new connectCommand();
    co->execute(lexArr, 0);

    Threads::getInstance()->server.join();

    cout << "in main" << endl;
    delete lexer;*/
    return 0;
}


