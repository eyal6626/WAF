#include "protocol.h"

Protocol::Protocol(){

}

//login
std::string Protocol::loginReq(std::string username,std::string password){
    return "100|" + username + "|" + password;
}

std::string Protocol::loginSucc(){
    return "101";
}

std::string Protocol::loginFailed(){
    return "102";
}

//signin
std::string Protocol::signup(std::string username,std::string password,std::string email){
    return "200|" + username + "|" + password + "|" + email;
}

std::string Protocol::signinSucc(){
    return "201";
}

std::string Protocol::signinInvalidDB(){
    return "202";
}

std::string Protocol::signinInvalidPass(){
    return "204";
}

std::string Protocol::signinInvalidUsername(){
    return "203";
}

//log
std::string Protocol::getLog(std::string username){
    return "300|" + username;
}

std::string Protocol::sendLog(std::string logData){
    return "301|" + logData + "|";
}

std::string Protocol::failInFindingLog(){
    return "302";
}

std::string Protocol::userSendLog(std::string logData,std::string username){
    return "310|" + username + "|" + logData;
}

//Logout
std::string Protocol::logout(std::string username){
    return "400|" + username;
}

