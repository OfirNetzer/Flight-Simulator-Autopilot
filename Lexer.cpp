//
// Created by avichai on 30/12/2019.
//

#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include "ex1.h"
#include "Command.h"
#include "OpenServerCommand.h"
#include "connectCommand.h"

#include "Lexer.h"

Lexer::Lexer() = default;

//todo handle a situation in which I get an expression without spaces, such as x<3
//todo handle a situation in which I get parnthesis inside the () of print/func/sleep etc.
//todo handle += and -= that can come instead of =

void Lexer::createLexer(string line, vector<string> &lexArr) {
    int i = 0;
    string str, sub;
    regex funcRegA("(\\s*[_[:alnum:]]+[(]+.+[)]+\\s*)");
    regex equalRegA("(\\s*[_[:alnum:]]+\\s?=(.*))");
    regex equalRegB("(\\s*[_[:alnum:]]+\\s+[_[:alnum:]]+\\s?=\\s?([0-9]+[.])?[[:alnum:]]+\\s*)");
    regex varReg("(\\s*[[:alpha:]]+\\s+[_[:alnum:]]+\\s?[->|<-]+\\s?sim[(]+.+[)]+\\s*)");
    regex funcRegB("(\\s*[_[:alnum:]]+[(]+.+[)]+\\s?[{]{1,1}\\s*)");

    if (regex_match(line, funcRegA)) { //e.g print(rpm)
        str = substring('(', line, &i);
        pushStr(str, lexArr);
        i++;
        str = "";
        str = substring(')', line, &i);
        //we can't just add str now to lexArr because we don't know:
        // a. how many words it contains. b. if it's an expression or a string. That's why we use pushStr
        pushStr(str, lexArr);
    } else if (regex_match(line, equalRegA)) { //e.g. primer = 3
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
    } else if (regex_match(line, equalRegB)) { // e.g. var h0 = heading
        str = substring(' ', line, &i);
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
    } else if (regex_match(line, varReg)) { // e.g. var alt -> sim(...)
        //first add all of the words up to "sim", delimited by whitespace
        size_t sim = line.find("sim(");
        while (i < sim) {
            str = substring(' ', line, &i);
            pushStr(str, lexArr);
            str = "";
            if (line[i] == ' ') {
                i++;
            }
        }
        //then add "sim(....)"
        str = substring('(', line, &i);
        pushStr(str, lexArr);
        str = "";
        i++;
        str = substring(')', line, &i);
        pushStr(str, lexArr);
    } else if (ifOrWhile(line)) { //line is if or while
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
    } else if (regex_match(line, funcRegB)) { // e.g. print(...) {
        int j=0;
        str = substring('(', line, &i);
        pushStr(str, lexArr);
        i++;
        str = "";
        str = substring(')', line, &i);

        //check for spaces
        size_t space = str.find(' ');
        if (space != string::npos) { //if there are spaces
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

bool Lexer::ifOrWhile(string str) {
    string temp;
    //trim leading spaces and tabs if there are any
    str = std::regex_replace(str, std::regex("^ +"), "");
    str.erase(std::remove(str.begin(), str.end(), '\t'), str.end());
    for (int i=0; str[i] != ' '; i++) {
        temp += str[i];
    }
    return temp == "while" || temp == "if";
}

string Lexer::substring(char delim, string line, int* i) {
    string stri;
    while (line[*i] != delim) {
        stri += line[*i];
        (*i)++;
    }
    return stri;
}

//function that checks if what's inside the () is a regular string ("") or expression (no "")
void Lexer::pushStr(string str, vector<string> &lexArr) {
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

vector<string> Lexer::mainLex(char **file) {
    string line;
    vector<string> lineArr, lexArr;
    int i = 0;

    ifstream myfile(file[1]);
    if (!myfile) {
        throw "Error with the file";
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