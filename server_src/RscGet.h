
#ifndef TP3_GET_H
#define TP3_GET_H
#include "Message.h"
#include "Monitor.h"
#include <vector>
#include <string>


class RscGet : public Message {
public:
    RscGet();
    std::string get(const std::vector<std::string>& parsed, Monitor& monitor);
};


#endif
