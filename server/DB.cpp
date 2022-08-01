#include "DB.h"

/*
C'tor that open or create and open the db file in the given path 
input:The database path with the database name
output:none
*/
DB::DB(std::string path){
    //Create db file if not exist and open it.
    //Or open the file if exist.
    int exit = 0;
    exit = sqlite3_open(path.c_str(),&this->database);
}

/*
Close the database
input:None
output:none
*/
void DB::closeDB(void){
    sqlite3_close(this->database);
}


/*
D'tor that close the database
input:None
output:none
*/
DB::~DB(){
    //Close the db
    closeDB();
}

/*
Function that create the tables in the db file
input:none
output:none
*/
void DB::initDB(){

    //Create the sql query
    std::string sqlQuery = "CREATE TABLE IF NOT EXISTS USERS (USERNAME TEXT NOT NULL,PASSWORD TEXT NOT NULL, MAIL TEXT NOT NULL,LOGPATH TEXT NOT NULL);";
    
    try{

        int exit = 0;
        char* errorMsg;
        //Try to create new table in the database file
        exit = sqlite3_exec(this->database,sqlQuery.c_str(),NULL,0,&errorMsg);
        
        //Check if the query worked
        if(exit != SQLITE_OK){
            std::cout << "\nDatabase :\n ERROR:Table was not created!\n";
            sqlite3_free(errorMsg);
        }
        else{
            std::cout << "\nDatabase: Ready!\n";
        }

    }
    //Print error message if there is error with the query
    catch(const std::exception & e){
        std::cout << "ERROR: " << e.what();
    }
}

/*
This callback function change the value of the flag to true if the ip is in the users table
input:argc - the amount of results, argv - values, azColName - the colume name
output:zero
*/
int DB::checkIfUserExistlistCallback(void *NotUsed, int argc, char **argv, char **azColName){
    //The callback function called only if there is result from the sql qurey 
    //This why if the ip is in the table the flag is automatically changes to true
    bool* isUserExist = (bool*)NotUsed;
    *isUserExist = USER_EXIST;

    return 0;
}

int DB::searchForLogPathlistCallback(void *NotUsed, int argc, char **argv, char **azColName){
    //The callback function called only if there is result from the sql qurey 
    //This why if the ip is in the table the flag is automatically changes to true
    std::string* logPath = (std::string*)NotUsed;
    *logPath = std::string(azColName[1]);

    return 0;
}

/*
Function that checks if the user is exist in the database
input:The user to search on the database
output:if the user exists
*/  
bool DB::checkIfUserExist(std::string username,std::string password){

    bool isUserExist = USER_NOT_EXIST; 
    int exit = 0;
    char* errorMsg;
    //Create the sql query
    std::string sqlQuery = "SELECT USERNAME FROM USERS where USERNAME = " + addQuotationMarks(username) + " AND PASSWORD = " + addQuotationMarks(password) + ";";

    try{
        //Try to check if this ip is exist in the blacklist
        exit = sqlite3_exec(this->database, sqlQuery.c_str(), checkIfUserExistlistCallback, &isUserExist, &errorMsg);
        
        //Check if the query worked
        if(exit != SQLITE_OK){
            std::cout << "\nDatabase :\nERROR:Can't search for the username!\n";
            sqlite3_free(errorMsg);
        }


    }
    //Print error message if there is error with the query
    catch(const std::exception & e){
        std::cout << "ERROR: " << e.what();
    }
    return isUserExist;
}

/*
Function that adds quotation marks to a string and return it
input:the string
output:the new string - the string that the user sended with quotation marks("")
*/
std::string DB::addQuotationMarks(std::string string){
    return "\"" + string + "\"";
}

void DB::addNewUser(std::string username,std::string password,std::string email){
    
    std::string logPath = "logs/"+username + "Log.txt"; 
    int exit = 0;
    char* errorMsg;
    //Create the sql query
    std::string sqlQuery = "INSERT INTO USERS VALUES(" + addQuotationMarks(username) + "," + addQuotationMarks(password) + "," + addQuotationMarks(email) + "," + addQuotationMarks(logPath) + ");";

    try{
        //Try to check if this ip is exist in the blacklist
        exit = sqlite3_exec(this->database, sqlQuery.c_str(), NULL,0,&errorMsg);
        
        //Check if the query worked
        if(exit != SQLITE_OK){
            std::cout << "\nDatabase :\nERROR:Can't search for the username!\n";
            sqlite3_free(errorMsg);
        }

    }
    //Print error message if there is error with the query
    catch(const std::exception & e){
        std::cout << "ERROR: " << e.what();
    }
}

std::string DB::getUserLog(std::string username){
    std::string logPath = CANT_FIND_LOG; 
    int exit = 0;
    char* errorMsg;
    //Create the sql query
    std::string sqlQuery = "SELECT LOGPATH FROM USERS where USERNAME = " + addQuotationMarks(username) + ";";

    try{
        //Try to check if this ip is exist in the blacklist
        exit = sqlite3_exec(this->database, sqlQuery.c_str(), searchForLogPathlistCallback, &logPath, &errorMsg);
        
        //Check if the query worked
        if(exit != SQLITE_OK){
            std::cout << "\nDatabase :\nERROR:Can't search for the username!\n";
            sqlite3_free(errorMsg);
        }


    }
    //Print error message if there is error with the query
    catch(const std::exception & e){
        std::cout << "ERROR: " << e.what();
    }
    return logPath;
}

bool DB::checkIfUsernameExist(std::string username){

    bool isUserExist = USER_NOT_EXIST; 
    int exit = 0;
    char* errorMsg;
    //Create the sql query
    std::string sqlQuery = "SELECT USERNAME FROM USERS where USERNAME = " + addQuotationMarks(username) + ";";

    try{
        //Try to check if this ip is exist in the blacklist
        exit = sqlite3_exec(this->database, sqlQuery.c_str(), checkIfUserExistlistCallback, &isUserExist, &errorMsg);
        
        //Check if the query worked
        if(exit != SQLITE_OK){
            std::cout << "\nDatabase :\nERROR:Can't search for the username!\n";
            sqlite3_free(errorMsg);
        }


    }
    //Print error message if there is error with the query
    catch(const std::exception & e){
        std::cout << "ERROR: " << e.what();
    }
    return isUserExist;
}