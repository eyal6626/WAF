#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <thread>
#include <vector>
#include <fstream>
#include "DB.h"
#include "protocol.h"
#include <regex>

#define SERVERPORT 6968
#define BUFSIZE  4096
#define SOCKETERROR (-1)
#define SERVER_BACKLOG 1
#define CLOSE_SOCKET "401"

typedef struct sockaddr_in SA_IN;
typedef struct sockaddr SA;

class Server
{
private:
    std::vector<std::string> users;
    DB* database;
    Protocol protocol;
    int serverSocket;
    int clientSocket;
    int addrSize;
    SA_IN serverAddr;
    SA_IN clientAddr;
    void checkForError(int answerCode, std::string msg);
    void handleClientMsg(int client_socket);
    std::string checkLogin(std::string msg);
    std::string checkRequestType(std::string req);
    std::string requestHandler(std::string reqCode, std::string req);
    std::string checkSignup(std::string msg);
    std::string getLogReq(std::string msg);
    std::string readDatafromLog(std::string logPath);
    std::string doLogout(std::string msg);
    void addDataToLog(std::string msg);
public:
    void serve();
    Server();
    ~Server();
};


