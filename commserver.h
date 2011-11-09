#ifndef COMMSERVER_H
#define COMMSERVER_H

#include <QTcpServer>
#include <QTcpSocket>

class CommServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit CommServer(QObject *parent = 0);
    QTcpSocket* connection;

signals:

public slots:
    void addConnection();
    void receiveMessage();
    void removeConnection();

};

#endif // COMMSERVER_H
