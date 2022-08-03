# WAF

This project is a WAF (Application Firewall) for Linux that protects HTTP servers from the following threats:

* Dos (Denial-of-service) attack

* DDOS (Distributed Denial-of-Service) attack

* SQL injection

The project has three parts. The actual WAF porgram, a user interface and a server.

1. The WAF program is the part that protects the server from attacks and also saves a log of all of the attacks that occurred and sends them to the server. The program has a config file that saves settings like which account(username and password) to save the log and the maximum number of packets that are sent when there is a dos or ddos attack on the server. The attacker's IP is added to a blacklist, and if he tries to send any packet from his IP, the packet will be dropped immediately.

2. The user interface is the part of the program that makes it possible for the user to watch his log, change settings for the program, and edit the blacklist. It's also connected to the server to login, create a new account, and get the log.

3. The server saves all of the logs, authenticates users when they want to login and create accounts. The server is a multithreaded server.

# What I Learned

* How to use the libnetfilter_queue library
* How to manipulate network traffic(drop packets,accept packets, etc.)
* How to extract data from packets and filter them
* How to defend against DOS, DDOS, and SQL injection attacks
* How to design a GUI using QT
* I learned more about networking,Linux OS and the world of cybersecurity.


