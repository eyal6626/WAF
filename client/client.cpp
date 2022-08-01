#include "client.h"

Client::Client(){
    Config conf;
    conf.loadSettings();
    this->clientSock = new Socket(conf.getPort(),conf.getIp());
}

Client::~Client(){
    sendLogout(getUsername());
    delete this->clientSock;
}

/*
The function recive message from the socket
input:none
output:the message
*/
std::string Client::getServerMsg(){
    return this->clientSock->reciveMessage();
}

/*
The function send a login message to the server
input:the username, the password of the username
output:none
*/
void Client::sendLogin(std::string name, std::string password){
    this->clientSock->sendMessage(this->protocol.loginReq(name,password));
}

/*
The function send a signup message
input:username, password, email
output:none
*/
void Client::sendSignup(std::string username,std::string password,std::string email){
    this->clientSock->sendMessage(this->protocol.signup(username,password,email));
}

/*
The function ask from the server for the user log
input: the username
output:none
*/
void Client::sendGetLog(std::string username){
    this->clientSock->sendMessage(this->protocol.getLog(username));
}

/*
The function send a logout message
input:the username of the user that want to logout
output:none
*/
void Client::sendLogout(std::string username){
     this->clientSock->sendMessage(this->protocol.logout(username));
}

/*
The function send a message to the log on the server
input:the path of the log, the username
output:none
*/
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
    if(logData != ""){
        this->clientSock->sendMessage(this->protocol.userSendLog(logData,username));
        std::ofstream fileClose;
        fileClose.open(logPath);
        fileClose.close();
    }

}

/*
Get function for the usernaem
input:none
output:the username
*/
std::string Client::getUsername(){
    return this->username;
}

/*
Set function that change the username
input:the new username
output:none
*/
void Client::setUsername(std::string user){
    this->username = user;
}

/*
Set function that change the password
input:the new password
output:none
*/
void Client::setPassword(std::string pass){
    this->password = pass;
}
