#include <iostream>
#include <string>
#include <ctime>

class userPacketsNumber {
public:
    userPacketsNumber(std::string ip, int countPackets, time_t firstPacketTime);//C'tor
    std::string getIp();
    int getCountPackets();
    time_t getFirstPacketTime();
    void setIp(std::string newIp);
    void setCountPackets(int newCountPackets);
    void setFirstPacketTime(time_t newFirstPacketTime);
private:
    std::string _ip;
    int _countPackets;
    time_t _firstPacketTime;
};