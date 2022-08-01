#ifndef SIGNUPSCREEN_H
#define SIGNUPSCREEN_H

#include <QWidget>
#include "client.h"

namespace Ui {
class signupScreen;
}

class signupScreen : public QWidget
{
    Q_OBJECT

public:
    explicit signupScreen(QWidget *parent = nullptr,Client *client = nullptr);
    ~signupScreen();

private slots:
    void on_goToLoginButton_clicked();

    void on_signupButton_clicked();

private:
    Ui::signupScreen *ui;
    Client* _client;
};

#endif // SIGNUPSCREEN_H
