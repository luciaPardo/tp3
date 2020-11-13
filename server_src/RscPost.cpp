
#include "RscPost.h"
#include "Message.h"
#include "Monitor.h"
#include <vector>
#include <string>
#include <unordered_map>


RscPost::RscPost(){}


std::string RscPost::get(const std::vector<std::string>& parsed,
                                                    Monitor& monitor){
    std::string response;
    std::string resource = parsed[1]; //metodo recurso protocolo
    if (resource.compare("/") == 0) {
        response += "HTTP/1.1 403 FORBIDDEN\n\n";
        return response;
    }
    response += "HTTP/1.1 200 OK\n\n";
    monitor.insert(resource, parsed[3]);
    response += parsed[3];
    return response;
}
