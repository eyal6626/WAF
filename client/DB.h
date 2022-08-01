#include <iostream>
#include <string>
#include <sqlite3.h>

#define NONE_MALICIOUS_IP false
#define MALICIOUS_IP true

class DB {
public:
    DB(std::string path);//C'tor   
    ~DB();//D'tor
    void initDB();//Create the tables in the db file
    bool checkIfIpIsInDatabase(std::string ip);//Check if the ip is exist in the database
    void addNewIpToBlacklist(std::string ip,std::string attackName);//Insert new ip to the database
    void closeDB(void);
private:
    sqlite3* database;

    //Callback functions
    static int checkIfIpIsInBlacklistCallback(void *NotUsed, int argc, char **argv, char **azColName);
    //This callback function change the value of the flag to true if the ip is in the blacklist table
    
    //Helpers
    std::string addQuotationMarks(std::string string);//Add quotation marks to a string and return it

};
