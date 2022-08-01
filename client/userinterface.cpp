#include "userinterface.h"
#include "ui_userinterface.h"


userInterface::userInterface(QWidget *parent,Client *client) :
    QWidget(parent),
    ui(new Ui::userInterface)
{
    this->_client = client;
    ui->setupUi(this);
    this->ui->textEdit->setReadOnly(true);
}

userInterface::~userInterface()
{
    delete ui;
}

std::string userInterface::extractDataFromLogMsg(std::string msg){
    msg = msg.substr(5,msg.length()-1);
    for(int i = 0;i < msg.length();i++){
        if(msg[i] == '*'){
            msg[i] = '\n';
        }
    }
    return msg;
}

bool is_digits(const std::string &str)
{
    return str.find_first_not_of("0123456789") == std::string::npos;
}

bool writeToFile( char const* filename, unsigned lineNo, char const * toWrite)
{
     std::fstream file( filename ) ;
     if ( !file )
          return false ;

     unsigned currentLine = 0 ;
     while ( currentLine < lineNo )
     {
          // We don't actually care about the lines we're reading,
          // so just discard them.
          file.ignore( std::numeric_limits<std::streamsize>::max(), '\n') ;
          ++currentLine ;
     }

     // Position the put pointer -- switching from reading to writing.
     file.seekp(file.tellg()) ;
     file << toWrite;
     return  true;
}

void userInterface::on_pushButton_clicked()
{
    this->_client->sendGetLog(this->_client->getUsername());
    std::string msg =  this->_client->getServerMsg();
    std::string logData = extractDataFromLogMsg(msg);
    this->ui->textEdit->setText(QString::fromLocal8Bit(logData.c_str()));
}


void userInterface::on_pushButton_2_clicked()
{
    this->ui->textEdit->setText("");
}


void userInterface::on_browseBlacklist_clicked()
{
    this->_DBfileName = QFileDialog::getOpenFileName(this,"open a file", QDir::homePath());
    this->db.setDatabaseName(this->_DBfileName);
    if(!this->db.open()){
        QMessageBox::critical(this,"Database","Can't open this file!");
    }
    else{
       QSqlQueryModel* model = new QSqlQueryModel();
       QSqlQuery* qry = new QSqlQuery(this->db);
       qry->prepare("SELECT * FROM blacklist");
       qry->exec();
       model->setQuery(std::move(*qry));
       this->ui->tableViewBlacklist->setModel(model);
       this->db.close();
    }

    //add ip db
}




void userInterface::on_deleteIpButton_2_clicked()
{

    this->db.setDatabaseName(this->_DBfileName);
    if(!this->db.open()){
        QMessageBox::critical(this,"Database","Can't open this db file!");
    }
    else{
       QSqlQueryModel* model = new QSqlQueryModel();
       QSqlQuery* qry = new QSqlQuery(this->db);
       qry->prepare("DELETE FROM blacklist WHERE IP = '" + this->ui->deleteIpInput->text() + "';");
       qry->exec();
       this->db.close();
    }
}


void userInterface::on_reloadBlacklist_clicked()
{
    this->db.setDatabaseName(this->_DBfileName);
    if(!this->db.open()){
        QMessageBox::critical(this,"Database","Can't open this file!");
    }
    else{
       QSqlQueryModel* model = new QSqlQueryModel();
       QSqlQuery* qry = new QSqlQuery(this->db);
       qry->prepare("SELECT * FROM blacklist");
       qry->exec();
       model->setQuery(std::move(*qry));
       this->ui->tableViewBlacklist->setModel(model);
       this->db.close();
    }
}


void userInterface::on_addIpButton_clicked()
{
    //Check the attack
    QString attackName;
    if(this->ui->radioButtonDos->isChecked()){
        attackName = "Dos";
    }
    if(this->ui->radioButtonDdos->isChecked()){
        attackName = "DDos";
    }
    if(this->ui->radioButtonSqlInjection->isChecked()){
        attackName = "Sql injection";
    }

    //Add to the database
    this->db.setDatabaseName(this->_DBfileName);
    if(!this->db.open()){
        QMessageBox::critical(this,"Database","Can't open this file!");
    }
    else{
       QSqlQueryModel* model = new QSqlQueryModel();
       QSqlQuery* qry = new QSqlQuery(this->db);
       qry->prepare("INSERT INTO blacklist VALUES('" + this->ui->addIpInput->text() + "','" + attackName + "');");
       qry->exec();
       model->setQuery(std::move(*qry));
       this->db.close();
    }
}


void userInterface::on_pushButton_3_clicked()
{
    std::string dosPacketsNumber = this->ui->dosInput->text().toStdString();
    std::string ddosPacketsNumber = this->ui->ddosInput->text().toStdString();
    if((dosPacketsNumber.length() > 0) && is_digits(dosPacketsNumber)){
        if((ddosPacketsNumber.length() > 0) && is_digits(ddosPacketsNumber)){
            writeToFile("WAF/conf.txt", 2, (dosPacketsNumber + "\n" + ddosPacketsNumber + "\n").c_str());
        }
    }
    else{
        QMessageBox::critical(this,"Error reading packets number!","Packets number should be more then zero!");
    }

}




