#ifndef TP3_SERVIDOR_H
#define TP3_SERVIDOR_H
#include <vector>
#include "../common_src/Peer.h"
#include "../common_src/Monitor.h"
#include "../common_src/common_thread.h"
#include "../common_src/ServerOutput.h"
class Server : public Thread {
private:
    void endServer();
    void destroyZombies(std::vector<Peer*>& threads);
    std::vector<Peer*> clients;
    char* port;
    char* root;
    Socket skt_listener;

public:
    std::atomic<bool> serv_online;
    Monitor monitor;
    Server(char* port, char* root);
    void shutDown();
    virtual void run() override;
    void operator()();
};

#endif
