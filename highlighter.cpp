#include "highlighter.h"

Highlighter::Highlighter(QTextDocument *parent) :
    QSyntaxHighlighter(parent)
{
    baliseFormat.setFontWeight(QFont::Bold);
    baliseFormat.setForeground(Qt::blue);

    attributFormat.setFontWeight(QFont::Normal);
    attributFormat.setForeground(Qt::darkMagenta);

    attributValueFormat.setFontWeight(QFont::Normal);
    attributValueFormat.setForeground(Qt::red);

    doctypeFormat.setFontWeight(QFont::Light);
    doctypeFormat.setForeground(Qt::darkCyan);

    balisePattern.setPattern("(</?\\w+\\s?.*\\s?/?>)");
    balisePattern.setMinimal(true);

    attributPattern.setPattern("\\s+.+=\".*\"");
    attributPattern.setMinimal(true);

    attributValuePattern.setPattern("\".+\"");
    attributValuePattern.setMinimal(true);

    doctypePattern.setPattern("<!DOCTYPE.+>");
    doctypePattern.setMinimal(true);
}

void Highlighter::highlightBlock(const QString &text)
{
    int index = text.indexOf(balisePattern);
    while (index >= 0)
    {
        balisePattern.indexIn(text, index);
        QString capturedText = balisePattern.cap(1);

        int lengthBalise = balisePattern.matchedLength();
        setFormat(index, lengthBalise, baliseFormat);

        int indexAttribut = capturedText.indexOf(attributPattern);
        while(indexAttribut >= 0)
        {
            int lengthAttribut = attributPattern.matchedLength();
            setFormat(index + indexAttribut, lengthAttribut, attributFormat);
            indexAttribut = capturedText.indexOf(attributPattern, indexAttribut + lengthAttribut);
        }

        int indexAttributValue = capturedText.indexOf(attributValuePattern);
        while(indexAttributValue >= 0)
        {
            int lengthAttributValue = attributValuePattern.matchedLength();
            setFormat(index + indexAttributValue + 1, lengthAttributValue - 2, attributValueFormat);
            indexAttributValue = capturedText.indexOf(attributValuePattern, indexAttributValue + lengthAttributValue);
        }

        index = text.indexOf(balisePattern, index + lengthBalise);
    }


    int indexDoctype = text.indexOf(doctypePattern);
    if(indexDoctype >= 0)
    {
        int lengthDoctype = doctypePattern.matchedLength();
        setFormat(indexDoctype, lengthDoctype, doctypeFormat);
    }
}
