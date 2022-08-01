#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <thread>
MainWindow::MainWindow(QWidget *parent,Client *client)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->_client = client;
    this->_client->setUsername("");
    this->_client->setPassword("");
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_goToSignupButton_clicked()
{
    this->signupDialog = new signupScreen(nullptr,this->_client);
    this->signupDialog->show();
    this->close();

}


void MainWindow::on_loginButton_clicked()
{
    //Send signup message to the server
    QString username = ui->usernameInput->text();
    QString password = ui->passwordInput->text();
    this->_client->sendLogin(username.toStdString(),password.toStdString());
    std::string serverAns = this->_client->getServerMsg();
    //In case of an error show error message box
    if(serverAns != "101"){
        QMessageBox::critical(this,"Login failed","Please try again!");

    }

    else{
        this->_client->setUsername(username.toStdString());
        this->_client->setPassword(password.toStdString());
        QMessageBox::information(this,"Login","Your in!");
        //Write to config
        std::ofstream file;
        file.open("WAF/conf.txt");
        file << username.toStdString() + "\n";
        file << password.toStdString()+ "\n";
        file << "100\n";
        file << "1000\n";
        file.close();
        this->userInterfaceDialog = new userInterface(nullptr,this->_client);
        this->userInterfaceDialog->show();
        this->close();
    }
}


