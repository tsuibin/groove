#include "ipinfo.h"
QString IPinfo::IPv4Address = IPinfo::getIpv4Address();

IPinfo::IPinfo()
{

}

QString IPinfo::getIpv4Address()
{
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach (QHostAddress address, list) {
       if(address.protocol() == QAbstractSocket::IPv4Protocol) {
           if (address.toString().contains("127.0.0.1")) {
                continue;
            }
            return address.toString();
       }
    }
}
