#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include "Expression.h"
#include "ex1.h"

using namespace std;

void createLexer(string line, vector<string> &lexArr);
void pushStr(string str, vector<string> &lexArr);
string substring(char, string, int*);
string expToStr(string str);

void createLexer(string line, vector<string> &lexArr) {
    int i = 0;
    string str = "";
    regex funcRegA("(\\s*[_[:alnum:]]+[(]+.+[)]+)");
    regex equalRegA("(\\s*[_[:alnum:]]+\\s?=\\s?([0-9]+[.])?[[:alnum:]]+)");
    regex equalRegB("(\\s*[_[:alnum:]]+\\s+[_[:alnum:]]+\\s?=\\s?([0-9]+[.])?[[:alnum:]]+)");
    regex varReg("(\\s*[[:alpha:]]+\\s+[_[:alnum:]]+\\s?[->|<-]+\\s?sim[(]+.+[)]+)");
    regex whileReg("(\\s*while\\s+[_[:alnum:]]+\\s?[<|<=|>|>=|==]?\\s?[_[:alnum:]])"); //[<|<=|>|>=|==]?[_[:alnum:]]?{?");
    regex funcRegB("(\\s*[_[:alnum:]]+[(]+.+[)]+\\s?[{]{1,1})");
    //todo handle while regex
    //split the funcRegA match by the delimiter '('
    if (regex_match(line, funcRegA)) {
        str = substring('(', line, &i);
        lexArr.push_back(str);
        i++;
        str = "";
        str = substring(')', line, &i);
        //we can't just add str now to lexArr because we don't know:
        // a. how many words it contains. b. if it's an expression or a string. That's why we use pushStr
        pushStr(str, lexArr);
    } else if (regex_match(line, equalRegA)) {
        str = substring('=', line, &i);
        //remove spaces from str
        str.erase(remove(str.begin(), str.end(), ' '), str.end());
        pushStr(str, lexArr);
        lexArr.push_back("=");
        i++;
        str = "";
        for (i; i < line.length(); i++) {
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
        pushStr(str, lexArr);
        i++;
        str = "";
        str = substring('=', line, &i);
        //remove spaces from str
        str.erase(remove(str.begin(), str.end(), ' '), str.end());
        pushStr(str, lexArr);
        lexArr.push_back("=");
        i++;
        str = "";
        for (i; i < line.length(); i++) {
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
        while (i < sim) {
            str = substring(' ', line, &i);
            pushStr(str, lexArr);
            str = "";
            if (line[i] == ' ') {
                i++;
            }
        }
        //then add "sim(....)"
        while (i < line.length()) {
            str += line[i];
            i++;
        }
        pushStr(str, lexArr);
    } else if (regex_match(line, whileReg)) {
        while (i < line.length()) {
            str = substring(' ', line, &i);
            pushStr(str, lexArr);
            str = "";
            i++;
        }
    } else if (regex_match(line, funcRegB)) {
        str = substring('(', line, &i);
        pushStr(str, lexArr);
        i++;
        str = "";
        str = substring(')', line, &i);
        pushStr(str, lexArr);
        str = line[++i];
        pushStr(str, lexArr);
    } else { //it's '{'
        pushStr(line, lexArr);
    }
}

string substring(char delim, string line, int* i) {
    string str;
    while (line[*i] != delim) {
        str += line[*i];
        (*i)++;
    }
    return str;
}

//function that checks if what's inside the () is a regular string ("") or expression (no "")
void pushStr(string str, vector<string> &lexArr) {
    int i = 0, len = str.length();
    string string1;
    size_t found = str.find(',');
    //trim leading spaces if there are any because of indentation
    str = regex_replace(str, std::regex("^ +"), "");
    //if no ',' was found in the string (meaning it's only one word)
    if (found == string::npos) {
        lexArr.push_back(str);
    } else { // if there's more than one word, check each one like above
        while (i < len) {
            while ((str[i] != ',') && (i<str.length())) {
                string1 += str[i];
                i++;
            }
            lexArr.push_back(string1);
            //skip the comma in the while loop above
            i++;
            string1 = "";
        }
    }
}

/*string expToStr(string str) {
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
        return "error in function expToStr";
    }
}*/

int main(int argc, char *argv[]) {

    // we need to check how to reach to the file
    FILE *fp;
    string line;
    vector<string> lineArr, lexArr;
    int i = 0;
    //Regex Debug://    myfile.open("fly_with_func.txt", ifstream::in);
/*    DEBUG!!!
    funcReg
    string test = "ofir(\"stam\" , chief)";
    equalRegA
    string test = "ofir = 9.2";
    string test = "ofir = cool";
    string test = "ofir = 1";
    equalRegB
    string test = "ofir var0 = Stam";
    string test = "ofir var0 = Stam";
    varReg
    string test = "var roll -> sim(Stam)";
    string test = "var roll <- sim(Stam)";
    createLexer(test, lexArr);*/
// todo - in the real program use the argv[1] input.
    ifstream myfile("fly_with_func.txt");
    if (!myfile) {
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
        createLexer(lineArr.at(j), lexArr);
    }

    for (string s : lexArr) {
        cout << s << endl;
    }
    return 0;
}
