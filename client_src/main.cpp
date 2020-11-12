#include "Client.h"
#include <iostream>
#define MIN_ARGS 3
#define QUIT 'q'


int main(int argc, char* argv[]){
    if (argc < MIN_ARGS){
        std::cerr << "ERROR cant parámetros" << std::endl;
        return 1;
    }
    Client client(argv[1], argv[2]);
    client.input();
    return 0;
}
