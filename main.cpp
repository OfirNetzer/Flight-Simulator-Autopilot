#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include "Expression.h"
#include "ex1.h"
#include "Command.h"

using namespace std;
vector<string> lexer(string myfile);
void checkReg(string line, vector<string> &lexArr);
void pushStr(string str, vector<string> &lexArr);
string expToStr(string str);

void checkReg(string line, vector<string> &lexArr) {
    int i = 0;
    string str = "";
    regex funcReg("([_[:alnum:]]+[(]+.+[)]+)");
    regex equalRegA("([_[:alnum:]]+\\s?=\\s?([0-9]+[.])?[[:alnum:]]+)");
    regex equalRegB("([_[:alnum:]]+\\s+[_[:alnum:]]+\\s?=\\s?([0-9]+[.])?[[:alnum:]]+)");
    regex varReg("([[:alpha:]]+\\s+[_[:alnum:]]+\\s?[->|<-]+\\s?sim[(]+.+[)]+)");
//    regex whileReg("(while\\s+[_[:alnum:]]+\\s?)"); //[<|<=|>|>=|==]?\\s?[_[:alnum:]]+\\s*[{]*)");
    regex whileReg("([[:alpha:]]+\\s+[_[:alnum:]]+\\s?[<|<=|>|>=|==]?\\s*[{]+)");
    regex funcRegB("([_[:alnum:]]+[(]+.+[)]+\\s?[{]{1,1})");
    //todo handle while
    //split the funcReg match by the delimiter '('
    if (regex_match(line, funcReg)) {
        while (line[i] != '(') {
            str += line[i];
            i++;
        }
        lexArr.push_back(str);
        i++;
        str = nullptr;
        while (line[i] != ')') {
            str += line[i];
            i++;
        }
        //we can't just add str now to lexArr because we don't know:
        // a. how many words it contains. b. if it's an expression or a string. That's why we use pushStr
        pushStr(str, lexArr);
    } else if (regex_match(line, equalRegA)) {
        while (line[i] != '=') {
            str += line[i];
            i++;
        }
        //remove spaces from str
        str.erase(remove(str.begin(), str.end(), ' '), str.end());
        lexArr.push_back(str);
        lexArr.push_back("=");
        i++;
        str = nullptr;
        for (i; i<line.length(); i++) {
            str += line[i];
        }
        //remove spaces from str
        str.erase(remove(str.begin(), str.end(), ' '), str.end());
        pushStr(str, lexArr);
    } else if (regex_match(line, equalRegB)) {
        while (line[i] != ' ') {
            str += line[i];
            i++;
        }
        lexArr.push_back(str);
        i++;
        str = nullptr;
        while (line[i] != '=') {
            str += line[i];
            i++;
        }
        //remove spaces from str
        str.erase(remove(str.begin(), str.end(), ' '), str.end());
        lexArr.push_back(str);
        lexArr.push_back("=");
        i++;
        str = nullptr;
        for (i; i<line.length(); i++) {
            str += line[i];
        }
        //remove spaces from str
        str.erase(remove(str.begin(), str.end(), ' '), str.end());
        pushStr(str, lexArr);
    } else if (regex_match(line, varReg)) {
        //first add all of the words up to "sim", delimited by whitespace
        size_t sim = line.find("sim(");
        size_t a = line.find("<-");
        size_t b = line.find("->");
        for (i=0; i<sim; i++) {
            while ((i != ' ') && (i != a) && (i != b)) {
                str += line[i];
                i++;
            }
            lexArr.push_back(str);
            i++;
            str = nullptr;
        }
        //then add "sim(....)"
        for (i; i<line.length(); i++) {
            str += line[i];
            i++;
        }
        lexArr.push_back(str);
    } else if (regex_match(line, whileReg)) {
        //TODO avichai to complete
        cout <<"hi";
        cout <<"hi";
        cout <<"hi";
    } else if (regex_match(line, funcRegB)) {
        //TODO avichai to complete
        cout <<"hi";
        cout <<"hi";
        cout <<"hi";
    }

}

//function that checks if what's inside the () is a regular string ("") or expression (no "")
void pushStr(string str, vector<string> &lexArr) {
    int i = 0;
    string string1;
    if (!str.find(',')) {
        //if it's only one word and is a string, return it
        if (str.find('"')) {
            lexArr.push_back(str);
        } // if it's one word and is an expression, interpret it and add to array lexArr
        else {
            lexArr.push_back(expToStr(str));
        }
    } else { // if there's more than one word, check each one like above
        for(int j=0; j< str.length(); j++) {
            while (str[i] != ',') {
                string1 += str[i];
                i++;
            }
            //if current word is a string, add it to the lexArr array
            if (string1[0] == '"' && str[i - 1] == '"') {
                lexArr.push_back(str);
            } else { // else, it's an expression. Turn it to string and add to lexArr
                lexArr.push_back(expToStr(str));
            }
            //skip the comma in the while loop above
            i++;
        }
    }
}

string expToStr(string str) {
    Interpreter* inter = new Interpreter();
    Expression* exp = nullptr;
    try {
        exp = inter->interpret(str);
        string strExp = to_string(exp->calculate());
        delete inter;
        delete exp;
        return strExp;
    } catch (const char* e) {
        if (exp != nullptr) {
            delete exp;
        }
        if (inter != nullptr) {
            delete inter;
        }
        std::cout << e << std::endl;
        return "error";
    }
}

//func that returns the lexer we built to the main function
vector<string> lexer(string filename){
    // we need to check how to reach to the file
    FILE *fp;
    string line;
    vector<string> lineArr, lexArr;
    int i = 0;
    //Regex Debug:
    /*DEBUG!!!
    //funcReg
//    string test = "ofir(\"stam\" , chief)";
    //equalRegA
//    string test = "ofir = 9.2";
//    string test = "ofir = cool";
//    string test = "ofir = 1";
    //equalRegB
//    string test = "ofir var0 = Stam";
//    string test = "ofir var0 = Stam";
    //varReg
//    string test = "var roll -> sim(Stam)";
//    string test = "var roll <- sim(Stam)";
//    checkReg(test, lexArr);
    string test = "while x < 0 {";
    string test = "takeof(var){";
    checkReg(test, lexArr);*/

//    string test = "while rpm <= 750 {";
    string test = "while x < 0 {";
//    string test = "while rpm < 7";
    checkReg(test, lexArr);
// todo - in the real program use the argv[1] input, which means the file we get from the cmd execute.
    ifstream myfile(filename);
//    myfile.open("fly_with_func.txt", ifstream::in);
    if (!myfile.is_open()) {
        throw "Error with the file";
    }
    // create lines of input array
    while (getline(myfile, line)){
        //add the lines to the array, with nullptr in the end of every line
        lineArr.push_back(line);
        i++;
    }
    //check regex and then push into lexer array
    for (int j=0; j < i; j++) {
        checkReg(lineArr.at(j), lexArr);
    }
    return lexArr;
}

void parser(vector<string> comArr) {
//    while ()
}

int main(int argc, char *argv[]) {
    regex whileReg("([[:alpha:]]+\\s+[_[:alnum:]]+\\s?[<|<=|>|>=|==]?\\s*[{]+)");
    string test = "while rpm < 7";
    if (regex_match(test, whileReg)){
        return 0;
    }
    vector<string> vector = lexer("fly_with_func.txt");
    return 0;
}

