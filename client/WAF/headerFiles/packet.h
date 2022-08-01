#include "tcpHeader.h"
#include "ipHeader.h"
#include <cstring>
#include <iostream>
#include <vector>

#define NOT_TCP false
#define TCP true
class Packet{

public:
    Packet(struct nfq_data* nfad);
    ~Packet();
    std::string getApplicationLayerData();
    IpHeader* ipHeader;
    TcpHeader* tcpHeader;
    bool isTcp ;
private:
    struct tcphdr* tcph;
    
    
    
    
};