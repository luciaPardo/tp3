#ifndef TP3_STRINGSENDER_H
#define TP3_STRINGSENDER_H

#include <string>
#include "SocketClient.h"

namespace StringSender {
    void sendMsg(SocketClient& socket, const std::string &message);
    std::string recvMsg(SocketClient& socket);
}


#endif
