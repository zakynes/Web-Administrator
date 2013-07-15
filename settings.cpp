#include "settings.h"

Settings::Settings(QObject *parent) :
    QObject(parent)
{
}

bool Settings::fastConnexion()
{
    QSettings settings("Zakynes Soft", "Web Administrator");

    settings.beginGroup("general");
    bool ret = settings.value("fast_connect", false).toBool();
    settings.endGroup();

    return ret;
}

QString Settings::lang()
{
    QSettings settings("Zakynes Soft", "Web Administrator");

    settings.beginGroup("general");
    QString ret = settings.value("lang", "fr").toString();
    settings.endGroup();

    return ret;
}

ServerInfo Settings::defaultServeur()
{
    QSettings settings("Zakynes Soft", "Web Administrator");
    ServerInfo server;

    settings.beginGroup("default_server");
    server.host = settings.value("name", "unknow").toString();
    server.host = settings.value("host", "localhost").toString();
    server.index = settings.value("index", 1).toInt();
    server.dbName = settings.value("dbName", "wa_shemat").toString();
    server.user = settings.value("user", "root").toString();
    server.password = settings.value("password", "").toString();
    settings.endGroup();

    return server;
}

QVector<ServerInfo> Settings::listServer()
{
    QSettings settings("Zakynes Soft", "Web Administrator");
    QVector<ServerInfo> serverList;
    int serverCount = 0;

    settings.beginGroup("general");
    serverCount = settings.value("server_count", 0).toInt();
    settings.endGroup();

    serverList.clear();
    settings.beginGroup("server_list");
    for(int i=0 ; i<serverCount ; i++)
    {
        ServerInfo server;

        QVariant index = i +1;
        QString strIndex = index.toString();

        server.name = settings.value("name" + strIndex, "unknow").toString();
        server.host = settings.value("host" + strIndex, "localhost").toString();
        server.index = index.toInt();
        server.dbName = settings.value("dbName" + strIndex, "wa_shemat").toString();
        server.user = settings.value("user" + strIndex, "root").toString();
        server.password = settings.value("password" + strIndex, "").toString();

        serverList.append(server);
    }
    settings.endGroup();

    return serverList;
}

void Settings::setFastConnexion(bool const& flag)
{
    QSettings settings("Zakynes Soft", "Web Administrator");

    settings.beginGroup("general");
    settings.setValue("fast_connect", flag);
    settings.endGroup();
}

void Settings::setLang(QString lang)
{
    QSettings settings("Zakynes Soft", "Web Administrator");

    settings.beginGroup("general");
    settings.setValue("lang", lang);
    settings.endGroup();
}

void Settings::setDefautServer(ServerInfo server)
{
    QSettings settings("Zakynes Soft", "Web Administrator");

    settings.beginGroup("default_server");
    settings.setValue("name", server.name);
    settings.setValue("host", server.host);
    settings.setValue("index", server.index);
    settings.setValue("dbName", server.dbName);
    settings.setValue("user", server.user);
    settings.setValue("password", server.password);
    settings.endGroup();
}

void Settings::addServer(ServerInfo server)
{
    QSettings settings("Zakynes Soft", "Web Administrator");
    QVariant serverCount = 0;

    settings.beginGroup("general");
    serverCount = settings.value("server_count", 0).toInt();
    settings.endGroup();

    serverCount = serverCount.toInt() +1;

    QString strIndex = serverCount.toString();

    settings.beginGroup("server_list");
    settings.setValue("name" + strIndex, server.name);
    settings.setValue("host" + strIndex, server.host);
    settings.setValue("index" + strIndex, server.index);
    settings.setValue("dbName" + strIndex, server.dbName);
    settings.setValue("user" + strIndex, server.user);
    settings.setValue("password" + strIndex, server.password);
    settings.endGroup();

    settings.beginGroup("general");
    settings.setValue("server_count", serverCount.toString());
    settings.endGroup();
}

void Settings::modifyServer(ServerInfo server)
{
    QSettings settings("Zakynes Soft", "Web Administrator");
    QVariant index = server.index;
    QString strIndex = index.toString();

    settings.beginGroup("server_list");
    settings.setValue("name" + strIndex, server.name);
    settings.setValue("host" + strIndex, server.host);
    settings.setValue("index" + strIndex, server.index);
    settings.setValue("dbName" + strIndex, server.dbName);
    settings.setValue("user" + strIndex, server.user);
    settings.setValue("password" + strIndex, server.password);
    settings.endGroup();
}

void Settings::deleteServer(int const& index)
{
    QSettings settings("Zakynes Soft", "Web Administrator");
    QVector<ServerInfo> serverList = listServer();
    QVariant serverCount = 0;

    serverList.remove(index);

    settings.beginGroup("general");
    serverCount = (settings.value("server_count", 1).toInt());
    settings.endGroup();

    settings.beginGroup("server_list");
    for(int i=0 ; i<serverList.size() ; i++)
    {
        ServerInfo server = serverList.at(i);

        QVariant index = i + 1;
        QString strIndex = index.toString();
        server.index = index.toInt();

        settings.setValue("name" + strIndex, server.name);
        settings.setValue("host" + strIndex, server.host);
        settings.setValue("index" + strIndex, server.index);
        settings.setValue("dbName" + strIndex, server.dbName);
        settings.setValue("user" + strIndex, server.user);
        settings.setValue("password" + strIndex, server.password);
    }

    QString strIndex = serverCount.toString();
    settings.remove("name" + strIndex);
    settings.remove("host" + strIndex);
    settings.remove("index" + strIndex);
    settings.remove("dbName" + strIndex);
    settings.remove("user" + strIndex);
    settings.remove("password" + strIndex);

    settings.endGroup();

    settings.beginGroup("general");
    settings.setValue("server_count", serverList.size());
    settings.endGroup();

    settings.sync();
}
