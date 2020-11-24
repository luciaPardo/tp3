#include "Parser.h"
#include <sys/types.h>
#include <string>
#include <vector>
#include <string.h>
#include <iterator>
#include <algorithm>

Parser::Parser()
 : petitorios()
{}

void Parser::stream(std::string& petitoriosInput,
                                         std::vector<std::string>& parsed){
    identifyCmd(petitoriosInput, parsed, "\n");
    identifyCmd(petitoriosInput, parsed, "\n\n");
}

void Parser::identifyCmd(std::string& petitoriosInput,
                                    std::vector<std::string>& parsed,
                                    std::string delim){
    std::vector<std::string> aux;
    size_t cmd_pos = petitoriosInput.find(delim);
    if (cmd_pos != std::string::npos){
        if (delim.compare("\n\n") == 0){
            std::string  body = petitoriosInput.substr(cmd_pos + 2,
                                            petitoriosInput.length());
            if (!body.empty())
                parsed.push_back(body);
            return;
        }
        split(petitoriosInput.substr(0, cmd_pos), aux);
        for (unsigned int i = 0; i < aux.size(); i++){
            parsed.push_back(aux[i]);
        }
    }
        petitoriosInput.erase(0, cmd_pos);
}

void Parser::split(const std::string& str,
                                std::vector<std::string>& instruccion){
    std::istringstream iss(str);
    std::copy(std::istream_iterator<std::string>(iss),
              std::istream_iterator<std::string>(),
              std::back_inserter(instruccion));
}

