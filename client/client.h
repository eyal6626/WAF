#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include "socket.h"
#include "protocol.h"
#include "config.h"

class Client{
    public:
    Client();
    ~Client();
    void sendLogin(std::string name, std::string password);
    void sendSignup(std::string username,std::string password,std::string email);
    void sendGetLog(std::string username);
    void sendLogout(std::string username);
    void sendLogDataToServer(std::string logPath,std::string username);
    void setUsername(std::string user);
    void setPassword(std::string pass);
    std::string getUsername();
    std::string getServerMsg();
    private:
    Socket* clientSock;
    Protocol protocol;
    std::string username;
    std::string password;
};

#endif
