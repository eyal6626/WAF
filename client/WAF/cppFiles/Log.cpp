#include "../headerFiles/Log.h"

Log::Log(std::string fileName){
    this->_fileName = fileName;
}

Log::~Log(){
    
}

void Log::writeToFile(std::string msg){
    std::ofstream file;
    file.open(this->_fileName, std::ios_base::app);
    file << msg;
    file.close();
}

std::string Log::getTimeAndDate(){
  time_t rawtime;
  struct tm * timeinfo;
  char buffer[80];

  time (&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(buffer,80,"%d-%m-%Y %I:%M:%S",timeinfo);
  std::string str(buffer);
  return str;
}

void Log::addSqlInjectionToLog(std::string ip){
    std::string msg = SQL_INJECTION_MSG + " - " + getTimeAndDate() + "\n"; 
    writeToFile(msg);
    addNewIpToBlacklistToLog(ip);
}

void Log::addDosToLog(std::string ip){
    std::string msg = DOS_MSG + " - " + getTimeAndDate() + "\n"; 
    writeToFile(msg);
    addNewIpToBlacklistToLog(ip);
}

void Log::addDdosToLog(){
    std::string msg = DDOS_MSG + " - " + getTimeAndDate() + "\n";  
    writeToFile(msg);
}

void Log::addNewIpToBlacklistToLog(std::string ip){
    writeToFile("Attacker ip: " +ip + " - " + getTimeAndDate() + std::string("\n")); 
}