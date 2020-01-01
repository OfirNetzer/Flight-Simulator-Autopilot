
//
// Created by ofirn93 on 23/12/2019.
//

#include "OpenServerCommand.h"
#include "Substring.h"
#include "Flag.h"
#include "symTable.h"
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>
#include <vector>
#include <thread>

using namespace std;

OpenServerCommand::OpenServerCommand() = default;

string* createLoc() {
    string loc[36];
    loc[0] = "instrumentation/airspeed-indicator/indicated-speed-kt";
    loc[1] = "sim/time/warp";
    loc[2] = "controls/switches/magnetos";
    loc[3] = "/instrumentation/heading-indicator/offset-deg";
    loc[4] = "instrumentation/altimeter/indicated-altitude-ft";
    loc[5] = "instrumentation/altimeter/pressure-alt-ft";
    loc[6] = "instrumentation/attitude-indicator/indicated-pitch-deg";
    loc[7] = "instrumentation/attitude-indicator/indicated-roll-deg";
    loc[8] = "instrumentation/attitude-indicator/internal-pitch-deg";
    loc[9] = "instrumentation/attitude-indicator/internal-roll-deg";
    loc[10] = "instrumentation/encoder/indicated-altitude-ft";
    loc[11] = "instrumentation/gps/indicated-ground-speed-kt";
    loc[12] = "instrumentation/gps/indicated-vertical-speed";
    loc[13] = "instrumentation/heading-indicator/indicated-heading-deg";
    loc[14] = "instrumentation/magnetic-compass/indicated-heading-deg";
    loc[15] = "instrumentation/slip-skid-ball/indicated-slip-skid";
    //todo complete 36

    return loc;
}

void receiveFromSim(int client_socket) {
    auto substr = new Substring();
    string* loc = createLoc();

    //now buffer holds the values sent from the simulator
    //I need to go over the first 36 values, delimited by ',' , and update the smap accordingly
    //This will be done in the following manner:
    //the i'th value in the buffer will update the loc[i]'th key's value in the map
    //updating the value will actually be updating the "value" member in the key's value which is a Var*
    while(Flag::getInstance()->threadFlag) {
        //reading from client
        char buffer[1024] = {0};
        int valread = read( client_socket , buffer, 1024);
        if (valread < 1) {
            cerr << "Error while reading from simulator" << endl;
        }
        string buf(buffer);
        int i=0, count=0;
        while (buf[i] != '\n') {
            string str = substr->create(',', buf, &i);
            symTable::getInstance()->siMap.at(loc[count])->setVal(stod(buf));
            count++;
            i++;
        }
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
    int port = stoi(arr.at(ind+1));
    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(port);
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
    } else {
        cout<<"Server is now listening ..."<<endl;
    }

    // accepting a client
    socklen_t addrlen = sizeof(sockaddr_in);
    int client_socket = accept(socketfd, (struct sockaddr*)&address, &addrlen);

    if (client_socket == -1) {
        cerr<<"Error accepting client"<<endl;
        return -4;
    }

    close(socketfd); //closing the listening socket

    createLoc();
    thread thread2(receiveFromSim, client_socket); //todo maybe thread should be singleton
    //todo check if join/detach should be written here and if not then where

    return 2;
}