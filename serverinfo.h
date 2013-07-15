#ifndef SERVERINFO_H
#define SERVERINFO_H

#include <QString>

class ServerInfo
{
public:
    ServerInfo();

    QString name;
    QString host;
    int index;
    QString dbName;
    QString user;
    QString password;
};

#endif // SERVERINFO_H
