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
bool checkWhile(string line);
string expToStr(string str);

void createLexer(string line, vector<string> &lexArr) {
    int i = 0;
    string str = "", sub = "";
    regex funcRegA("(\\s*[_[:alnum:]]+[(]+.+[)]+\\s*)");
    regex equalRegA("(\\s*[_[:alnum:]]+\\s?=(.*))"); //"(\\s*[_[:alnum:]]+\\s?=\\s?([0-9]+[.])?[[:alnum:]]+\\s*)"
    regex equalRegB("(\\s*[_[:alnum:]]+\\s+[_[:alnum:]]+\\s?=\\s?([0-9]+[.])?[[:alnum:]]+\\s*)");
    regex varReg("(\\s*[[:alpha:]]+\\s+[_[:alnum:]]+\\s?[->|<-]+\\s?sim[(]+.+[)]+\\s*)");
    regex whileReg("(\\s*while\\s+[_[:alnum:]]+\\s?[<|<=|>|>=|==]?\\s?[_[:alnum:]]\\s*[{])"); //[<|<=|>|>=|==]?[_[:alnum:]]?{?");
    regex funcRegB("(\\s*[_[:alnum:]]+[(]+.+[)]+\\s?[{]{1,1}\\s*)");
    //todo handle while regex
    //split the funcRegA match by the delimiter '('
    if (regex_match(line, funcRegA)) {
        str = substring('(', line, &i);
        pushStr(str, lexArr);
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
        while (i < (line.length()-1)) {
            //trim leading spaces and tabs if there are any
            line = std::regex_replace(line, std::regex("^ +"), "");
            line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
            str = substring(' ', line, &i);
            pushStr(str, lexArr);
            str = "";
            i++;
        }
        str = line[i];
        lexArr.push_back(str);
    } else if (regex_match(line, funcRegB)) {
        int j=0;
        str = substring('(', line, &i);
        pushStr(str, lexArr);
        i++;
        str = "";
        str = substring(')', line, &i);
        //check for spaces
        size_t space = str.find(' ');
        if (space != string::npos) {
            for (j=0;str[j] != ' ';j++) {
                sub += str[j];
            }
            pushStr(sub, lexArr);
            sub = str[++j];
            pushStr(sub, lexArr);
        } else { //if there aren't any spaces
            pushStr(str, lexArr);
            str = line[++i];
            pushStr(str, lexArr);
        }
    } else { //it's '}'
        pushStr(line, lexArr);
    }
}

string substring(char delim, string line, int* i) {
    string stri = "";
    while (line[*i] != delim) {
        stri += line[*i];
        (*i)++;
    }
    return stri;
}

//function that checks if what's inside the () is a regular string ("") or expression (no "")
void pushStr(string str, vector<string> &lexArr) {
    int i = 0, len = str.length();
    string string1;
    char delim = ',';
    size_t comma = str.find(',');
    //trim leading spaces and tabs if there are any
    str = std::regex_replace(str, std::regex("^ +"), "");
    str.erase(std::remove(str.begin(), str.end(), '\t'), str.end());
    //if no ',' was found in the string (meaning it's only one word)
    if (comma == string::npos) {
        lexArr.push_back(str);
    } else { // if there's more than one word, check each one like above
        while (i < len) {
            while ((str[i] != delim) && (i < str.length())) {
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

int main(int argc, char *argv[]) {

    string line;
    vector<string> lineArr, lexArr;
    int i = 0;

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

    return 0;
}
