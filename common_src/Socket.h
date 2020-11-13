#ifndef TP3_SOCKET_H
#define TP3_SOCKET_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string>

class Socket {
    int fd;
    void connect(int fd, struct addrinfo* ptr);
    bool bindAndListen(int fd, struct sockaddr* ai_addr, socklen_t ai_addrlen);
    void configInfo(bool serv_flag,const char* port, const char* host,
                                                struct addrinfo** results);
public:
    Socket();
    explicit Socket(int fd);
    Socket(Socket &&other);
    Socket& operator=(Socket &&other)noexcept;
    void connection(const char* host, const char* port);
    void bind(const char* port);
    Socket acceptClient();
    ssize_t send(char* msg, size_t msg_size);
    ssize_t recieve(char* msg, ssize_t msg_size);
    void forceShutDown();
    void shutDownChannel(int channel_write);
    ~Socket();
};


#endif
