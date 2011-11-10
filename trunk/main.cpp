#include <QtGui/QApplication>
#include <QTextCodec>
#include <QNetworkInterface>

#include "comm.h"
#include "commserver.h"
#include "gsession.h"
#include "ipinfo.h"


quint16 port;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));



    Comm w;
    w.login();

    /*
    CommServer s;

    port = 5000;
    if ( s.listen(QHostAddress::Any, port) ) {
        qDebug() << "listen ok";
    } else {
        qDebug() << s.errorString();
    }
*/


    qDebug() << IPinfo::IPv4Address;







    return a.exec();

}
