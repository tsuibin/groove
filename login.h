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

private slots:
    void on_pushButton_login_clicked();

private:
    Ui::Login *ui;
    QSqlDatabase m_db;
};

#endif // LOGIN_H
