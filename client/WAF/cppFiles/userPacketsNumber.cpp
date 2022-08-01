#include "../headerFiles/userPacketsNumber.h"


userPacketsNumber::userPacketsNumber(std::string ip, int countPackets, time_t firstPacketTime)
{
    this->_ip = ip;
    this->_countPackets = countPackets;
    this->_firstPacketTime = firstPacketTime;
}
std::string userPacketsNumber::getIp()
{
    return this->_ip;
}
int userPacketsNumber::getCountPackets()
{
    return this->_countPackets;
}

time_t userPacketsNumber::getFirstPacketTime()
{
    return this->_firstPacketTime;
}
void userPacketsNumber::setIp(std::string newIp)
{
    this->_ip = newIp;
}
void userPacketsNumber::setCountPackets(int newCountPackets)
{
    this->_countPackets = newCountPackets;
}
void userPacketsNumber::setFirstPacketTime(time_t newFirstPacketTime)
{
    this->_firstPacketTime = newFirstPacketTime;
}