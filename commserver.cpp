#include "commserver.h"
#include "message.h"

CommServer::CommServer(QObject *parent) :
    QTcpServer(parent)
{
    init();
    connect(this,SIGNAL(newConnection()),this,SLOT(newConnectSlot()));
    qDebug() << "Comm";
}

void CommServer::init()
{
    if(this->listen(QHostAddress::Any,5000))
    {
        qDebug() << "listen ok!";
    }
    else{
         qDebug() << "listen error!";
    }
}

void CommServer::newConnectSlot()
{

    qDebug() << "newConnectSlot";
    QTcpSocket *tcp = this->nextPendingConnection();//连接描述符
    connect(tcp,SIGNAL(readyRead()),this,SLOT(readMessage()));
    userList << tcp;
}

void CommServer::readMessage()
{

    QByteArray tmp;
    QSqlQuery ms_query;
    QTcpSocket* socket = static_cast< QTcpSocket* >(sender());//收到信号则给socket
    QString ip;
    ip = socket->peerAddress().toString();

    tmp.append( socket->readAll());
     QString ms_sql = "insert into usermessage(ip,messagetmp,flag) values('";
     ms_sql.append(ip + "','");
     ms_sql.append( tmp+ "',");
     ms_sql.append("1);");
     qDebug()<< ms_sql<<"ms_sql";
     qDebug()<<ms_query.exec( ms_sql )<<"ms_query.exec( ms_sql )";
     if ( ms_query.exec( ms_sql ) ) {

         qDebug() << "insert ok";
       }
     emit emitmessage(tmp);

    for(int i = 0; i < GSession::ipList.count(); i++){
        if(ip == GSession::ipList.at(i)){
            emit oldmessageemit(ip);
            break;
        }
    }
    int j = 0;
    for(int i = 0; i < GSession::ipList.count(); i++){
        if(ip != GSession::ipList.at(i)){
            j++;
        }
    }
    if(j == GSession::ipList.count()){
        emit newmessageemit(ip);
    }
    GSession::ipList.append(ip);
}

void CommServer::removeConnection()
{
    qDebug() << "user offline";
}

QString CommServer::getIP()//查找IP
{
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach (QHostAddress address, list)
    {
        if(address.protocol() == QAbstractSocket::IPv4Protocol)
        {
            if(address.toString().contains("127.0."))
            {
                continue;
            }
            return address.toString();
        }
    }
    return 0;
}


