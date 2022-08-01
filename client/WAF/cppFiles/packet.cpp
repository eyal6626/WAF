#include "../headerFiles/packet.h"

Packet::Packet(struct nfq_data* nfad){
    
    unsigned char* nf_packet = NULL;
    int len = nfq_get_payload(nfad,&nf_packet);
    
    //Check if the there is any problem with extracting the packet payload
    if((len < 0) || nf_packet == NULL){
        isTcp = NOT_TCP;
        this->ipHeader == nullptr;
        this->tcpHeader == nullptr;
    }
    //If there is no problem with the packet extract the data from the packet
    else{
        //Extract the ip header:
        struct iphdr *iph = ((struct iphdr *) nf_packet);
        this->ipHeader = new IpHeader(iph);
    
        if(iph->protocol == IPPROTO_TCP){
        //Extract the tcp header:
        this->tcph = (struct tcphdr *) (nf_packet + this->ipHeader->getSize());
        this->tcpHeader = new TcpHeader(this->tcph);
        isTcp = TCP;
        }
        
        else{
            isTcp = NOT_TCP;
            this->tcpHeader == nullptr;
        }
    }

    
    
}

Packet::~Packet(){
    delete this->ipHeader;
    if(this->isTcp != NOT_TCP){
        delete this->tcpHeader;
    }
}

std::string Packet::getApplicationLayerData(){
    unsigned char* user_data = (unsigned char *)((unsigned char *)this->tcph + (this->tcph->doff * 4));
    std::string data((char *)user_data);

    return data;
}