
#include "Socket.h"
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
#define MAX_CLIENTS 20
#define MAX_BYTES 64


Socket::Socket(Socket &&other) : fd(other.fd) {
    other.fd = -1;
}

Socket& Socket::operator=(Socket &&other)noexcept{
    this->fd = other.fd;
    other.fd = -1;
    return *this;
}
Socket::Socket()
    : fd(-1)
{}
Socket::Socket(int fd)
    : fd(fd)
{}
void Socket::connect(int fd, struct addrinfo *ptr) {
    int err = ::connect(fd, ptr->ai_addr, ptr->ai_addrlen);
    if (err < 0)
        throw Exception("Falló el socket connect: ", errno);
}

bool Socket::bindAndListen(int fd,struct sockaddr *ai_addr,
                                                    socklen_t ai_addrlen){
    int option = 1;
    int err_sktopt = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &option,
                                                            sizeof(option));
    if (err_sktopt) throw Exception("Error setsockopt", errno);
    int err = ::bind(fd, ai_addr, ai_addrlen);
    if (err < 0) throw Exception("Error del bind: ", errno);
    int err_listen = ::listen(fd, MAX_CLIENTS);
    if (err_listen < 0) throw Exception("Error del Listen: ", errno);
    return true;
}

Socket Socket::acceptClient() {
    int fd_cliente = accept(fd, NULL, NULL);
    if (fd_cliente == -1 || fd == -1){
        throw Exception("Error accept: ", errno);
    }
    return Socket(fd_cliente);
}

ssize_t Socket::send(char msg[], size_t msg_size){
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

ssize_t Socket::recieve(char* msg, ssize_t msg_size) {
    if (msg_size == 0) return 0;
    ssize_t tot_bytes = 0;
    while (tot_bytes < msg_size){
        ssize_t new_bytes = ::recv(fd, &msg[tot_bytes],
                                   msg_size - tot_bytes,
                                   0);
        if (new_bytes == -1){
            fprintf(stderr, "Error del receive new bytes: %s \n",
                    strerror(errno));
            return -1;
        }else if (new_bytes == 0){
            return tot_bytes;
        } //else if (new_bytes < MAX_BYTES){
//            return new_bytes;
//        }
        tot_bytes += new_bytes;
    }
    return tot_bytes;
}


void Socket::serverConnect(const char* port) { //connect to port
    struct addrinfo* results;
    struct addrinfo* ptr;
    bool is_connected = false;
    configInfo(true, port, NULL, &results);
    for (ptr = results; ptr != NULL && !is_connected; ptr = ptr->ai_next){
        fd = ::socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (fd == -1){
            throw Exception("Fallo de creación de Socket en server connect");
        }
        bindAndListen(fd, results->ai_addr, results->ai_addrlen);
        is_connected = true;
    }
    freeaddrinfo(results);
}


void Socket::clientConnect(const char* host, const char* port) {
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



void Socket::configInfo(bool serv_flag,const char* port, const char* host,
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


Socket::~Socket() {
    if (fd == -1) return;
    ::shutdown(fd, SHUT_RDWR); //cierro ambos lados
    ::close(fd);
}

void Socket::forceShutDown() {
    if (shutdown(fd, SHUT_RDWR) == -1) //cierro ambos lados
        throw Exception("Error en el forceShutDown: %s", errno);
    if (close(fd) == -1)
        throw Exception("Error en el forceShutDown: %s", errno);
}

void Socket::shutDownChannel(int channel_write) {
    if (fd == -1) return;
    if (channel_write == 1){
        ::shutdown(fd, SHUT_WR);
    } else{
        ::shutdown(fd, SHUT_RD);
    }
}
