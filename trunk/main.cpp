#include <QtGui/QApplication>
#include <QTextCodec>
#include "comm.h"
#include "commserver.h"


quint16 port;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    Comm w;
    w.login();

    return a.exec();
}
