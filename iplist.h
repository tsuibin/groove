#ifndef IPLIST_H
#define IPLIST_H

#include <QList>

class IPinfo;

class IPList
{
public:
    IPList();
    QList< IPinfo > m_ipList;
};

#endif // IPLIST_H
