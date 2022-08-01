#include "config.h"

Config::Config(){
    this->port = DEFAULT_PORT;
    this->ip = DEFAULT_IP;
}

/*
 * The function load the settings of the program from the config
 * input:none
 * output:none
*/
void Config::loadSettings(){
    std::ifstream configFile;
    std::string line;
    configFile.open("config.txt");

    if (configFile.is_open()) {
        std::getline(configFile, line);
        this->port = std::stoi(line.c_str());
        std::getline(configFile, line);
        this->ip = line;
    }
    configFile.close();
}

/*
* Get function that get the port
* input:none
* output:the port number of the server
*/
int Config::getPort(){
    return this->port;
}

/*
* Get function that get the ip
* input:none
* output:the ip of the server
*/
std::string Config::getIp(){
    return this->ip;
}
