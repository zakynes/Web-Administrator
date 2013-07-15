#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QTextEdit>

namespace WA_UI {
class TextEdit;
}

class TextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit TextEdit(QTextEdit *parent = 0);
    bool isTextBaseColor();
    bool isTextBaseBackgroundColor();
    void changeTextColor();
    void changeBackgroundColor();
    
signals:
    
public slots:
    //Edit function
    void bold();
    void italic();
    void underline();
    void alignLeft();
    void alignRight();
    void center();
    void justify();
    void insertList();
    void insertTable();
    void insertLien();
    void insertPicture();
    void insertMovie();
    void changeFontSize(int size);
    void executeRightColorAction();
    void executeRightBackgroundColorAction();

protected:
    bool canInsertFromMimeData(const QMimeData *source);
    void insertFromMimeData(const QMimeData *source);
};

#endif // TEXTEDIT_H
