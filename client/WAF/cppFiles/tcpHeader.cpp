#include "../headerFiles/tcpHeader.h"

TcpHeader::TcpHeader(struct tcphdr *tcp){
    this->_finFlag = tcp->fin;
    this->_ackFlag = tcp->ack;
    this->_srcPort = std::to_string(htons((unsigned short int) tcp->source));
    this->_destPort = std::to_string(htons((unsigned short int) tcp->dest));
    this->_size  = (tcp->doff << 2);
}

TcpHeader::~TcpHeader(){

}

std::string TcpHeader::getSrcPort(){
    return this->_srcPort;
}

std::string TcpHeader::getDestPort(){
    return this->_destPort;
}

unsigned short TcpHeader::getSize(){
    return this->_size;
}

bool TcpHeader::endOfConverstion(){
    return this->_ackFlag && this->_finFlag;
}