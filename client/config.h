#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <string>
#include <fstream>

#define DEFAULT_PORT 6968
#define DEFAULT_IP "127.0.0.1"

class Config{
public:
    Config();
    void loadSettings();
    int getPort();
    std::string getIp();
private:
    int port;
    std::string ip;
};

#endif // CONFIG_H
