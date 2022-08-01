#include "client.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    Client* client = new Client();
    QApplication a(argc, argv);
    MainWindow w(nullptr,client);
    w.show();
    a.exec();
    delete client;
    return 0;
}


