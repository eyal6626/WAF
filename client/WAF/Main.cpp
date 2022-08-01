#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <unistd.h>
#include <iterator>
#include <memory>
#include "headerFiles/DB.h"
#include "headerFiles/userPacketsNumber.h"
#include "headerFiles/libnetfilterQueueBasics.h"
#include "headerFiles/packet.h"
#include "headerFiles/Log.h"
#include "headerFiles/confing.h"
#include "headerFiles/client.h"
#include <thread>

#define COMMAND_LINE_ARGUMENTS_NUMBER 3
#define QUEUE_NUMBER 1
#define INFECTED true
#define NOT_INFECTED false
#define MINUTE 60
#define DOS_ATTACK "Dos"
#define CONF_PATH std::string("tempLog.txt")

//Open the database
DB db("databaseFile");
Conf configFile("conf.txt");
Log tempLog(CONF_PATH);

int maximum_packets_in_minute = 0;
int maximum_packets_in_minute_for_person = 0;
std::time_t times = 0;
int packets_in_minute = 0;
bool timer_on = false;
std::time_t timer = 0;
std::vector<std::string > rules;
std::string serverPort;
std::vector<std::shared_ptr<userPacketsNumber> > users_packets_number;	// vector of users packets number
std::string lastIp = "";

void sendAttackToServerLog(){
    Client client;
	if(client.isSocketConnected()){
	    client.setUsername(configFile.getUsername());
		client.sendLogin(configFile.getUsername(),configFile.getPassword());
		client.sendLogDataToServer("tempLog.txt",client.getUsername());
	}
}

/*
This function check if the data that the user send is infected
input: the user data
output:if the data is infected in sql injection
*/
bool checkForSqlInjection(std::string msg)
{
	std::vector<std::string>::iterator it;
	//Check if the rules are in the data 
	for (it = rules.begin(); it != rules.end(); it++)
	{
		
		//If the data in infected return infected
		if (msg.find(*it) != std::string::npos)
		{
			return INFECTED;
		}
	}
	return NOT_INFECTED;
}

static int cb(struct nfq_q_handle *qh, struct nfgenmsg *nfmsg, struct nfq_data *nfad, void *data)
{

	struct nfqnl_msg_packet_hdr *ph = nfq_get_msg_packet_hdr(nfad);
	
	//Create a new packet class 
	Packet packet(nfad);
	//Check if the packet is tcp packet
	if (packet.isTcp == TCP)
	{
		//Check the port of the packet
		if (packet.tcpHeader->getDestPort() == serverPort)
		{
			//Check if the ip is in the blacklist
			if (db.checkIfIpIsInDatabase(packet.ipHeader->getSrcIp()) == MALICIOUS_IP)
			{
			 	//if the packet is in the blacklist drop the packet
				return nfq_set_verdict(qh, ntohl(ph->packet_id), NF_DROP, 0, nullptr);
			}

            std::cout << "\nIp:" << packet.ipHeader->getSrcIp() << "  Port:" << packet.tcpHeader->getDestPort();
			
            std::string data = packet.getApplicationLayerData();
			std::cout << "\nPacket data: \n"<< data << "\n";
			//Check if the http message is post or not
			if (data.find("POST") != std::string::npos)
			{
			 	//Get http data
				std::string httpData = data.substr(data.find("\r\n\r\n"), (data.length() - 1));
				
				//Check if there is sql injection in the message
				if (checkForSqlInjection(httpData) == INFECTED)
				{
				    //Block the attacker ip
					tempLog.addSqlInjectionToLog(packet.ipHeader->getSrcIp());
					std::thread(sendAttackToServerLog);
					db.addNewIpToBlacklist(packet.ipHeader->getSrcIp(), "SQL injection");
					return nfq_set_verdict(qh, ntohl(ph->packet_id), NF_DROP, 0, nullptr);
				}
				else{
					if(lastIp != packet.ipHeader->getSrcIp()){
						lastIp = packet.ipHeader->getSrcIp();
					}
				}
			}
			//Check if there is sql injection in the other segment of the packet
			else{
				if(lastIp == packet.ipHeader->getSrcIp()){
					//Check if the other segment contains sql injection
					if (checkForSqlInjection(packet.getApplicationLayerData()) == INFECTED)
					{
				    	//Block the attacker ip
						tempLog.addSqlInjectionToLog(packet.ipHeader->getSrcIp());
					    std::thread sendToLog(sendAttackToServerLog);
                        sendToLog.detach();
						db.addNewIpToBlacklist(packet.ipHeader->getSrcIp(), "SQL injection");
						return nfq_set_verdict(qh, ntohl(ph->packet_id), NF_DROP, 0, nullptr);
					}
					else{
						lastIp = "";
					}
				}
			}


			// check timer
			if (std::time(0) > timer + (5 *MINUTE))
			{
				timer_on = false;
				timer = 0;
			}

			//if timer is on because of ddos sleep for 5 secs for every packet.
			if (timer_on)
			{
				tempLog.addDdosToLog();
			    std::thread sendToLog(sendAttackToServerLog);
                sendToLog.detach();
				usleep(5000000);
			}

			//check dos attack 
			//check if the packet should go to our server
			bool found = false;
			for (auto itr = users_packets_number.begin(); itr != users_packets_number.end(); itr++)
			{
				
			 	// if user in list so update the vector
				if (itr[0]->getIp() == packet.ipHeader->getSrcIp())
				{
					itr[0]->setCountPackets(itr[0]->getCountPackets() + 1);
					found = true;
				}
			}
			// check if its dos attack to our server and if there is a user that not attacking (left minute)
			for (auto itr = users_packets_number.begin(); itr != users_packets_number.end(); itr++)
			{
				if(itr != users_packets_number.end()){
			 		// if its a dos attack
					if (itr[0]->getCountPackets() >= maximum_packets_in_minute_for_person)
					{
						tempLog.addDosToLog(packet.ipHeader->getSrcIp());
					    std::thread sendToLog(sendAttackToServerLog);
                        sendToLog.detach();
						db.addNewIpToBlacklist(itr[0]->getIp(), DOS_ATTACK);
					}
					// check if user time is over than minute
					if (std::time(0) - (itr[0]->getFirstPacketTime() > MINUTE))
					{
					
						users_packets_number.erase(itr--);
					}
				}
			}
			// if user not in vector so add him
			if (!found)
			{
				std::shared_ptr<userPacketsNumber> newUser(new userPacketsNumber(packet.ipHeader->getSrcIp(), 1, std::time(0)));

				//Fixed: create new class object with new userPacketNumber
				users_packets_number.push_back(newUser);
			}

			//check for ddos attack
			//if the time is 0 so start the time and count first packet
			if (times == 0)
			{
				times = std::time(0);
				packets_in_minute = 1;
			}
			//if minute is passed so init the time ant the packet counter
			else if (std::time(0) - times >= MINUTE)
			{
				times = 0;
				packets_in_minute = 0;
			}
			//if its ddos so delay the packet traffic
			else if (packets_in_minute > maximum_packets_in_minute)
			{
				timer_on = true;
				timer = std::time(0);
			}
			//add to packet counter another packet
			else
			{
				packets_in_minute++;
			}
		}
	}
	return nfq_set_verdict(qh, ntohl(ph->packet_id), NF_ACCEPT, 0, nullptr);
}

int main(int argc, char *argv[])
{
	try{
	db.initDB();
	maximum_packets_in_minute = atoi(configFile.getDdosPacketNumber().c_str());
	maximum_packets_in_minute_for_person = atoi(configFile.getDosPacketNumber().c_str());
	/*
	if (argc == COMMAND_LINE_ARGUMENTS_NUMBER)
	{
		try
		{
			maximum_packets_in_minute = std::atoi(argv[1]);
			maximum_packets_in_minute_for_person = std::atoi(argv[2]);
			
		}
		catch (...)
		{
			std::cout << "you need to put numbers in both arguments";
			return 0;
		}
	}
	else
	{
		std::cout << "you need to put 2 arguments";
		return 0;
	}
	*/

	//Set the rules 
	std::ifstream file("sqlInjectionRules.txt");
	std::string str;
	while (std::getline(file, str))
	{
		rules.push_back(str);
	}

		
	//Get the server port
	std::cout << "Enter server port: ";
	std::cin >> serverPort;
	std::cout << "\nEstablishing connection";
	std::cout << "\n==========================\n";
	//Build the queue to catch packets
	LibnetfilterQueueBasics libnetfilterQueue(cb, QUEUE_NUMBER);
	std::cout << "=======================================================\n\n";
	//Start scanning for packets 
	libnetfilterQueue.getPacket();
	db.closeDB();
	}
	catch(std::exception e){
		std::cout << "\n\nerror: " << e.what();
	}
	return 0;
	
}
