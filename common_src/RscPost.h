#ifndef TP3_RSCPOST_H
#define TP3_RSCPOST_H
#include "Message.h"
#include "Monitor.h"
#include <vector>
#include <string>


class RscPost : public Message{
public:
    RscPost();
    std::string get(const std::vector<std::string>& parsed, Monitor& monitor);
};



#endif
