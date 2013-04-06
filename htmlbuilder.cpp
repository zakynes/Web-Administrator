#include "htmlbuilder.h"
#include <QRegExp>

HtmlBuilder::HtmlBuilder() :
    QObject()
{
    regexBalise.setPattern("(<.+>)");
    regexBalise.setMinimal(true);

    regexEndBalise.setPattern("^<\\s?/.+>$");
    regexEndBalise.setMinimal(true);

    regexSimpleBalise.setPattern("^<.+/\\s?>$");
    regexSimpleBalise.setMinimal(true);

    structuredHtmlText = 0;
}

QString HtmlBuilder::returnCleanedHtmlText(QString const &originalText)
{
    delete structuredHtmlText;

    structuredHtmlText = new XmlNode("<div>");
    htmlText = originalText;

    cleanHtmlText();

    buildStructuredHtmlTextNode(htmlText, structuredHtmlText);

    htmlText = "";

    finalizeStructuredHtmlText(structuredHtmlText);

    rebuildHtmlText(0, structuredHtmlText);

    return htmlText.section("\n", 1);
}

void HtmlBuilder::cleanHtmlText()
{
    deleteDoctype();
    deleteHtmlBalise();
    deleteEntete();
    deleteBodyBalise();
}

void HtmlBuilder::deleteDoctype()
{
    QRegExp regex("<!DOCTYPE.*>");
    regex.setMinimal(true);
    htmlText.remove(regex);
}

void HtmlBuilder::deleteHtmlBalise()
{
    QRegExp regex("</?html.*>");
    regex.setMinimal(true);
    htmlText.remove(regex);
}

void HtmlBuilder::deleteEntete()
{
    QRegExp regex("<head.*>.*</head>");
    regex.setMinimal(true);
    htmlText.remove(regex);
}

void HtmlBuilder::deleteBodyBalise()
{
    QRegExp regex("</?body.*>");
    regex.setMinimal(true);
    htmlText.remove(regex);
}


void HtmlBuilder::buildStructuredHtmlTextNode(QString &text, XmlNode *parentNode)
{
    int posInParentNode = 0;
    XmlNode* node;
    QString beforBalise;
    QString balise;

    while(!text.isEmpty())
    {
        beforBalise = text.section(regexBalise, 0, 0);

        regexBalise.indexIn(text);
        balise = regexBalise.cap(1);

        text = text.section(regexBalise, 1);

        createTextNodeIfNessesary(beforBalise, posInParentNode, parentNode);

        if(regexEndBalise.exactMatch(balise))
            return;

        node = new XmlNode(balise, posInParentNode, parentNode);

        if(!regexSimpleBalise.exactMatch(balise))
            buildStructuredHtmlTextNode(text, node);

        posInParentNode++;
    }
}

void HtmlBuilder::createTextNodeIfNessesary(QString text, int &posInParentNode, XmlNode *parentNode)
{
    if(!parentNode->isPreBalise())
        text.remove("\n");
    if(!text.isEmpty())
    {
        XmlNode* node = new XmlNode(text, posInParentNode, parentNode);
        posInParentNode++;
    }
}

void HtmlBuilder::finalizeStructuredHtmlText(XmlNode* node)
{
    node->finalize();

    for(int i=0 ; i<node->countChildren() ; i++)
        finalizeStructuredHtmlText(node->getChildAt(i));
}

void HtmlBuilder::rebuildHtmlText(int tabulation, XmlNode *node)
{
    insertNewLineOnNessesary(node);
    insertTabulation(tabulation, node);

    htmlText += node->toHtml();

    for(int i=0 ; i<node->countChildren() ; i++)
        rebuildHtmlText(tabulation +1, node->getChildAt(i));

    if(node->getType() == XmlNode::BALISE_BLOCK || node->getType() == XmlNode::BALISE_INLINE)
    {
        insertNewLineOnNessesary(node);
        insertTabulation(tabulation, node);

        htmlText += node->toHtmlEndBalise();
    }
}

void HtmlBuilder::insertTabulation(int const& tabulation, XmlNode* node)
{
    if(node->getType() == XmlNode::BALISE_BLOCK)
        for(int i=0 ; i<tabulation ; i++)
            htmlText += "    ";
}

void HtmlBuilder::insertNewLineOnNessesary(XmlNode* node)
{
    if(node->getType() == XmlNode::BALISE_BLOCK)
        htmlText += "\n";
}

