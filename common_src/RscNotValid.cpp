
#include "RscNotValid.h"
#include "Message.h"
#include "Monitor.h"
#include <vector>
#include <string>
#include <utility>

RscNotValid::RscNotValid(){}

std::string RscNotValid::get(const std::vector<std::string>& parsed,
                                                    Monitor& monitor){
    std::string response = "HTTP/1.1 405 METHOD NOT ALLOWED\n\n";
    response += parsed[0] + " es un comando desconocido\n";
    return response;
}
