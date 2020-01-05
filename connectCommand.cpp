
//
// Created by ofirn93 on 23/12/2019.
//

#include "connectCommand.h"
#include "Queue.h"
#include "Flag.h"
#include "Threads.h"
#include "Exp.h"
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <vector>
#include <thread>
#include <pthread.h>

using namespace std;

connectCommand::connectCommand() = default;

void sendToSim(int client_socketfd) {
    while (Flag::getInstance()->threadFlag) {
        while (!(Queue::getInstance()->q.empty())) {
            string str = Queue::getInstance()->q.front();
            int is_sent = send(client_socketfd, str.c_str(), str.length(), 0);
            if (is_sent == -1) {
                std::cout << "Error sending message" << std::endl;
            }
            cout << Queue::getInstance()->q.front() << endl; //todo erase after done with test
            Queue::getInstance()->q.pop();
        }
        /*Flag::getInstance()->threadFlag = false;
        cout << "client thread finished" << endl;*/
    }
    close(client_socketfd);
}

int connectCommand::execute(vector<string> lexer, int ind) {
    //create socket
    int client_socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socketfd == -1) {
        //error
        std::cerr << "Could not create a socket"<<std::endl;
        return -1;
    }

    const char* ip = lexer.at(ind + 1).c_str();
    cout << ip << endl; //todo erase after done testing it
    double port = Exp::inter(lexer.at(ind + 2));
    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    //todo change ip and port to be read from the array, like the two lines above
    address.sin_addr.s_addr = inet_addr(ip); //give me any IP allocated for my machine //todo find out why this doesn't work
    address.sin_port = htons(port);
    //we need to convert our number to a number that the network understands.

    int is_connect = connect(client_socketfd, (struct sockaddr *)&address, sizeof(address));
    if (is_connect == -1) {
        std::cerr << "Could not connect to host server" << std::endl;
        return -2;
    } else {
        std:: cout << "Client is now connected to server"<< std::endl;
    }
/*

    thread thread2(sendToSim, client_socketfd);
    thread2.join();
*/
    Threads::getInstance()->client = thread(sendToSim, client_socketfd);

    return 3;
}