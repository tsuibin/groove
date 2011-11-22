#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "gsession.h"


namespace Ui {
    class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();
signals:
    void loginSuccess();
    void showRegister();

private slots:
    void on_pushButton_login_clicked();

    void on_pushButton_reg_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
