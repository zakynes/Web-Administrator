#ifndef XMLNODE_H
#define XMLNODE_H

#include <QObject>
#include <QVector>

class XmlNode : public QObject
{
    Q_OBJECT

public:
    enum HTML_TYPE {BALISE_BLOCK, BALISE_INLINE, SIMPLE_BALISE, TEXT, INVALIDE_HTML};

private:
    bool finalized;
    XmlNode* parent;
    int posIntParentTree;
    QString name;
    QString defaultTextColor;
    QString defaultBackgroundColor;
    QString defaultFontSize;
    QString defaultFontWeight;
    HTML_TYPE type;
    QVector<QString> attribut;
    QVector<QString> attributValue;
    QVector<XmlNode*> childernNode;

public:
    explicit XmlNode(QString const& html, int posInParentTree = 0, XmlNode *parent = 0);
    ~XmlNode();

    bool isPreBalise();

    QString toHtml();
    QString toHtmlEndBalise();

    XmlNode* getParent();
    HTML_TYPE getType();

    QString getDefaultTextColor();
    QString getDefaultBackgroundColor();
    QString getDefaultFontSize();
    QString getDefaultFontWeight();

    XmlNode* getChildAt(int const& index);
    int countChildren();

    void appendChild(XmlNode* node);
    void insertChildren(int pos, QVector<XmlNode*> nodeTree);

    void setParent(int posInParentTree = 0, XmlNode* parent = 0);

    bool isFinalized();
    void finalize();

protected:
    void initByHtmlSection(QString const& html);
    bool isBaliseByType();
    bool isBalise(QString const& html);
    void setName(QString const& html);
    void setType(QString const& html);
    void setAttributsAndValue(QString const& html);

    void cleanName();
    void defineDefaultStyleByParent();
    void deleteUslessStyle();
    void deleteUslessAttibut();
    void deleteThisUslessBalise();
    
};

#endif // XMLNODE_H
