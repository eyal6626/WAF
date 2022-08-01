#include <iostream>
#include <string>
#include <sqlite3.h>

#define USER_NOT_EXIST false
#define USER_EXIST true
#define CANT_FIND_LOG "!"

class DB {
public:
    DB(std::string path);//C'tor   
    ~DB();//D'tor
    void initDB();//Create the tables in the db file
    bool checkIfUserExist(std::string username,std::string password);//Check if the ip is exist in the database
    bool checkIfUsernameExist(std::string username);
    void addNewUser(std::string username,std::string password,std::string email);
    void closeDB(void);
    std::string getUserLog(std::string username);
private:
    sqlite3* database;

    //Callback functions
    static int checkIfUserExistlistCallback(void *NotUsed, int argc, char **argv, char **azColName);
    static int searchForLogPathlistCallback(void *NotUsed, int argc, char **argv, char **azColName);
    
    //Helpers
    std::string addQuotationMarks(std::string string);//Add quotation marks to a string and return it

};