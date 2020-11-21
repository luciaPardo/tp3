#ifndef _MONITOR_H
#define _MONITOR_H

#include <vector>
#include <string>
#include <cstring>
#include <mutex>
#include <unordered_map>


class Monitor {
    std::mutex mtx;
    std::unordered_map<std::string,std::string> resources;

public:
    Monitor();
    void insert(const std::string& key, const std::string& value);
    std::string& access(const std::string& key);
    bool is(const std::string& key);
};

#endif
