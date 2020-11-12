#ifndef TP3_STRINGSENDER_H
#define TP3_STRINGSENDER_H

#include <string>
#include "Socket.h"

namespace StringSender {
    void sendMsg(Socket& socket, std::string &message);
    std::string recvMsg(Socket& socket);
}


#endif
