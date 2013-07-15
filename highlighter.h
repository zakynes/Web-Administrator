#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>

namespace WA_UI {
class Highlighter;
}

class Highlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    explicit Highlighter(QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text);

    QTextCharFormat baliseFormat;
    QTextCharFormat attributFormat;
    QTextCharFormat attributValueFormat;
    QTextCharFormat doctypeFormat;
    QRegExp doctypePattern;
    QRegExp attributValuePattern;
    QRegExp attributPattern;
    QRegExp balisePattern;
};

#endif // HIGHLIGHTER_H
