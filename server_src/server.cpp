#include "server.h"
#include "Peer.h"
#include "../common_src/Exception.h"
#include "../common_src/SocketClient.h"
#include <iostream>
#include <sstream>
#include <string>
#include<bits/stdc++.h>
#include <utility>
#include <iostream>


Server::Server(char* port, char* root)
    : clients(),
      port(port),
      root(root),
      skt_listener(port),
      serv_online(true),
      monitor()

{
    std::string cast = std::string(root);
    std::ifstream file(cast);
    if (file) {
        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();
        std::string content = buffer.str();
        monitor.insert("/", content);
    }
}


void Server::operator()(){
    this->start();
}

void Server::run(){
    std::vector<Peer*> threads;
    clients = threads;
    while (serv_online){
        try {
            SocketClient skt_peer = std::move(skt_listener.acceptClient());
            Peer* new_peer = new Peer(std::move(skt_peer), this->monitor);
            clients.push_back(new_peer);
            new_peer->start();
        }
        catch (Exception& e) {
            break;
        }
        destroyZombies(clients);
    }
    endServer();
}

void Server::destroyZombies(std::vector<Peer*>& threads){
    std::vector<Peer*>::iterator it = threads.begin();
    while (it != threads.end()){
        if ((*it)->isDead()) {
            (*it)->join();
            delete *it;
            it = threads.erase(it);
        } else {
            ++it;
        }
    }
}

void Server::endServer(){
    std::vector<Peer*>::iterator it = clients.begin();
    while (it != clients.end()) {
        std::cout << (*it)->isDead() << std::endl;
        (*it)->join();
        delete *it;
        it = clients.erase(it);
        ++it;
        }
    }

void Server::shutDown(){
    serv_online = false;
    skt_listener.forceShutDown(); 
}
