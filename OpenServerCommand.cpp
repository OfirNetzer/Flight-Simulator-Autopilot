//
// Created by avichai on 01/01/2020.
//

#include "OpenServerCommand.h"
#include "Flag.h"
#include "symTable.h"
#include "Substring.h"
#include "Exp.h"
#include "Threads.h"
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>
#include <vector>
#include <thread>

using namespace std;

void receiveFromSim(int client_socket) {
    vector<string> loc = OpenServerCommand::createLoc();
    cout << "server 1" << endl;
    cout << "server 2" << endl;
    cout << "server 3" << endl;
    //todo erase the above three lines after done testing
    while (Flag::getInstance()->threadFlag) {
        //reading from client
        char buffer[1024] = {0};
        int valread = read( client_socket , buffer, 1024);
        if (valread < 1) {
            cerr << "Error while reading from simulator" << endl;
        }
        string buf(buffer);
        int i=0, count=0;
        while (buf[i-1] != '\n') {
            string str;
            while (buf[i] != ',' && buf[i] != '\n') {
                str += buf[i];
                i++;
            }
            char* end;
            double val = strtod(str.c_str(), &end);
            symTable::getInstance()->siMap.at(loc.at(count))->setVal(val);
            count++;
            i++;
            ///test
            cout << str << endl; //todo erase after done with test
        }
    }
    close(client_socket);
}

int OpenServerCommand::execute(vector<string> lexer, int ind) {

    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        cerr << "Could not create a socket"<<endl;
        return -1;
    }
    double port = Exp::inter(lexer.at(ind + 1));
    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(port); //we need to convert our number to a number that the network understands

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        cerr<<"Could not bind the socket to an IP"<<endl;
        return -2;
    }

    //making socket listen to the port
    if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
        cerr<<"Error during listening command"<<endl;
        return -3;
    } else {
        cout<<"Server is now listening ..."<<endl;
    }

    // accepting a client
    //socklen_t addrlen = sizeof(sockaddr_in);
    int client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &address);

    if (client_socket == -1) {
        cerr<<"Error accepting client"<<endl;
        return -4;
    } else {
        cout<<"Connected"<<endl;
    }

    close(socketfd); //closing the listening socket
/*
    thread thread1(receiveFromSim, client_socket); //
    thread1.join();*/

    Threads::getInstance()->server = thread(receiveFromSim, client_socket);
}

OpenServerCommand::OpenServerCommand() = default;