
#ifndef TP3_SERVEROUTPUT_H
#define TP3_SERVEROUTPUT_H
#include "common_thread.h"
#include <vector>
#include <string>
#include <mutex>

class ServerOutput{
    std::mutex mtx;
public:
    ServerOutput();
    void printOutput(const std::vector<std::string>& parsed);
    ~ServerOutput();
};


#endif
