#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QVector>
#include <QSettings>
#include "serverinfo.h"

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = 0);

    bool fastConnexion();
    QString lang();
    ServerInfo defaultServeur();
    QVector<ServerInfo> listServer();

public slots:
    void setFastConnexion(bool const& flag);
    void setLang(QString lang);
    void setDefautServer(ServerInfo server);
    void addServer(ServerInfo server);
    void modifyServer(ServerInfo server);
    void deleteServer(int const& index);
    
};

#endif // SETTINGS_H
