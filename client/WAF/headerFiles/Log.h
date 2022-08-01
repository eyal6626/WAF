#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

#define SQL_INJECTION_MSG std::string("Sql injection was detected")
#define DOS_MSG std::string("Dos attack was detected")
#define DDOS_MSG std::string("DDos attack was detected")
#define NEW_IP_ADD_TO_THE_BLACKLIST std::string("New ip added to the blacklist")

class  Log
{
public:
    Log(std::string fileName);
    ~Log();
    void addSqlInjectionToLog(std::string ip);
    void addDosToLog(std::string ip);
    void addDdosToLog();

private:
    std::string _fileName;
    void writeToFile(std::string msg);
    std::string getTimeAndDate();
    void addNewIpToBlacklistToLog(std::string ip);


};

