#ifndef COMM_H
#define COMM_H

#include <QWidget>
#include "login.h"


class SendMessage;
class CommServer;


namespace Ui {
    class Comm;
}

class Comm : public QWidget
{
    Q_OBJECT

public:
    explicit Comm(QWidget *parent = 0);
    ~Comm();
    void login();

public slots:
    void createModule();

private:
    Ui::Comm *ui;
    SendMessage *m_sendMessage;
    Login *m_login;
    CommServer *m_commServer;

};

#endif // COMM_H
