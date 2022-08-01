#include "Server.h"
#include <assert.h>


Server::Server(/* args */)
{
    this->database = new DB("usersInfo");
    this->database->initDB();
    checkForError(this->serverSocket = socket(AF_INET, SOCK_STREAM, 0), "Failed to create the socket!");
    //Init address struct
    this->serverAddr.sin_family = AF_INET;
    this->serverAddr.sin_addr.s_addr = INADDR_ANY;
    this->serverAddr.sin_port = htons(SERVERPORT);

    //Bind the socket
    checkForError(bind(this->serverSocket,(SA*)&this->serverAddr, sizeof(this->serverAddr)), "Bind failed!");
    //The socket is starting to listen for connections
    checkForError(listen(this->serverSocket, SERVER_BACKLOG), "Listen failed!");

};

Server::~Server()
{
   close(this->serverSocket);
}

void Server::serve(){
    std::cout << "Waiting for clients...\n";
    while (true)
    {
        //Accept new connection
        this->addrSize = sizeof(SA_IN);
        checkForError(this->clientSocket = accept(this->serverSocket, (SA*)&this->clientAddr, (socklen_t*)&this->addrSize), "Accept failed!");
        std::cout << "\nConnected!\n";

        //Get the client msg
        std::thread clientThread(&Server::handleClientMsg, this,(this->clientSocket));
	    clientThread.detach();

    }
}

void Server::handleClientMsg(int client_socket){
    char buffer[BUFSIZE];
    size_t bytesRead;
    int msgSize = 0;
    std::string ans = "!";
    size_t bytesSent = 0;
    size_t bytesLeft = 0;
   
    while(ans.compare(CLOSE_SOCKET) != 0){
        msgSize = 0;
        //Get the client message
        while (bytesRead == read(client_socket, buffer+msgSize, sizeof(buffer) - msgSize - 1) > 0)
        {
            msgSize += bytesRead;
            if(msgSize > BUFSIZE -1 || buffer[msgSize-1] == '\n')break;
        }
        checkForError(bytesRead, "Recv error!");
        buffer[msgSize-1] = 0;
        
        std::cout << "Msg: " << buffer << std::endl;
        std::string req = buffer;
    
        ans = requestHandler(checkRequestType(req),req);

        bytesLeft = strlen(ans.c_str());
        if(ans != "0" && ans != CLOSE_SOCKET){
            while(bytesLeft > 0){
                bytesSent = send(client_socket, ans.c_str(), bytesLeft, 0);
                assert(bytesSent <= bytesLeft);
                bytesLeft -= bytesSent;
                ans = ans.substr(bytesSent, ans.length() - 1);
            }
    }
        
    }
    fflush(stdout);
    close(client_socket);
    std::cout << "\nUser disconnected!\n" << std::endl;
}

void Server::checkForError(int answerCode, std::string msg){
    if(answerCode == -1){
        std::cout << msg << "\n";
    }
}

std::string Server::checkRequestType(std::string req){
    return req.substr(0,3);
}

std::string Server::requestHandler(std::string reqCode, std::string req){
    if(reqCode == "100"){
        return checkLogin(req);
    }
    else if(reqCode == "200"){
        return checkSignup(req);
    }
    else if(reqCode == "300"){
        return getLogReq(req);
    }
    else if(reqCode == "310"){
        addDataToLog(req);
        return "0";
    }
    else if(reqCode == "400"){
        return doLogout(req);
    }
    return "0";
}

std::string Server::checkLogin(std::string msg){

    std::string username = msg.substr(4,msg.length() - 1);
    username = username.substr(0,username.find("|"));
    std::string password = msg.substr(5+username.length(),msg.length()-1);
    if(this->database->checkIfUserExist(username,password)){
        this->users.push_back(username);
        return "101";
    }
    else{
        return "102";
    }
}

std::string Server::checkSignup(std::string msg){
    std::string username = msg.substr(4,msg.length() - 1);
    username = username.substr(0,username.find("|"));
    std::string password = msg.substr(5+username.length(),msg.length()-1);
    password = password.substr(0,password.find("|"));
    std::cout << "\npass:" << password << std::endl;
    std::string email = msg.substr(5+username.length()+password.length(),msg.length() - 1);
    if(this->database->checkIfUsernameExist(username)){
        return "202";
    }
    else if(username.length() < 8){
        return "203";
    }
    else if(password.length() < 8){
        return "204";
    }
    this->database->addNewUser(username,password,email);
    std::ofstream file;
    file.open("logs/"+username + "Log.txt");
    file << username + " Log:";
    file.close();
    return "201";
}

std::string Server::getLogReq(std::string msg){
    std::string username = msg.substr(4,msg.length() - 1);
    std::string path = this->database->getUserLog(username);
    if(path.compare(CANT_FIND_LOG) != 0){
        return this->protocol.sendLog(readDatafromLog(path));
    }
    else{
        return this->protocol.failInFindingLog();
    }
}

std::string Server::readDatafromLog(std::string logPath){
    std::ifstream file(logPath);
    std::string logData = "";
    std::string line = "";
    if(file.is_open()){
        while(getline(file,line)){
            logData = logData + "*" + line;
        }
        file.close();
    }
    return logData;
}

std::string Server::doLogout(std::string msg){
    std::string username = msg.substr(4,msg.length() - 1);
    for(auto it = this->users.begin();it != this->users.end();++it){
        if((*it).compare(username) == 0){
            this->users.erase(it--);
        }
    }
    return CLOSE_SOCKET;
}

void Server::addDataToLog(std::string msg){
    std::string username = msg.substr(4,msg.length() - 1);
    username = username.substr(0,username.find("|"));
    std::string data = msg.substr(5+username.length(), msg.length() - 1);
    std::string path = this->database->getUserLog(username);
    std::cout << data;
    for(int i = 0; i < data.length();i++){
        if(data[i] == '*'){
            data[i] = '\n';
        }
    }


    std::ofstream file;
    file.open(("logs/"+username + "Log.txt"), std::ios_base::app);
    file << data;
    file.close();
}