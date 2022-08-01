#include "socket.h"

Socket::Socket(int port,std::string ip){
    this->_ip = ip;
    this->_port = port;
    this->_sock = socket(AF_INET,SOCK_STREAM,0);
    if(this->_sock == -1){
        return;
        std::cout << "\n\nError while creating socket!\nPress any key to close the program!";
        exit(1);
    }

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(this->_port);
    if(inet_pton(AF_INET,this->_ip.c_str(),&hint.sin_addr) <= 0){
        std::cout << "\n\nError IP\nPress any key to close the program!";
        exit(1);   
    }

    //Connect the socket to the server
    int connectRes = connect(this->_sock, (struct sockaddr*)&hint, sizeof(hint));
    if(connectRes == -1){
        std::cout << "\n\nError while connecting to server!\nPress any key to close the program!";
        exit(1);      
    }

}

Socket::~Socket(){
    close(this->_sock);
}

bool Socket::sendMessage(std::string msg){
    int sendRes = send(this->_sock, msg.c_str(), msg.size() + 1, 0);
    return sendRes == -1;
}

std::string Socket::reciveMessage(){
    memset(buf,0,LEN);
    int rec = recv(this->_sock,this->buf,LEN,0);
    if(rec == -1){
        return ERROR_IN_GETTING_MSG_FROM_THE_SERVER;
    }
    else{
        std::string data((char *)buf);
        return data;
    }
}
