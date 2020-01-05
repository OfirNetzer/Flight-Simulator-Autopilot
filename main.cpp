#include <string>
#include "Lexer.h"
#include "Queue.h"
#include "symTable.h"
#include "CommandDB.h"
#include "Flag.h"
#include "Threads.h"

symTable* symTable:: instance = nullptr;
CommandDB* CommandDB:: instance = nullptr;
Flag* Flag:: instance = nullptr;
Threads* Threads:: instance = nullptr;

using namespace std;

int main(int argc, char *argv[]) {
/* ///Exp test
 * symTable::getInstance()->uiMap.insert({"h0", new Var("n", "s", "d", 200)});
    symTable::getInstance()->uiMap.insert({"heading", new Var("n", "s", "d", 40)});
    Exp::inter("(h0-heading)/80");*/

    ///lexer test
    auto lexer = new Lexer();
    vector<string> lexArr = lexer->mainLex(argv);

    ///test server
    vector<string> loc = OpenServerCommand::createLoc();
    for (int i = 0; i < 36; i++) {
        symTable::getInstance()->siMap.insert({loc[i], new Var("n", "s", "d", 5)});
    }
    auto op = new OpenServerCommand();
    op->execute(lexArr, 0); //todo change 0 to index

   /* ///test client
//    symTable::getInstance()->uiMap.insert({})
    Queue::getInstance()->q.push("queue 1");
    Queue::getInstance()->q.push("queue 2");
    Queue::getInstance()->q.push("queue c");
    auto co = new connectCommand();
    co->execute(lexArr, 2);

    Threads::getInstance()->client.join();*/
    Threads::getInstance()->server.join();

    cout << "in main" << endl;


    //todo join thread1 (client) and thread2 (server) at the end. Probably inside the parser
    delete lexer;
    return 0;
}
