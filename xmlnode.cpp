#include "xmlnode.h"
#include <QRegExp>

XmlNode::XmlNode(const QString &html, int posInParentTree, XmlNode *parent) :
    QObject(),
    attribut(),
    attributValue(),
    childernNode()
{
    defaultTextColor = "#000000";
    defaultBackgroundColor = "#ffffff";
    defaultFontSize = "8pt";
    defaultFontWeight = "400";

    initByHtmlSection(html);

    this->posIntParentTree = posInParentTree;
    this->parent = parent;

    finalized = false;

    if(parent != 0)
        parent->appendChild(this);
}

XmlNode::~XmlNode()
{
    for(int i=0 ; i<childernNode.size() ; i++)
        delete childernNode.at(i);
}

bool XmlNode::isPreBalise()
{
    if(name == "pre")
        return true;
    return false;
}

QString XmlNode::toHtml()
{
    QString htmlReturn(name);

    if(isBaliseByType())
    {
        htmlReturn.prepend("<");

        for(int i=0 ; i<attribut.size() ; i++)
        {
            htmlReturn.append(" ");
            htmlReturn.append(attribut.at(i));
            htmlReturn.append("=\"");
            htmlReturn.append(attributValue.at(i));
            htmlReturn.append("\"");
        }

        if(this->type == SIMPLE_BALISE)
            htmlReturn.append("/");

        htmlReturn.append(">");
    }

    return htmlReturn;
}

QString XmlNode::toHtmlEndBalise()
{
    QString htmlReturn("");
    if(this->type == BALISE_BLOCK || this->type == BALISE_INLINE)
    {
        htmlReturn = name;
        htmlReturn.prepend("</");
        htmlReturn.append(">");
    }

    return htmlReturn;
}

XmlNode* XmlNode::getParent()
{
    return parent;
}

XmlNode::HTML_TYPE XmlNode::getType()
{
    return type;
}

QString XmlNode::getDefaultTextColor()
{
    return defaultTextColor;
}

QString XmlNode::getDefaultBackgroundColor()
{
    return defaultBackgroundColor;
}

QString XmlNode::getDefaultFontSize()
{
    return defaultFontSize;
}

QString XmlNode::getDefaultFontWeight()
{
    return defaultFontWeight;
}


XmlNode* XmlNode::getChildAt(int const& index)
{
    return childernNode.at(index);
}

int XmlNode::countChildren()
{
    return childernNode.size();
}

void XmlNode::appendChild(XmlNode* node)
{
    childernNode.append(node);
}

void XmlNode::insertChildren(int pos, QVector<XmlNode *> nodeTree)
{
    for(int i=0 ; i<nodeTree.size() ; i++)
        childernNode.insert(pos +i, nodeTree.at(i));
}


void XmlNode::setParent(int posInParentTree, XmlNode* parent)
{
    this->posIntParentTree = posInParentTree;
    this->parent = parent;
}


bool XmlNode::isFinalized(){
    return finalized;
}

void XmlNode::initByHtmlSection(QString const& html)
{
    setType(html);
    setName(html);

    if(isBaliseByType())
        setAttributsAndValue(html);
}

bool XmlNode::isBaliseByType()
{
    if(type == BALISE_BLOCK || type == BALISE_INLINE || type == SIMPLE_BALISE)
        return true;
    return false;
}

bool XmlNode::isBalise(QString const& html)
{
    QRegExp regex("^<.+>$");
    regex.setMinimal(true);

    return regex.exactMatch(html);
}

void XmlNode::setName(QString const& html)
{
    if(isBaliseByType())
    {
        QRegExp regex("<(\\S+).*>");
        regex.setMinimal(true);
        regex.indexIn(html);
        this->name = regex.cap(1);
    }
    else
        name = html;
}

void XmlNode::setType(QString const& html)
{
    if(isBalise(html))
    {
        QRegExp baliseSimple("^<\\S+\\s?[\\S+=\".*\"]*\\s?/\\s?>$");
        baliseSimple.setMinimal(true);
        QRegExp baliseBlock("^<[p|div|tab|tr|td|ul|pre]\\s?.*>$");
        baliseBlock.setMinimal(true);

        if(baliseSimple.exactMatch(html))
            this->type = SIMPLE_BALISE;
        else if(baliseBlock.exactMatch(html))
            this->type = BALISE_BLOCK;
        else
            this->type = BALISE_INLINE;
    }
    else
        this->type = TEXT;
}

void XmlNode::setAttributsAndValue(QString const& html)
{
    QRegExp attributCap("\\s?(\\S+)=\"(.+)\"");
    attributCap.setMinimal(true);
    int pos = 0;

    while ((pos = attributCap.indexIn(html, pos)) != -1)
    {
        attribut << attributCap.cap(1);
        attributValue << attributCap.cap(2);
        pos += attributCap.matchedLength();
    }
}

void XmlNode::finalize()
{
    cleanName();

    if(parent != 0)
        defineDefaultStyleByParent();

    deleteUslessStyle();
    deleteUslessAttibut();
    deleteThisUslessBalise();
}

void XmlNode::cleanName()
{
    if(type != TEXT)
        name = name.remove(" ");
}

void XmlNode::defineDefaultStyleByParent()
{
    defaultTextColor = parent->getDefaultTextColor();
    defaultBackgroundColor = parent->getDefaultBackgroundColor();
    defaultFontSize = parent->getDefaultFontSize();
    defaultFontWeight = parent->getDefaultFontWeight();
}

void XmlNode::deleteUslessStyle()
{
    for(int i=0 ; i<attribut.size() ; i++)
    {
        QString style = attributValue.at(i);

        style = style.remove(QRegExp("-qt-paragraph-type:\\s?empty\\s?;"));
        style = style.remove(QRegExp("margin-top:\\s?\\d+px\\s?;"));
        style = style.remove(QRegExp("margin-bottom:\\s?\\d+px\\s?;"));
        style = style.remove(QRegExp("margin-left:\\s?\\d+px\\s?;"));
        style = style.remove(QRegExp("margin-right:\\s?\\d+px\\s?;"));
        style = style.remove(QRegExp("-qt-list-indent:\\s?\\d+\\s?;"));
        style = style.remove(QRegExp("-qt-block-indent:\\s?\\d+\\s?;"));
        style = style.remove(QRegExp("text-indent:\\s?\\d+px\\s?;"));

        style = style.remove(QRegExp("font-size:" + defaultFontSize + ";"));
        style = style.remove(QRegExp("font-weight:" + defaultFontWeight + ";"));
        style = style.remove(QRegExp("color:" + defaultTextColor + ";"));
        style = style.remove(QRegExp("background-color:" + defaultBackgroundColor + ";"));
        style = style.remove("  ");

        attributValue.replace(i, style);
    }
}

void XmlNode::deleteUslessAttibut()
{
    QVector<QString> newAttribut;
    QVector<QString> newAttributValue;

    for(int i=0 ; i<attribut.size() ; i++)
    {
        if(attributValue.at(i).contains(QRegExp("\\S+")))
        {
            newAttribut.append(attribut.at(i));
            newAttributValue.append(attributValue.at(i));
        }
    }

    attribut = newAttribut;
    attributValue = newAttributValue;
}

void XmlNode::deleteThisUslessBalise()
{
    //Span balise only
    if(name != "span" || attribut.size() == 0 || parent != 0)
        return;

    //Move children in parent node
    parent->insertChildren(this->posIntParentTree, this->childernNode);
}

