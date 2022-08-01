#include "../headerFiles/libnetfilterQueueBasics.h"

/*
***********************************************************************************************
***********************************************************************************************
**   C'tor, the c'tor is seting up the program, in way that allowing us to read the packets  **
**   Input:The callback function, the number of the queue that the program reads from        **
**   Output:None                                                                             **
***********************************************************************************************
***********************************************************************************************
 */
LibnetfilterQueueBasics::LibnetfilterQueueBasics(nfq_callback cbFunction, u_int16_t queueNumber){
    this->openHandler = nfq_open();
    bind(); //Init the openHandler(bind it)
    this->ququeHandler = queueSetUp(cbFunction,queueNumber);
}

/*
***********************************************************************************************
***********************************************************************************************
**   D'tor, the d'tor is closing the handlers that we opened at the c'tor                    **
**   Input:None                                                                              **
**   Output:None                                                                             **
***********************************************************************************************
***********************************************************************************************
 */
LibnetfilterQueueBasics::~LibnetfilterQueueBasics(){
    std::cout << "unbinding from queue";
    nfq_destroy_queue(this->ququeHandler);
    std::cout << "\nclosing library handle\n";
    nfq_close(this->openHandler);

}


/*
***********************************************************************************************
***********************************************************************************************
**   The function bind a nfqueue handler to AF_INET protocol family                          **
**   and check if the handler is valid.                                                      **
**   Input:None                                                                              **
**   Output:None                                                                             **
***********************************************************************************************
***********************************************************************************************
 */
void LibnetfilterQueueBasics::bind(){
        if (!this->openHandler) {
                std::cout << stderr << "error during nfq_open()\n";
                exit(1); 
        }
        
        //Unbinding existing nf_queue handler
        std::cout << "unbinding existing nf_queue handler for AF_INET (if any)\n";
        if (nfq_unbind_pf(this->openHandler, AF_INET) < 0) {
                std::cout << stderr <<  "error during nfq_unbind_pf()\n";
                exit(1);
        }
        
        //Binding existing nf_queue handler
        std::cout << "binding nfnetlink_queue as nf_queue handler for AF_INET\n";
        if (nfq_bind_pf(this->openHandler, AF_INET) < 0) {
                std::cout << stderr <<  "error during nfq_bind_pf()\n";
                exit(1);
        }
}

/*
***********************************************************************************************
***********************************************************************************************
**   The function binding the socket for the given queue and set the queue to copy mode      **
**   Input:The callback function, the number of the queue that the program reads from        **
**   Output:the queue handle                                                                 **           **
***********************************************************************************************
***********************************************************************************************
 */
nfq_q_handle* LibnetfilterQueueBasics::queueSetUp(nfq_callback cb,u_int16_t queueNumber){
        
        //Binding this socket to the given queue
        std::cout << "binding this socket to queue" << "'" << queueNumber << "'" << "\n";
        nfq_q_handle* qh = nfq_create_queue(this->openHandler, queueNumber, cb, nullptr);
        if (!qh) {
                std::cout << stderr << " error during nfq_create_queue()\n";
                exit(1);
        }

        //set the queue for copy mode
        std::cout << "setting copy_packet mode\n";
        if (nfq_set_mode(qh, NFQNL_COPY_PACKET, 0xffff) < 0) {
                std::cout << stderr << " can't set packet_copy mode\n";
                exit(1);
        }
    return qh;
}


/*
***********************************************************************************************
***********************************************************************************************
**   This function handle the packets - sending the packet to the callback function          **
**   Input:None                                                                              **
**   Output:None                                                                             **
***********************************************************************************************
***********************************************************************************************
 */
void LibnetfilterQueueBasics::getPacket(){
    //getting the file descriptor  
    int fd = nfq_fd(this->openHandler);
    ssize_t rv = 0;

    //Get every packet end send it to the call back function
    while ((rv = recv(fd, buf, sizeof(buf), 0)) >= 0) {
            //std::cout << "pkt received\n";  
            if(nfq_handle_packet(this->openHandler, this->buf, rv) < 0){
            std::cout << "error\n";
            }
            cleanBuffer();
        }
}

void LibnetfilterQueueBasics::cleanBuffer(){
    for (int i = 0; i < std::strlen(buf); i++)
    {
        buf[i] = 0;
    }

}