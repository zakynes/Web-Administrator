#include "editwidget.h"
#include "highlighter.h"

EditWidget::EditWidget(QWidget *parent):
    QStackedWidget(parent)
{
    //Rich text
    richeEditor = new TextEdit();
    richeEditor->setContentsMargins(20, 20, 20, 20);
    richeEditor->setAutoFormatting(QTextEdit::AutoNone);

    highlighter = new Highlighter();
    //richeEditor->addAction(copyAction);
    //richeEditor->addAction(cutAction);
    //richeEditor->addAction(pasteAction);

    //Plain text
    htmlEditor = new QPlainTextEdit();
    highlighter->setDocument(htmlEditor->document());

    setDefault();

    //htmlEditor->addAction(copyAction);
    //htmlEditor->addAction(cutAction);
    //htmlEditor->addAction(pasteAction);

    this->addWidget(richeEditor);
    this->addWidget(htmlEditor);
    this->setContentsMargins(0,5,5,5);
    this->setCurrentIndex(0);

    connect(richeEditor, SIGNAL(textChanged()), this, SLOT(setCurrentBlockHasModified()));
    connect(htmlEditor, SIGNAL(textChanged()), this, SLOT(setCurrentBlockHasModified()));
}

void EditWidget::setDefault()
{
    richeEditor->setHtml("<h1>titre test</h1><p><img src=\"ressources/images/flash-video.png\"/><img src=\"video:lien\"/></p><p>text <strong>test</strong><br />test pour le <span style=\"color:#ff0000;\">bold</span><p/>");

    document = new Block("null", "null");
    richeMode = true;
    emit setStatTools(richeMode);
}

TextEdit* EditWidget::getRicheEditor(){
    return richeEditor;
}

void EditWidget::setDocument(Block *doc)
{
    disconnect(richeEditor, SIGNAL(textChanged()), this, SLOT(setCurrentBlockHasModified()));
    disconnect(htmlEditor, SIGNAL(textChanged()), this, SLOT(setCurrentBlockHasModified()));
    document->setCustomHtml((richeMode)? richeEditor->toHtml() : htmlEditor->toPlainText());

    document = doc;
    richeEditor->setHtml(document->toWebSite());
    this->setCurrentIndex(0);
    richeMode = true;
    emit setStatTools(richeMode);

    connect(richeEditor, SIGNAL(textChanged()), this, SLOT(setCurrentBlockHasModified()));
    connect(htmlEditor, SIGNAL(textChanged()), this, SLOT(setCurrentBlockHasModified()));
}

void EditWidget::switchEditor()
{
    if(richeMode)
    {
        document->setCustomHtml(richeEditor->toHtml());
        htmlEditor->setPlainText(document->toWebSite());
        this->setCurrentIndex(1);
        richeMode = false;
    }
    else
    {
        richeEditor->setHtml(htmlEditor->toPlainText());
        this->setCurrentIndex(0);
        richeMode = true;
    }

    emit setStatTools(richeMode);
}

void EditWidget::majMargin(int left, int right)
{
    setContentsMargins(left, 5, right, 5);
}

void EditWidget::setCurrentBlockHasModified()
{
    document->modified();
}
