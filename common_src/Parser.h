#ifndef TP3_PARSER_H
#define TP3_PARSER_H

#include <sys/types.h>
#include <string>
#include <sstream>
#include <vector>

class Parser {
    std::stringstream petitorios;
    void identifyCmd(std::string& petitoriosInput,
                     std::vector<std::string>& parsed,
                     std::string delim);
    void split(const std::string& str, std::vector<std::string>& instruccion);
public:
    Parser();
    void stream(std::string& petitorios, std::vector<std::string>& parsed);
};
#endif
