#include "Client.h"
#include <iostream>
#include "../common_src/Exception.h"
#define MSG_ERROR_UNKNW "ERROR DESCONOCIDO"
#define MIN_ARGS 3
#define QUIT 'q'
#define HOST 1
#define PORT 2


int main(int argc, char* argv[]){
    if (argc < MIN_ARGS){
        std::cerr << "ERROR cant parámetros" << std::endl;
        return 1;
    }
    try{
        Client client(argv[HOST], argv[PORT]);
        client.input();
    } catch (Exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << MSG_ERROR_UNKNW << std::endl;
    }
    return 0;
}
