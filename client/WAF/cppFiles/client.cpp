#include "../headerFiles/client.h"

Client::Client(){
    this->clientSock = new Socket(PORT,IP);
}

Client::~Client(){
    sendLogout(getUsername());
    delete this->clientSock;
}

std::string Client::getServerMsg(){
    return this->clientSock->reciveMessage();
}

void Client::sendLogin(std::string name, std::string password){
    this->clientSock->sendMessage(this->protocol.loginReq(name,password));
}

void Client::sendSignup(std::string username,std::string password,std::string email){
    this->clientSock->sendMessage(this->protocol.signup(username,password,email));
}

void Client::sendGetLog(std::string username){
    this->clientSock->sendMessage(this->protocol.getLog(username));
}

void Client::sendLogout(std::string username){
     this->clientSock->sendMessage(this->protocol.logout(username));
}

void Client::sendLogDataToServer(std::string logPath,std::string username){
    std::ifstream file(logPath);
    std::string logData = "";
    std::string line = "";
    if(file.is_open()){
        while(getline(file,line)){
            logData = logData + "*" + line;
        }
        file.close();
    }
    std::cout << "\nsend: " << logData << std::endl;
    if(logData != ""){
        this->clientSock->sendMessage(this->protocol.userSendLog(logData,username));
        std::ofstream fileClose;
        fileClose.open(logPath);
        fileClose.close();
    }

}

std::string Client::getUsername(){
    return this->username;
}

void Client::setUsername(std::string user){
    this->username = user;
}


void Client::setPassword(std::string pass){
    this->password = pass;
}

bool Client::isSocketConnected(){
    return this->clientSock->isConnected();
}