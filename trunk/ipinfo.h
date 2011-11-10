#ifndef IPINFO_H
#define IPINFO_H

#include <QString>
#include <QHostAddress>
#include <QNetworkInterface>

class IPinfo
{
public:
    IPinfo();
    static QString IPv4Address;
    QString username;
    QString IPaddress;
protected:
    static QString getIpv4Address();
};




#endif // IPINFO_H
