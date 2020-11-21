#include "Peer.h"
#include "Parser.h"
#include <sstream>
#include <iostream>
#include "../common_src/StringSender.h"
#include "Message.h"
#include "ServerOutput.h"
#include <utility>

Peer::Peer(SocketClient skt, Monitor& monitor)
:   skt_peer(skt),
    monitor(monitor),
    is_active(true),
    peer_online(true)
{}


void Peer::run(){
    Parser parse;
    std::string message = StringSender::recvMsg(skt_peer);
    const std::string response = getResponse(message);
    StringSender::sendMsg(skt_peer, response);
    skt_peer.shutDownChannel(1);
    peer_online = false;
}

const std::string Peer::getResponse(std::string& message){
    Parser parser;
    ServerOutput stdout;
    std::vector<std::string> parsed;
    parser.stream(message, parsed);
    stdout.printOutput(parsed);
    Message msg;
    return msg.get(parsed, this->monitor);
}


bool Peer::isDead(){
    return peer_online;
}


