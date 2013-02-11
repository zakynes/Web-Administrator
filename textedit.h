#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QTextEdit>

class TextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit TextEdit(QTextEdit *parent = 0);
    
signals:
    
public slots:
    //Edit function
    void bold();
    void italic();
    void underligne();
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
    void changeTextColor();
    void changeBackgroundColor();
};

#endif // TEXTEDIT_H
