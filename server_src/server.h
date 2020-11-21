#ifndef TP3_SERVIDOR_H
#define TP3_SERVIDOR_H
#include <vector>
#include "Peer.h"
#include "Monitor.h"
#include "thread.h"
#include "ServerOutput.h"
#include "../common_src/SocketAcceptor.h"
#include "../common_src/SocketClient.h"

class Server : public Thread {
private:
    void endServer();
    void destroyZombies(std::vector<Peer*>& threads);
    std::vector<Peer*> clients;
    char* port;
    char* root;
    SocketAcceptor skt_listener;

public:
    std::atomic<bool> serv_online;
    Monitor monitor;
    Server(char* port, char* root);
    void shutDown();
    virtual void run() override;
    void operator()();
};

#endif
