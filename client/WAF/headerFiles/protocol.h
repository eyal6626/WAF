#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <iostream>
#include <string>

class Protocol{
    public:
    Protocol();
    
    //login
    std::string loginReq(std::string username,std::string password);
    std::string loginSucc();
    std::string loginFailed();

    //signin
    std::string signup(std::string username,std::string password,std::string email);
    std::string signinSucc();
    std::string signinInvalidDB();
    std::string signinInvalidPass();
    std::string signinInvalidUsername();

    //log
    std::string getLog(std::string username);
    std::string sendLog(std::string logData);
    std::string failInFindingLog();
    std::string userSendLog(std::string logData,std::string username);

    //Logout
    std::string logout(std::string username);

};

#endif
