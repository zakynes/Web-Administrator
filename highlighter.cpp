#include "highlighter.h"

Highlighter::Highlighter(QTextDocument *parent) :
    QSyntaxHighlighter(parent)
{
}

void Highlighter::highlightBlock(const QString &text)
{
    QTextCharFormat balise;
    balise.setFontWeight(QFont::Bold);
    balise.setForeground(Qt::blue);
    QString pattern = "</?\\w+\\s?.*\\s?/?>";

    QRegExp expression(pattern);
    expression.setMinimal(true);
    int index = text.indexOf(expression);
    while (index >= 0)
    {
       int length = expression.matchedLength();
       setFormat(index, length, balise);
       index = text.indexOf(expression, index + length);
    }

    QTextCharFormat attribut;
    attribut.setFontWeight(QFont::Normal);
    attribut.setForeground(Qt::darkMagenta);
    pattern = "(style|name|type)=\".+\"";

    expression.setPattern(pattern);
    index = text.indexOf(expression);
    while (index >= 0)
    {
      int length = expression.matchedLength();
      setFormat(index, length, attribut);
      index = text.indexOf(expression, index + length);
    }

    QTextCharFormat doctype;
    doctype.setFontWeight(QFont::Light);
    doctype.setForeground(Qt::darkCyan);
    pattern = "<!DOCTYPE.+>";

    expression.setPattern(pattern);
    index = text.indexOf(expression);
    while (index >= 0)
    {
      int length = expression.matchedLength();
      setFormat(index, length, doctype);
      index = text.indexOf(expression, index + length);
    }
}
