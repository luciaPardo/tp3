
#include "StringSender.h"
#include <sstream>
#include <string>
#include "Socket.h"
#include <iostream>
#include <vector>
#define MAX_BUFF 32


void StringSender::sendMsg(Socket &socket, std::string &message) {
    ssize_t msgsize = message.length();
    socket.send(const_cast<char*>(message.c_str()), msgsize);
}


std::string StringSender::recvMsg(Socket &socket) {
    char msg[MAX_BUFF] = {0};
    std::string mem("");
    while (true){
        ssize_t bytes = socket.recieve(msg,(ssize_t)MAX_BUFF);
        mem.append(msg, bytes);
        if (bytes <= 0)
            break;
    }
    return mem;
}
