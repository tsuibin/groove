#ifndef COMM_H
#define COMM_H

#include <QWidget>



class SendMessage;
class CommServer;
class Login;
class GRegister;

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
    void showRegisterSlot();

private:
    Ui::Comm *ui;
    SendMessage *m_sendMessage;
    Login *m_login;
    CommServer *m_commServer;
    GRegister *m_gregister;
};

#endif // COMM_H
