#ifndef TP3_SOCKETACCEPTOR_H
#define TP3_SOCKETACCEPTOR_H
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include "Exception.h"
#include <sstream>
#include <vector>
#include "SocketClient.h"
#define MAX_CLIENTS 20

class SocketAcceptor{
    int fd;
    void configInfo(bool serv_flag,const char* port, const char* host,
                                         struct addrinfo** results);
    bool bindAndListen(int fd, struct sockaddr* ai_addr, socklen_t ai_addrlen);
public:
    SocketClient acceptClient();
    explicit SocketAcceptor(const char* port);
    void forceShutDown();
    void shutDownChannel(int channel_write);
    ~SocketAcceptor();
};

#endif
