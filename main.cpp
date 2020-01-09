#include <string>
#include "Lexer.h"
#include "symTable.h"
#include "CommandDB.h"
#include "Flag.h"
#include "Parser.h"
#include "Mutex.h"

/**argv is a file with commands for the simulator.
 * Main sends it to create a lexer which tokenizes the file's content,
 * and then sends the lexer to the parser, which executes every line of the file.
 *
 */

symTable* symTable:: instance = nullptr;
CommandDB* CommandDB:: instance = nullptr;
Flag* Flag:: instance = nullptr;
Mutex* Mutex:: instance = nullptr;

using namespace std;

int main(int argc, char *argv[]) {

    auto lexer = new Lexer();
    vector<string> lexArr = lexer->mainLex(argv);
    auto parser = new Parser();
    parser->run(lexArr);
    delete lexer;
    delete parser;

    return 0;
}


