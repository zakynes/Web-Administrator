#ifndef SERVERLISTDIALOG_H
#define SERVERLISTDIALOG_H

#include <QDialog>
#include <QVector>
#include <QLineEdit>
#include <QListView>
#include <serverinfo.h>

class ServerListDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ServerListDialog(QVector<ServerInfo> serverList, int defautServerIndex, QWidget *parent = 0);
    
signals:
    void sendDeleteServer(int index);
    void sendAddServer(ServerInfo server);
    void sendModifiedServer(ServerInfo server);
    void sendConnect(ServerInfo server);
    void setDefautServer(ServerInfo server);

private slots:
    void defaultChanged();
    void editServerInfo(QModelIndex index);
    void okPressedCustom();
    void connectPressed();
    void newServer();
    void deletePressed();

private:
    void saveCurrentServerInfo();
    QVector<ServerInfo> serverList;
    int defaultIndex;
    int currentIndex;

    QListView* listView;
    QLineEdit* nameEdit;
    QLineEdit* hostEdit;
    QLineEdit* dbEdit;
    QLineEdit* userEdit;
    QLineEdit* passwordEdit;
    
};

#endif // SERVERLISTDIALOG_H
