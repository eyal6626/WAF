#ifndef SOCKET_H
#define SOCKET_H

#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string>
#include <string.h>
#include <iostream>

#define LEN 4096
#define ERROR_IN_GETTING_MSG_FROM_THE_SERVER ""

class Socket{
    public:
    Socket(int port,std::string ip);//C'tor open socket with the server
    ~Socket();
    bool sendMessage(std::string msg);//Send message to the server 
    std::string reciveMessage();//Recive message from the server
    bool isConnected();
    
    private:
    int _port;
    std::string _ip;
    int _sock;
    char* buf[LEN];
    bool socketCreated = false;
};

#endif
