
#ifndef TP3_CLIENT_H
#define TP3_CLIENT_H
#include<bits/stdc++.h>
#include "../common_src/SocketClient.h"
#include <string>
#include <vector>

class Client {
    SocketClient skt;
public:
    Client(const char * host, const char* port);
    int connect();
    void input();
};

#endif
