#include "commserver.h"

CommServer::CommServer(QObject *parent) :
    QTcpServer(parent)
{
    connect(this,SIGNAL(newConnection()),this,SLOT(addConnection()));
}

void CommServer::addConnection()
{
    if ( this->hasPendingConnections() )
    {
        connection = nextPendingConnection();

        connect(connection, SIGNAL(disconnected()),this,SLOT(removeConnection()));
        connect(connection, SIGNAL(readyRead()),this,SLOT(receiveMessage()));
    }
}

void CommServer::receiveMessage()
{
    qDebug() << connection->readAll();
}

void CommServer::removeConnection()
{
    qDebug() << "user offline";
}
