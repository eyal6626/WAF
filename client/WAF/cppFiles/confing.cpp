#include "../headerFiles/confing.h"

Conf::Conf(std::string fileName){
    std::ifstream file(fileName);
    std::string line = "";
    if(file.is_open()){
        //Get username
        getline(file,line);
        this->_username = line;
        //Get password
        getline(file,line);
        this->_password = line;
        //Get dos packet number
        getline(file,line);
        this->_dosPacketNumber = line;
        //Get ddos packet number
        getline(file,line);
        this->_ddosPacketNumber = line;
        //Close file
        file.close();
    }
    else{
        std::cout << "Can't open conf file!";
        std::cin;
        exit(1);
    }
}

std::string Conf::getUsername(){
    return this->_username;
}

std::string Conf::getPassword(){
    return this->_password;
}

std::string Conf::getDosPacketNumber(){
    return this->_dosPacketNumber;
}

std::string Conf::getDdosPacketNumber(){
    return this->_ddosPacketNumber;
}

