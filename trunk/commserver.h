#ifndef COMMSERVER_H
#define COMMSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QSqlQuery>
class Message;
class CommServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit CommServer(QObject *parent = 0);
    QTcpSocket* tcpsocket;
    void init();

signals:
    void emitmessage(QByteArray tmp);

    void newmessageemit(QString );

    void oldmessageemit(QString );

public slots:
    void newConnectSlot();
    void readMessage();
    void removeConnection();

private:
    QList < QTcpSocket* > userList;//QList为类名，相当于链表，userList为变量，保存的数据全为QTcpSocket*类型
    QString getIP();
};

#endif // COMMSERVER_H
