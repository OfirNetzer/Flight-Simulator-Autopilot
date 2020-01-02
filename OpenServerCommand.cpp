//
// Created by avichai on 01/01/2020.
//

#include "OpenServerCommand.h"
#include "Flag.h"
#include "symTable.h"
#include "Substring.h"
//#include "Exp.h"
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>
#include <vector>
#include <thread>

using namespace std;

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
    loc[16] = "instrumentation/turn-indicator/indicated-turn-rate";
    loc[17] = "instrumentation/vertical-speed-indicator/indicated-speed-fpm";
    loc[18] = "controls/flight/aileron";
    loc[19] = "controls/flight/elevator";
    loc[20] = "controls/flight/rudder";
    loc[21] = "controls/flight/flaps";
    loc[22] = "controls/engines/engine/throttle";
    loc[23] = "controls/engines/current-engine/throttle";
    loc[24] = "controls/switches/master-avionics";
    loc[24] = "controls/switches/starter";
    loc[25] = "engines/active-engine/auto-start";
    loc[26] = "controls/flight/speedbrake";
    loc[27] = "sim/model/c172p/brake-parking";
    loc[28] = "controls/engines/engine/primer";
    loc[29] = "controls/engines/current-engine/mixture";
    loc[30] = "controls/switches/master-bat";
    loc[31] = "controls/switches/master-alt";
    loc[32] = "engines/engine/rpm";
    //todo complete 36

    return loc;
}

void receiveFromSim(int client_socket) {
    vector<string> loc = OpenServerCommand::createLoc();
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
            string str = Substring::create(',', buf, &i);
            symTable::getInstance()->siMap.at(loc.at(count))->setVal(stod(str));
            count++;
            i++;
            ///test
            cout << str << endl;
        }
    }
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
//    int port = stoi(arr.at(ind+1));
    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(5400);
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
    //socklen_t addrlen = sizeof(sockaddr_in);
    int client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &address);

    if (client_socket == -1) {
        cerr<<"Error accepting client"<<endl;
        return -4;
    } else {
        cout<<"Connected"<<endl;
    }

    close(socketfd); //closing the listening socket

    thread thread1(receiveFromSim, client_socket); //todo maybe thread should be singleton
    thread1.join();
    //todo check if join/detach should be written here and if not then where
}

OpenServerCommand::OpenServerCommand() = default;