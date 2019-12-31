
//
// Created by ofirn93 on 23/12/2019.
//

#include "OpenServerCommand.h"
#include "Substring.h"
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>
#include <vector>
#include <thread>

#define PORT 5400

using namespace std;

OpenServerCommand::OpenServerCommand() = default;

void receiveFromSim(int client_socket) {
    auto substr = new Substring();

    //now buffer holds the values sent from the simulator
    //I need to go over the first 36 values, delimited by ',' , and update the smap accordingly
    //This will be done in the following manner:
    //the i'th value in the buffer will update the loc[i]'th key's value in the map
    //updating the value will actually be updating the "value" member in the key's value which is a Var*

    for (int i=0; i<36; i++) {
        //todo check that sending buffer as a string (while it's a char[]) doesn't cause any bugs
        //string str = substr->create(',', buffer, &i);
        //symTable::getInstance()->smap.at(loc[i])->getVar(name, val).val = str;
    }
    delete substr;
    close(client_socket);
}

int OpenServerCommand::execute(vector<string> arr, int ind) {
    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        cerr << "Could not create a socket"<<endl;
        return -1;
    }

    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(PORT/*stoi(arr.at(ind+1))*/);
    //we need to convert our number to a number that the network understands.

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        cerr<<"Could not bind the socket to an IP"<<endl;
        return -2;
    }

    //making socket listen to the port
    if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
        cerr<<"Error during listening command"<<endl;
        return -3;
    } /*else{
        cout<<"Server is now listening ..."<<endl;
    }*/

    // accepting a client
    socklen_t addrlen = sizeof(sockaddr_in);
    int client_socket = accept(socketfd, (struct sockaddr*)&address, &addrlen);

    if (client_socket == -1) {
        cerr<<"Error accepting client"<<endl;
        return -4;
    }

    close(socketfd); //closing the listening socket

    thread thread2(receiveFromSim, client_socket); //todo maybe thread should be singleton
    //todo check if join/detach should be written here and if not then where

    return 2;
}