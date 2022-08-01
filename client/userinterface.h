#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "client.h"
#include <QWidget>
#include <string>
#include <QFileDialog>
#include <QDir>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>
#include <iostream>
#include <limits>
#include <fstream>

namespace Ui {
class userInterface;
}

class userInterface : public QWidget
{
    Q_OBJECT

public:
    explicit userInterface(QWidget *parent = nullptr,Client *client = nullptr);
    ~userInterface();
    std::string extractDataFromLogMsg(std::string msg);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_browseBlacklist_clicked();

    void on_deleteIpButton_2_clicked();

    void on_reloadBlacklist_clicked();

    void on_addIpButton_clicked();

    void on_pushButton_3_clicked();

private:
    Client* _client;
    Ui::userInterface *ui;
    QString _DBfileName;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
};

#endif // USERINTERFACE_H
