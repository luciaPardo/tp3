#include "RscGet.h"
#include "Message.h"
#include "Monitor.h"
#include <vector>
#include <string>

RscGet::RscGet(){}


std::string RscGet::get(const std::vector<std::string>& parsed,
                                                    Monitor& monitor){
    std::string resource = parsed[1];
    std::string response;
    if (resource.compare("/") == 0){
        response += "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";
        std::string body = monitor.pop("/");
        response += body;
    } else if (monitor.is(parsed[1])) {
        response += "HTTP/1.1 200 OK\n\n";
        std::string body = monitor.pop(resource);
        response += body;
    } else {
        response += "HTTP/1.1 404 NOT FOUND\n\n";
    }
    return response;
}
