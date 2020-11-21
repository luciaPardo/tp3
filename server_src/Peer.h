
#ifndef TP3_PEER_H
#define TP3_PEER_H
#include "thread.h"
#include "Monitor.h"
#include "../common_src/SocketClient.h"
#include "../common_src/SocketAcceptor.h"
#include <vector>
#include <string>
#include <atomic>
#include "ServerOutput.h"

class Peer : public Thread {
    SocketClient& skt_peer;
    Monitor& monitor;
    std::atomic<bool> is_active;
    std::atomic<bool> peer_online;
public:
    Peer(SocketClient skt_peer, Monitor& monitor);
    const std::string getResponse(std::string& message);
    void run() override;
    bool isDead();
};


#endif
