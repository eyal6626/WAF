#include <iostream>
#include <string>
#include <stdint.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <linux/netfilter.h>
#include <libnetfilter_queue/libnetfilter_queue.h>
#include <linux/tcp.h>

class TcpHeader{

public:
    TcpHeader(struct tcphdr *tcp);
    ~TcpHeader();
    std::string getSrcPort();
    std::string getDestPort();
    unsigned short getSize();
    bool endOfConverstion();

private:
    std::string _srcPort;
    std::string _destPort;
    unsigned short _size;
    u_int16_t _finFlag;
    u_int16_t _ackFlag;
};