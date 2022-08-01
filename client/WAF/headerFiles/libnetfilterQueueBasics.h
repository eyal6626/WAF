#include <cstring>
#include <iostream>
#include <string>
#include <libnetfilter_queue/libnetfilter_queue.h>
#include <arpa/inet.h>
#include <linux/netfilter.h>

#define BUFFER_LEN 4096

class LibnetfilterQueueBasics{

public:
    LibnetfilterQueueBasics(nfq_callback cbFunction,u_int16_t queueNumber);
    ~LibnetfilterQueueBasics();
    void getPacket();
    

private:
    void cleanBuffer();
    nfq_handle* openHandler;
    nfq_q_handle* ququeHandler;
    char buf[BUFFER_LEN] = {0};
    void bind();
    nfq_q_handle* queueSetUp(nfq_callback cb, u_int16_t queueNumber);

};
