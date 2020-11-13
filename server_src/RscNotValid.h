
#ifndef TP3_RSCNOTVALID_H
#define TP3_RSCNOTVALID_H
#include "Message.h"
#include "Monitor.h"
#include <vector>
#include <string>


class RscNotValid : public Message{
public:
    RscNotValid();
    std::string get(const std::vector<std::string>& parsed, Monitor& monitor);
};

#endif
