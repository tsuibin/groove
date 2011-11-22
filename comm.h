#ifndef COMM_H
#define COMM_H

#include <QWidget>



class SendMessage;
class CommServer;
class Login;
class GRegister;
class Message;
class Tip;
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
    void sendtalkwidegt();
    void talkwidegt(QString );
    void talkMessage(QString );
    void tipshow(QString );
    void removeMsgWidgetList(QString);
    void closeALLslots();

private:
    Ui::Comm *ui;
    SendMessage *m_sendMessage;
    Login *m_login;
    CommServer *m_commServer;
    GRegister *m_gregister;
    CommServer *m_commserver;
    Message *m_message;
    Tip *m_tip;
    QList<Message *> m_msgWidgetList;
};

#endif // COMM_H
