
#ifndef TP3_PEER_H
#define TP3_PEER_H
#include "thread.h"
#include "Monitor.h"
#include "../common_src/Socket.h"
#include <vector>
#include <string>
#include <atomic>
#include "ServerOutput.h"

class Peer : public Thread {
    Socket skt_peer;
    Monitor& monitor;
    std::atomic<bool> is_active;
    std::atomic<bool> peer_online;
public:
    Peer(Socket skt_peer, Monitor& monitor);
    std::string getResponse(std::string& message, Monitor& monitor);
    void run() override;
    bool isDead();
};


#endif
