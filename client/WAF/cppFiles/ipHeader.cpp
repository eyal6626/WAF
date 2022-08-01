#include "../headerFiles/ipHeader.h"


IpHeader::IpHeader(struct iphdr *iph){
   struct sockaddr_in source, dest;
   source.sin_addr.s_addr = iph->saddr;
   dest.sin_addr.s_addr = iph->daddr;

   this->_srcIp = inet_ntoa(source.sin_addr); 
   this->_destIp = inet_ntoa(dest.sin_addr);
   this->_size = iph->ihl << 2;
}

IpHeader::~IpHeader(){

}

std::string IpHeader::getSrcIp(){
    return this->_srcIp;
}

std::string IpHeader::getDestIp(){
    return this->_destIp;
}

unsigned char IpHeader::getSize(){
    return this->_size;
}