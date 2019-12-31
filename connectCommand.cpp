//
// Created by ofirn93 on 23/12/2019.
//

#include "connectCommand.h"
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <vector>
#include <thread>

#define PORT 8081

using namespace std;

connectCommand::connectCommand() = default;

void sendToSim(char buffer[]) {

    //cout << "set " + c.sim + c.value << endl;
}

int connectCommand::execute(vector<string> arr, int i) {
    //create socket
    int client_socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socketfd == -1) {
        //error
        std::cerr << "Could not create a socket"<<std::endl;
        return -1;
    }

    //bind socket to IP address
    // we first need to create the sockaddr obj.
    //todo handle warning in the next row, might fix the problem
    sockaddr_in address{}; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1"); //give me any IP allocated for my machine
    address.sin_port = htons(PORT);
    //we need to convert our number to a number that the network understands.

    int is_connect = connect(client_socketfd, (struct sockaddr *)&address, sizeof(address));
    if (is_connect == -1) {
        std::cerr << "Could not connect to host server" << std::endl;
        return -2;
    } else {
        std:: cout << "Client is now connected to server"<< std::endl;
    }

/*
    ///test
    char hello[] = "Hi from client";
    int is_sent = send(client_socketfd, hello, strlen(hello), 0);
    if (is_sent == -1) {
        std::cout << "Error sending message" << std::endl;
    } else {
        std::cout << "Hello message sent to server" << std::endl;
    }*/

    char buffer[1024] = {0};
    int valread = read(client_socketfd, buffer, 1024);
    if (valread < 1){
        cerr << "Cannot read values from the computer";
        return -3;
    }

/*    ///test
    std::cout << buffer << std::endl;*/

    close(client_socketfd);

//    thread thread1(sendToSim, buffer);
//    thread1.detach();

    return 0;
}