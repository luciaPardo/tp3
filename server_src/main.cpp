#include "server.h"
#include <iostream>
#include "../common_src/Exception.h"

#define QUIT 'q'
#define MIN_ARGS 2

int main(int argc, char* argv[]){
    if (argc < MIN_ARGS){
        std::cerr << "ERROR cant parámetros" << std::endl;
        return 1;
    }
    try {
        Server server(argv[1], argv[2]);
        server();
        while (true) {
            if (getc(stdin) == QUIT) {
                server.shutDown();
                server.join();
                break;
            }
        }
    }
    catch(Exception &e){
            std::cerr << e.what() << std::endl;
            return 1;
    }
    return 0;
}
