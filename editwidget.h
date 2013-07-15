#ifndef EDITWIDGET_H
#define EDITWIDGET_H

#include <QStackedWidget>
#include <QPlainTextEdit>
#include <QTextDocument>

#include "textedit.h"
#include "block.h"
#include "highlighter.h"

class EditWidget : public QStackedWidget
{
    Q_OBJECT

private:
    TextEdit* richeEditor;
    QPlainTextEdit* htmlEditor;
    Block* document;
    Highlighter* highlighter;
    bool richeMode;

public:
    EditWidget(QWidget* parent = 0);

    TextEdit* getRicheEditor();

    friend class MainControler;

public slots:
    void switchEditor();
    void setDocument(Block *doc);
    void majMargin(int left, int right);
    void setCurrentBlockHasModified();
    void setDefault();

signals:
    void setStatTools(bool riche);
    void redoAvailable(bool);
    void undoAvailable(bool);
};

#endif // EDITWIDGET_H
