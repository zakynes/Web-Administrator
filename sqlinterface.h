#ifndef SQLINTERFACE_H
#define SQLINTERFACE_H

#include <QObject>
#include <QVector>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlError>
#include <QStandardItem>
#include <QStandardItemModel>

#include "page.h"
#include "block.h"
#include "serverinfo.h"

namespace WA_SQL {
class SqlInterface;
}

#define SELECT_PAGES "SELECT * FROM `wa_pages` ORDER BY 'index';"
#define SELECT_BLOCK "SELECT `titre`, `contents`, `create_datetime`, `last_modif` FROM `wa_block` WHERE `page_index`=:PAGEINDEX ORDER BY :ORDERBY;"
#define MODIFY_BLOCK "UPDATE `wa_block` SET `titre`=':titre', `contents`=':contents', `index`=':index', `last_modif`=NOW() WHERE `global_index`=?;"
#define DELETE_BLOCK "DELETE FROM `wa_block` WHERE `page_index`=? AND `index`=?"
#define ADD_BLOCK "INSERT INTO `wa_block` (`titre`, `contents`, `index`, `last_modif`, `create_datetime`) VALUES (':titre', ':contents', ':index', NOW(), NOW());"
#define TOUCHE_MODIF "UPDATE `wa_block` SET `last_modif`=NOW() WHERE `global_index`=?;"

class SqlInterface : public QObject
{
    Q_OBJECT
public:
    explicit SqlInterface(QObject *parent = 0);
    ~SqlInterface();

    void setPages(QStandardItemModel *pages);
    QStandardItemModel *getPages();
protected:
    void initSqlDatabase(ServerInfo server = ServerInfo());
    void openConnexion(); //Open if no instance in work
    void closeConnexion(); //Close when no one request in work

    QStandardItemModel* pages;
    QSqlDatabase db;
    
signals:
    void setProgressComplete();
    void setMaxProgressBar(int max);
    void setMinProgressBar(int min);
    void setProgressBarValue(int value);
    void sendModel(QStandardItemModel* model);
    void sendNewModifDate(QString date);
    void sendOpenError(QSqlError error);
    
public slots:
    void connectDB(ServerInfo server);
    void upload();
    void download();
    void touche(unsigned short index);
    void deleteBlock(const unsigned short &PageIndex, const unsigned short &index);
    void progressComplete();
    void progressValue(int value);
    
};

#endif // SQLINTERFACE_H
