#ifndef HTMLBUILDER_H
#define HTMLBUILDER_H

#include <QObject>
#include <QRegExp>
#include "xmlnode.h"

class HtmlBuilder : public QObject
{
    Q_OBJECT

private:
    QRegExp regexBalise;
    QRegExp regexEndBalise;
    QRegExp regexSimpleBalise;

public:
    explicit HtmlBuilder();

    QString returnCleanedHtmlText(QString const &originalText);

protected:
    QString htmlText;
    XmlNode* structuredHtmlText;

    void cleanHtmlText();
    void deleteDoctype();
    void deleteHtmlBalise();
    void deleteEntete();
    void deleteBodyBalise();

    void buildStructuredHtmlTextNode(QString &text, XmlNode *parentNode);
    void createTextNodeIfNessesary(QString text, int &posInParentNode, XmlNode *parentNode);

    void finalizeStructuredHtmlText(XmlNode *node);

    void rebuildHtmlText(int tabulation, XmlNode *node);
    void insertTabulation(const int &tabulation, XmlNode *node);
    void insertNewLineOnNessesary(XmlNode* node);
};

#endif // HTMLBUILDER_H
