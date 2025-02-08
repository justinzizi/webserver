#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <cassert>

#include<string.h>



class WebServer{
    public:
    WebServer();
    ~WebServer();


    void eventListen();
    bool dealclientdata();
    void dealwithread(int sockfd);
    void dealwithwrite(int sockfd);




public:
    int m_port;
    int m_listenfd;
    int m_OPT_LINGER;
    int m_LISTENrigmode;
};



#endif