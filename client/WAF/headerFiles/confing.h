#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

class Conf{

public:
    Conf(std::string fileName);
    std::string getUsername();
    std::string getPassword();
    std::string getDosPacketNumber();
    std::string getDdosPacketNumber();
    

private:
    std::string _username;
    std::string _password;
    std::string _dosPacketNumber;
    std::string _ddosPacketNumber;
};