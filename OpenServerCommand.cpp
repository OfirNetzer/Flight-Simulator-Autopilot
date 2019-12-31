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

#define PORT 8081

using namespace std;

OpenServerCommand::OpenServerCommand() = default;

void receiveFromSim(char buffer[]) {
    auto substr = new Substring();

    //now buffer holds the values sent from the simulator
    //I need to go over the first 36 values, delimited by ',' , and update the smap accordingly
    //This will be done in the following manner:
    //the i'th value in the buffer will update the loc[i]'th key's value in the map
    //updating the value will actually be updating the "value" member in the key's value which is a Var*

    for (int i=0; i<36; i++) {
        //todo check that sending buffer as a string (while it's a char[]) doesn't cause any bugs
        string str = substr->create(',', buffer, &i);
        //symTable::getInstance()->smap.at(loc[i])->getVar(name, val).val = str;
    }
}

int OpenServerCommand::execute(vector<string> arr, int i) {
    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        cerr << "Could not create a socket"<<endl;
        return -1;
    }

    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address{}; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(PORT);
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
    } else{
        cout<<"Server is now listening ..."<<endl;
    }

    // accepting a client
    int client_socket = accept(socketfd, (struct sockaddr*)&address, (socklen_t*)&address);

    if (client_socket == -1) {
        cerr<<"Error accepting client"<<endl;
        return -4;
    }

    //reading from client
    char buffer[1024] = {0};
    int valread = read(client_socket, buffer, 1024);
    if (valread < 1){
        cerr << "Cannot read values from simulator";
        return -5;
    }

/*    ///test
    cout<<buffer<<endl;

    //writing back to client
    char hello[] = "Hello, I can hear you! \n";
    send(client_socket , hello , strlen(hello) , 0 );
    cout<<"Hello message sent\n"<<endl;

     ///end test*/

    close(socketfd); //closing the listening socket

    //thread thread1(receiveFromSim, buffer);
    //todo check if join/detach should be written here

    return 0;
}