#include "block.h"
#include "htmlbuilder.h"

#include <QObject>

Block::Block(const QString &titre, const QString &html):
    QStandardItem(titre)
{
    this->html = html;
    setText(titre);
    setCustomHtml(html);
    m_modified = false;
    setEditable(false);
}

QString Block::returnFormatForDateTime(){
    return "yyyy-MM-dd hh-mm-ss";
}

void Block::setCreateDateTime(QDateTime dateTime){
    createDateTime = dateTime;
}

void Block::setlastModifDateTime(QDateTime dateTime){
    lastModifDateTime = dateTime;
}

QString Block::getCreateDateTime(){
    return createDateTime.toString();
}

QString Block::getlastModifDateTime(){
    return lastModifDateTime.toString();
}

void  Block::setCustomHtml(QString const& html)
{
    this->html = html;//Need reformat html
}

int Block::getBlockIndex()
{
    return index().row();
}

void Block::setTitre(QString const& str)
{
    setText(str);
    modified();
}

bool Block::isNew()
{
    return m_new;
}

bool Block::isModified()
{
    return m_modified;
}

QString Block::toWebSite()
{
    HtmlBuilder builder;
    return builder.returnCleanedHtmlText(html);
}

void Block::buildToolTip()
{
    QString description = "";

    description.append("Date de creation : \n   ");
    description.append(createDateTime.toString(returnFormatForDateTime()));

    description.append("\n\nDate de modification : \n   ");
    description.append(lastModifDateTime.toString(returnFormatForDateTime()));

    setToolTip(description);

}

void Block::isNewDoc()
{
    m_new = true;
    modified();
}

void Block::modified()
{
    m_modified = true;
}

void Block::saved()
{
    m_new = false;
    m_modified = false;
}

