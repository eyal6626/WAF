#include "signupscreen.h"
#include "ui_signupscreen.h"

#include "mainwindow.h"

signupScreen::signupScreen(QWidget *parent,Client *client) :
    QWidget(parent),
    ui(new Ui::signupScreen)
{
    this->_client = client;
    ui->setupUi(this);
}

signupScreen::~signupScreen()
{
    delete ui;
}


void signupScreen::on_goToLoginButton_clicked()
{
    this->hide();
    MainWindow *mainWindow = new MainWindow(nullptr,this->_client);
    mainWindow->show();
    this->close();

}





void signupScreen::on_signupButton_clicked()
{
    QString username = ui->usernameInput->text();
    QString password = ui->passwordInput->text();
    QString email = ui->emailInput->text();
    this->_client->sendSignup(username.toStdString(),password.toStdString(),email.toStdString());
    std::string serverAns = this->_client->getServerMsg();
    if(serverAns == "201"){
        QMessageBox::information(this,"Signup","New account created!");
    }
    else if(serverAns == "202"){
        QMessageBox::critical(this,"Signup Error","Username is already exists!");
    }
    else if(serverAns == "203"){
        QMessageBox::critical(this,"Signup Error","Username has to be at least 8 characters length!");
    }
    else if(serverAns == "204"){
        QMessageBox::critical(this,"Signup Error","Password has to be at least 8 characters length!");
    }
}

