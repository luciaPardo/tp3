#ifndef TP3_SOCKETCLIENT_H
#define TP3_SOCKETCLIENT_H
#include "Exception.h"


class SocketClient {
    int fd;
    void configInfo(bool serv_flag,const char* port, const char* host,
                                         struct addrinfo** results);
    void connect(int fd, struct addrinfo* ptr);
public:
    SocketClient& operator=(SocketClient &&other)noexcept;
    explicit SocketClient(int filedescriptor);
    SocketClient(SocketClient &&other);
    SocketClient(SocketClient&) = delete;
    SocketClient(const char* host, const char* port);
    ssize_t send(char msg[], size_t msg_size);
    ssize_t recieve(char* msg, ssize_t msg_size);
    void shutDownChannel(int channel_write);
    ~SocketClient();
};
#endif
