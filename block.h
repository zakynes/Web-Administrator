#ifndef BLOCK_H
#define BLOCK_H

#include <QStandardItem>
#include <QTime>
#include <QDate>
#include <QDateTime>

namespace WA_DATA {
class Block;
}

class Block : public QStandardItem
{
public:
    explicit Block(QString const& titre, QString const& html = "");

    static QString returnFormatForDateTime();

    void setCustomHtml(const QString &html);
    void setCreateDateTime(QDateTime dateTime);
    void setlastModifDateTime(QDateTime dateTime);
    QString getCreateDateTime();
    QString getlastModifDateTime();
    int getBlockIndex();
    void setTitre(QString const& str);
    bool isNew();
    bool isModified();
    QString toWebSite();
    void buildToolTip();
    void saved();
    void isNewDoc();
    void modified();

private:
    bool m_new;
    bool m_modified;
    QString html;
    QDateTime createDateTime;
    QDateTime lastModifDateTime;

};

#endif // BLOCK_H
