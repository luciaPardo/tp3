
#ifndef _MONITOR_H
#define _MONITOR_H

#include <vector>
#include "common_thread.h"
#include <string>
#include <cstring>
#include <mutex>
#include <unordered_map>


class Monitor {
    std::mutex mtx;
    std::unordered_map<std::string,std::string> resources;

public:
    Monitor();
    void insert(std::string key, std::string value);
    std::string& access(std::string key);
    bool is(std::string key);
};

#endif
