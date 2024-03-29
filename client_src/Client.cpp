#include "../common_src/SocketClient.h"
#include "Client.h"
#include<bits/stdc++.h>
#include <string>
#include <vector>
#include <iostream>
#include "../common_src/StringSender.h"
#define CHNL_WR 1


Client::Client(const char* host, const char* port)
    :  skt(host, port)
{}

void Client::input(){
    std::cin >> std::noskipws;
    std::istream_iterator<char> it(std::cin);
    std::istream_iterator<char> end;
    std::string message(it, end);
    StringSender::sendMsg(skt, message);
    skt.shutDownChannel(CHNL_WR);
    std::string recieved = StringSender::recvMsg(skt);
    std::cout << recieved;
    return;
}

