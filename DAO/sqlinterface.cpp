#include "sqlinterface.h"
#include <QStringList>
#include <QException>
#include <QDateTime>
#include "serverinfo.h"

SqlInterface::SqlInterface(QObject *parent) :
    QObject(parent)
{
    pages = new QStandardItemModel();
    pages->appendRow(new QStandardItem("test"));

    initSqlDatabase();
}


SqlInterface::~SqlInterface()
{
    closeConnexion();

    delete pages;
}


void SqlInterface::setPages(QStandardItemModel *pages){this->pages = pages;}
QStandardItemModel *SqlInterface::getPages(){return this->pages;}

void SqlInterface::openConnexion()
{
    if(!db.open())
        emit sendOpenError(db.lastError());
}

void SqlInterface::closeConnexion()
{
    if(db.isOpen())
        db.close();
}

void SqlInterface::initSqlDatabase(ServerInfo server)
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(server.host);
    db.setDatabaseName(server.dbName);
    db.setUserName(server.user);
    db.setPassword(server.password);
}

void SqlInterface::upload()
{
    if(!db.isOpen())
        openConnexion();

    QSqlQuery queryNewBlock;
    QSqlQuery queryModifBlock;
    queryNewBlock.prepare(""ADD_BLOCK);
    queryModifBlock.prepare(""MODIFY_BLOCK);

    for(int i=0 ; i<pages->rowCount() ; i++)
    {
        Page* currentPage = (Page*)pages->item(i);

        for(int j=0 ; j<currentPage->rowCount() ; j++)
        {
            Block* currentBlock = currentPage->getBlockAt(j);

            if(currentBlock->isNew())
            {
                queryNewBlock.bindValue(":titre", currentBlock->text());
                queryNewBlock.bindValue(":contents", currentBlock->toWebSite());
                queryNewBlock.bindValue(":index", currentBlock->index().row());
                queryNewBlock.exec();
            }
            else if(currentBlock->isModified())
            {
                queryNewBlock.bindValue(":titre", currentBlock->text());
                queryNewBlock.bindValue(":contents", currentBlock->toWebSite());
                queryNewBlock.bindValue(":index", currentBlock->index().row());
                queryModifBlock.exec();
            }

            currentBlock->saved();
        }
    }
}

void SqlInterface::download()
{
    pages->clear();

    if(!db.isOpen())
        openConnexion();

    QSqlQuery querySelectPages;
    QSqlQuery querySelectBlockFromPage;
    querySelectPages.prepare(""SELECT_PAGES);
    querySelectBlockFromPage.prepare(""SELECT_BLOCK);

    querySelectPages.exec();
    while(querySelectPages.next())
    {
        //Create page
        Page* page = new Page(querySelectPages.value(1).toString());
        page->setMultiblock(querySelectPages.value(2).toBool());
        page->setOrdonable(querySelectPages.value(3).toBool());
        page->setAddBlock(querySelectPages.value(4).toBool());
        page->setOrderByDate(querySelectPages.value(5).toBool());
        page->buildToolTip();
        pages->appendRow(page);

        //Add bind value
        int pageRow = page->getIndexRow();
        querySelectBlockFromPage.bindValue(":PAGEINDEX", pageRow +1);
        querySelectBlockFromPage.bindValue(":ORDERBY", "'index'");
        if(page->isDateOrder())
            querySelectBlockFromPage.bindValue(":ORDERBY", "'create_datetime'");
        querySelectBlockFromPage.exec();
        while(querySelectBlockFromPage.next())
        {
            Block* block = new Block(querySelectBlockFromPage.value(0).toString());
            block->setCustomHtml(querySelectBlockFromPage.value(1).toString());
            block->setCreateDateTime(querySelectBlockFromPage.value(2).toDateTime());
            block->setlastModifDateTime(querySelectBlockFromPage.value(3).toDateTime());
            block->buildToolTip();
            page->appendRow(block);
        }
    }

    emit sendModel(pages);
}

void SqlInterface::touche(unsigned short index)
{
    if(!db.isOpen())
        openConnexion();

    QSqlQuery query;

    query.prepare(""TOUCHE_MODIF);
    query.addBindValue(index);
    query.exec();

    query.prepare("SELECT `last_modif` FROM `wa_block` WHERE `page_index`=?");
    query.addBindValue(index);
    query.exec();
    query.next();

    QDateTime date = query.value(0).toDateTime();

    emit sendNewModifDate(date.toString());
}

void SqlInterface::deleteBlock(const unsigned short &PageIndex, const unsigned short &index)
{
    if(!db.isOpen())
        openConnexion();

    QSqlQuery query;

    query.prepare(""DELETE_BLOCK);
    query.addBindValue(PageIndex);
    query.addBindValue(index);
    query.exec();
}


void SqlInterface::progressComplete()
{

}

void SqlInterface::progressValue(int value)
{

}


void SqlInterface::connectDB(ServerInfo server)
{
    if(db.isOpen())
        closeConnexion();

    initSqlDatabase(server);

    download();
}
