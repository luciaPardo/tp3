#include "Peer.h"
#include "Parser.h"
#include <sstream>
#include <iostream>
#include "StringSender.h"
#include "Message.h"
#include "ServerOutput.h"
#include <utility>

Peer::Peer(Socket skt, Monitor& monitor)
:   skt_peer(std::move(skt)),
    monitor(monitor),
    is_active(true),
    peer_online(true)
{}


void Peer::run(){
    Parser parse;
    std::string message = StringSender::recvMsg(skt_peer);
    std::string response = getResponse(message, monitor);
    StringSender::sendMsg(skt_peer, response);
    skt_peer.shutDownChannel(1);
    peer_online = false;
}

std::string Peer::getResponse(std::string& message, Monitor& monitor){
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


