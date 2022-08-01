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
    std::string sqlQuery = "CREATE TABLE IF NOT EXISTS blackList (IP TEXT NOT NULL,ATTACK TEXT NOT NULL);";
    
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
This callback function change the value of the flag to true if the ip is in the blacklist table
input:argc - the amount of results, argv - values, azColName - the colume name
output:zero
*/
int DB::checkIfIpIsInBlacklistCallback(void *NotUsed, int argc, char **argv, char **azColName){
    //The callback function called only if there is result from the sql qurey 
    //This why if the ip is in the table the flag is automatically changes to true
    bool* isIpIsInBlacklist = (bool*)NotUsed;
    *isIpIsInBlacklist = MALICIOUS_IP;

    return 0;
}

/*
Function that checks if the ip is exist in the database
input:The ip to search on the database
output:False is the ip is not malicious and True if the ip is malicous
*/  
bool DB::checkIfIpIsInDatabase(std::string ip){

    bool isIpIsInBlacklist = NONE_MALICIOUS_IP; 
    int exit = 0;
    char* errorMsg;
    //Create the sql query
    std::string sqlQuery = "SELECT IP FROM blackList where IP = " + addQuotationMarks(ip) + ";";
    
    try{
        //Try to check if this ip is exist in the blacklist
        exit = sqlite3_exec(this->database, sqlQuery.c_str(), checkIfIpIsInBlacklistCallback, &isIpIsInBlacklist, &errorMsg);
        
        //Check if the query worked
        if(exit != SQLITE_OK){
            std::cout << "\nDatabase :\nERROR:Can't search for the ip!\n";
            sqlite3_free(errorMsg);
        }
        /* for debuging
        else{
            std::cout << "\nSearching for the ip!\n";
        }
        */

    }
    //Print error message if there is error with the query
    catch(const std::exception & e){
        std::cout << "ERROR: " << e.what();
    }
    return isIpIsInBlacklist;
}

/*
Function that inserts new ip to the database
input:The ip, the name of the attack that came from this ip
output:none
*/  
void DB::addNewIpToBlacklist(std::string ip,std::string attackName){
    //Create the sql query
    std::string sqlQuery = "INSERT INTO blacklist VALUES(" + addQuotationMarks(ip) + "," + addQuotationMarks (attackName) + ");";
    
    try{

        int exit = 0;
        char* errorMsg;
        //Try to add a new ip to the blacklist
        exit = sqlite3_exec(this->database,sqlQuery.c_str(),NULL,0,&errorMsg);
        
        //Check if the query worked
        if(exit != SQLITE_OK){
            std::cout << "\nDatabase :\nERROR:Can't add ip to the blacklist\n";
            sqlite3_free(errorMsg);
        }
        else{
            std::cout << "\nThe IP is added to the blacklist!\n";
        }

    }
    //Print error message if there is error with the query
    catch(const std::exception & e){
        std::cout << "ERROR: " << e.what();
    }
}

/*
Function that adds quotation marks to a string and return it
input:the string
output:the new string - the string that the user sended with quotation marks("")
*/
std::string DB::addQuotationMarks(std::string string){
    return "\"" + string + "\"";
}
