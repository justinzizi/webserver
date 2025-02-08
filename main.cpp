#include "config.h"
#include <iostream>
#include "webserver.h"

int main()
{
    WebServer server; 
    server.eventListen();
    std::cout << "Server is listening on port 8080..." << std::endl;
    return 0;
}