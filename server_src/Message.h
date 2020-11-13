#ifndef TP3_MESSAGE_H
#define TP3_MESSAGE_H
#include "Monitor.h"
#include <vector>
#include <string>


class Message {
public:
    Message();
    std::string get(const std::vector<std::string>& parsed, Monitor& monitor);
};

#endif
