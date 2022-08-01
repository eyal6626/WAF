#include <iostream>
#include <string>
#include <stdint.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <linux/netfilter.h>
#include <libnetfilter_queue/libnetfilter_queue.h>
#include <linux/ip.h>

class IpHeader{

public:
    IpHeader(struct iphdr *iph);
    ~IpHeader();
    std::string getSrcIp();
    std::string getDestIp();
    unsigned char getSize();

private:
    std::string _srcIp;
    std::string _destIp;
    unsigned char _size;
};