#include "SocketAcceptor.h"
#include "SocketClient.h"


SocketClient SocketAcceptor::acceptClient() {
    int fd_cliente = accept(fd, NULL, NULL);
    if (fd_cliente == -1 || fd == -1){
        throw Exception("Error accept: ", errno);
    }
    return SocketClient(fd_cliente);
}


bool SocketAcceptor::bindAndListen(int fd,struct sockaddr *ai_addr,
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

SocketAcceptor::SocketAcceptor(const char* port) { //connect to port
    struct addrinfo* results;
    struct addrinfo* ptr;
    bool is_connected = false;
    configInfo(true, port, NULL, &results);
    for (ptr = results; ptr != NULL && !is_connected; ptr = ptr->ai_next){
        fd = ::socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (fd == -1){
            freeaddrinfo(results);
            throw Exception("Fallo de creación de Socket en server connect");
        }
        bindAndListen(fd, results->ai_addr, results->ai_addrlen);
        is_connected = true;
    }
    freeaddrinfo(results);
}


void SocketAcceptor::configInfo(bool serv_flag,const char* port,
                                         const char* host,
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


SocketAcceptor::~SocketAcceptor() {
    if (fd == -1) return;
    ::shutdown(fd, SHUT_RDWR); //cierro ambos lados
    ::close(fd);
}

void SocketAcceptor::forceShutDown() {
    if (shutdown(fd, SHUT_RDWR) == -1)
        throw Exception("Error en el forceShutDown: %s", errno);
    if (close(fd) == -1)
        throw Exception("Error en el forceShutDown: %s", errno);
}

void SocketAcceptor::shutDownChannel(int channel_write) {
    if (fd == -1) return;
    if (channel_write == 1){
        ::shutdown(fd, SHUT_WR);
    } else{
        ::shutdown(fd, SHUT_RD);
    }
}
