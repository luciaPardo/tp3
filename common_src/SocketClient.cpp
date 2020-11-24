#include "SocketClient.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string>
#include <unistd.h>
#include <cstring>
#include "Exception.h"
#include <sstream>
#include <vector>

SocketClient::SocketClient(int filedescriptor)
    : fd(filedescriptor)
{}


SocketClient& SocketClient::operator=(SocketClient &&other)noexcept{
    this->fd = other.fd;
    other.fd = -1;
    return *this;
}

SocketClient::SocketClient(SocketClient &&other) : fd(other.fd){
    other.fd = -1;
}

void SocketClient::connect(int fd, struct addrinfo *ptr) {
    int err = ::connect(fd, ptr->ai_addr, ptr->ai_addrlen);
    if (err < 0)
        throw Exception("Falló el socket connect: ", errno);
}

SocketClient::SocketClient(const char* host, const char* port) {
    struct addrinfo* results;
    struct addrinfo* ptr;
    bool is_connected = false;
    configInfo(true, port, NULL, &results);
    for (ptr = results; ptr != NULL && !is_connected; ptr = ptr->ai_next){
        fd = ::socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        connect(fd, ptr);
        is_connected = true;
    }
    freeaddrinfo(results);
}


ssize_t SocketClient::send(char msg[], size_t msg_size){
    if (msg_size == 0) return 0;
    size_t tot_bytes = 0;
    while (tot_bytes < msg_size){
        ssize_t bytes = ::send(fd, &msg[tot_bytes], msg_size - tot_bytes,
                             MSG_NOSIGNAL);
        if (bytes == -1) {
            throw Exception("Error enviando mensaje Socket::send: ", errno);
            return -1;
        }
        if (bytes == 0)
            return 0;
        else
            tot_bytes += bytes;
    }
    return tot_bytes;
}

ssize_t SocketClient::recieve(char* msg, ssize_t msg_size) {
    if (msg_size == 0) return 0;
    ssize_t tot_bytes = 0;
    while (tot_bytes < msg_size){
        ssize_t new_bytes = ::recv(fd, &msg[tot_bytes],
                                   msg_size - tot_bytes,
                                   0);
        if (new_bytes == -1){
            throw Exception("Error en el recieve (socket): ",errno);
            return -1;
        }else if (new_bytes == 0){
            return tot_bytes;
        }
        tot_bytes += new_bytes;
    }
    return tot_bytes;
}

void SocketClient::configInfo(bool serv_flag,const char* port, const char* host,
                                         struct addrinfo** results){
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = serv_flag ? AI_PASSIVE : 0;
    if (getaddrinfo(host, port, &hints, results) != 0) {
        freeaddrinfo(*results);
        throw Exception("Error en gettadrinfo (configInfo): ", errno);
    }
}


void SocketClient::shutDownChannel(int channel_write) {
    if (fd == -1) return;
    if (channel_write == 1){
        ::shutdown(fd, SHUT_WR);
    } else{
        ::shutdown(fd, SHUT_RD);
    }
}

SocketClient::~SocketClient() {
    if (fd == -1) return;
    ::shutdown(fd, SHUT_RDWR); //cierro ambos lados
    ::close(fd);
}
