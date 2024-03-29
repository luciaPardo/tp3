#include "Monitor.h"
#include <vector>
#include <bits/stdc++.h>
#include <unordered_map>
#include <mutex>
#include <cstring>
#include <string>
#include <utility>

Monitor::Monitor()
    :  mtx(), resources()
{}

void Monitor::insert(const std::string& key, const std::string& value){
    std::lock_guard<std::mutex> lck(mtx);
    resources.insert(std::make_pair(key, value));
}

std::string& Monitor::access(const std::string& key){
    std::lock_guard<std::mutex> lck(mtx);
   return resources[key];
}


bool Monitor::is(const std::string& key){
    std::lock_guard<std::mutex> lck(mtx);
    std::unordered_map<std::string,std::string>::const_iterator valor
                                                = resources.find(key);
    return (valor != resources.end());
}



