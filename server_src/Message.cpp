#include "Message.h"
#include "RscGet.h"
#include "RscPost.h"
#include "RscNotValid.h"
#include "Monitor.h"
#include <vector>
#include <string>
#include <iostream>

Message::Message(){}

std::string Message::get(const std::vector<std::string>& parsed,
                                                    Monitor& monitor){
    std::string response;
    if (parsed[0].compare("GET") == 0){
        RscGet resourse;
        response = resourse.get(parsed, monitor);
    } else if (parsed[0].compare("POST") == 0) {
        RscPost resourse;
        response = resourse.get(parsed, monitor);
    } else {
        RscNotValid resource;
        response = resource.get(parsed, monitor);
    }
    return response;
}
