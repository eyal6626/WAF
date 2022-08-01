#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"
#include "signupscreen.h"
#include <QMessageBox>
#include "userinterface.h"
#include <iostream>
#include <fstream>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr,Client *client = nullptr);
    ~MainWindow();

private slots:
    void on_goToSignupButton_clicked();

    void on_loginButton_clicked();

private:
    Ui::MainWindow *ui;
    signupScreen* signupDialog;
    userInterface* userInterfaceDialog;
    Client* _client;

};

#endif // MAINWINDOW_H
