//
// Created by avichai on 30/12/2019.
//

#include <iostream>
#include <regex>
#include <string>
#include "ex1.h"
#include "Substring.h"
#include "Lexer.h"

Lexer::Lexer() = default;

//todo handle a situation in which I get parnthesis inside the () of print/func/sleep etc
//todo handle += and -= that can come instead of =
//todo change in ex1.cpp that -x will be valid (meanning without '(' after the '-' )
//todo handle case in which there are parenthesis around the while or the if condition

void Lexer::createLexer(string line, vector<string> &lexArr) {
    int i = 0;
    string str, sub;
    regex funcRegA("(\\s*[_[:alnum:]]+[(]+.+[)]+\\s*)");
    regex equalRegA("(\\s*[_[:alnum:]]+\\s?[-]?[+]?=(.*))");
    regex equalRegB("(\\s*[_[:alnum:]]+\\s+[_[:alnum:]]+\\s?[-]?[+]?=\\s?([0-9]+[.])?[[:alnum:]]+\\s*)");
    regex varReg("(\\s*[[:alpha:]]+\\s+[_[:alnum:]]+\\s?[->|<-]+\\s?sim[(]+.+[)]+\\s*)");
    regex funcRegB("(\\s*[_[:alnum:]]+[(]+.+[)]+\\s?[{]{1,1}\\s*)");

    //todo change the below if's of equalRegA and equalRegB so that they don't always push '=' into lexArr, but rather whatever is there, whether it's = or -= or +=
    //todo I changed in Substring, that if stri == "+=" or "-=" then (*i)-- in the last condition

    if (regex_match(line, funcRegA)) { //e.g print(rpm)
        //push until '('
        size_t found = line.find('(');
        pushStr(line.substr(0, found), lexArr);
        //push after first '(' until last ')'
        int pars = countEndPars(line);
        pushStr(line.substr(found + 1, findLastPar(line, pars) - found - 1), lexArr);
    } else if (regex_match(line, funcRegB)) { // e.g. print(...) {
        //push until '('
        size_t found = line.find('(');
        pushStr(line.substr(0, found), lexArr);
        //push after first '(' until last ')'
        int pars = countEndPars(line);
        str = line.substr(found+1, findLastPar(line, pars)-found-1);

        //check for spaces
        size_t space = str.find(' ');
        //if there are spaces, push the string word by word
        if (space != string::npos) {
            //push words into lexArr
            for (int k = 0; k < str.length(); k++) {
                sub = Substring::create(' ', str, &k);
                if (sub.empty() || sub == " ") {
                    k++;
                    sub = Substring::create(' ', str, &k);
                }
                pushStr(sub, lexArr);
                k++;
                sub = Substring::create2(')', ',', str, &k);
                pushStr(sub, lexArr);
            }
            lexArr.push_back("{");
        } else { //if there aren't any spaces
            pushStr(str, lexArr);
            lexArr.push_back("{");
        }
    } else if (regex_match(line, equalRegA) || regex_match(line, equalRegB)) { //e.g. primer = 3, var h0 = heading
        //if there are two words before the =, push now the first one ("var")
        if (regex_match(line, equalRegB)) {
            str = Substring::create(' ', line, &i);
            pushStr(str, lexArr);
            i++;
            str = "";
        }

        str = Substring::create('=', line, &i);
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
    } else if (regex_match(line, varReg)) { // e.g. var alt -> sim(...)
        //first add all of the words up to "sim", delimited by whitespace
        size_t sim = line.find("sim(");
        while (i < sim) {
            str = Substring::create(' ', line, &i);
            pushStr(str, lexArr);
            str = "";
            if (line[i] == ' ') {
                i++;
            }
        }
        //then add "sim(....)"
        str = Substring::create('(', line, &i);
        pushStr(str, lexArr);
        str = "";
        i++;
        pushStr(line.substr(i, line.length()-i-1), lexArr);
    } else if (ifOrWhile(line)) { //line is if or while
        line = std::regex_replace(line, std::regex("^ +"), "");
        line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
        while (i < (line.length()-1)) {
            //trim leading spaces and tabs if there are any
            str = Substring::create(' ', line, &i);
            pushStr(str, lexArr);
            str = "";
            i++;
        }
        str = line[i];
        lexArr.push_back(str);
    }  else { //it's '}'
        pushStr(line, lexArr);
    }
}

bool Lexer::ifOrWhile(string str) {
    string temp;
    //trim leading spaces and tabs if there are any
    str = std::regex_replace(str, std::regex("^ +"), "");
    str.erase(std::remove(str.begin(), str.end(), '\t'), str.end());
    for (int i=0; str[i] != ' '; i++) {//todo handle a situation in which I get an expression without spaces, such as x<3
        temp += str[i];
    }
    return temp == "while" || temp == "if";
}

//function that checks if what's inside the () is a regular string ("") or expression (no "")
void Lexer::pushStr(string str, vector<string> &lexArr) {
    int i = 0, len = str.length();
    string string1;
    char delim = ',';
    size_t comma = str.find(',');
    //trim leading and trailing spaces and tabs if there are any
    str = regex_replace(str, regex("^ +"), "");
    str.erase(remove(str.begin(), str.end(), '\t'), str.end());
    str = regex_replace(str, regex(" +$"), "");
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

vector<string> Lexer::mainLex(char *file[]) {
    string line;
    vector<string> lineArr, lexArr;
    int i = 0;

    ifstream myfile(file[1]);
    if (!myfile) {
        cerr << "Error occurred while opening file";
    }

    // create lines of input array
    while (getline(myfile, line)){
        //add the lines to the array, with nullptr in the end of every line
        lineArr.push_back(line);
        i++;
    }

    //check regex and then push into mainLex array
    for (int j=0; j < i; j++) {
        createLexer(lineArr.at(j), lexArr);
    }

    ///test
    //todo erase when done with it
    for (string s : lexArr) {
        cout << s << endl;
    }

    return lexArr;
}

int Lexer::countEndPars(string line) {
    int pars = 0;
    for (char c : line) {
        if (c == ')') {
            pars++;
        }
    }
    return pars;
}

//find the position of the last ')' in the string
int Lexer::findLastPar(string line, int pars) {
    int countPars = 0;
    int posCounter = -1;
    for (char c : line) {
        posCounter++;
        if (c == ')') {
            countPars++;
        }
        if(countPars == pars) {
            break;
        }
    }
    return posCounter;
}
