#include "../common_src/Socket.h"
#include "Client.h"
#include<bits/stdc++.h>
#include <string>
#include <vector>
#include <iostream>
#include "../common_src/StringSender.h"


Client::Client(const char* host, const char* port)
    : skt()
{
    skt.clientConnect(host, port);
}

void Client::input(){
    std::cin >> std::noskipws;
    std::istream_iterator<char> it(std::cin);
    std::istream_iterator<char> end;
    std::string message(it, end);
    StringSender::sendMsg(skt, message);
    skt.shutDownChannel(1);
    std::string recieved = StringSender::recvMsg(skt);
    std::cout << recieved;
    return;
}

