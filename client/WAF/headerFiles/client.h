#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include "../headerFiles/protocol.h"
#include "../headerFiles/socket.h"

#define PORT 6968
#define IP "127.0.0.1"

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
    bool isSocketConnected();

    private:
    Socket* clientSock;
    Protocol protocol;
    std::string username;
    std::string password;
};

#endif
