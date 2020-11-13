
#include "ServerOutput.h"
#include <mutex>
#include <vector>
#include <string>
#include <iostream>

ServerOutput::ServerOutput()
: mtx()
{}

void ServerOutput::printOutput(const std::vector<std::string>& parsed){
    std::lock_guard<std::mutex> lck(mtx);
    std::string output = parsed[0];
    std::cout << output << " " << parsed[1] << " " << parsed[2] << "\n";
}

ServerOutput::~ServerOutput() {}
