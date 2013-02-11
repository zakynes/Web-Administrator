#include "textedit.h"

#include <QInputDialog>
#include <QRegExp>
#include <QColorDialog>
#include <QFileDialog>

#include "dialoglien.h"
#include "dialogtable.h"

TextEdit::TextEdit(QTextEdit *parent) :
    QTextEdit(parent)
{
}

void TextEdit::bold()
{
    if(fontWeight() == QFont::Bold)
        setFontWeight(QFont::Normal);
    else
        setFontWeight(QFont::Bold);
}

void TextEdit::italic()
{
    if(fontItalic())
        setFontItalic(false);
    else
        setFontItalic(true);
}

void TextEdit::underligne()
{
    if(fontUnderline())
        setFontUnderline(false);
    else
        setFontUnderline(true);
}

void TextEdit::alignLeft()
{
    setAlignment(Qt::AlignLeft);
}

void TextEdit::alignRight()
{
    setAlignment(Qt::AlignRight);
}

void TextEdit::center()
{
    setAlignment(Qt::AlignCenter);
}

void TextEdit::justify()
{
    setAlignment(Qt::AlignJustify);
}

void TextEdit::insertList()
{
    insertHtml("<ul><li>text</li></ul>");
}

void TextEdit::insertTable()
{
    QString titre("");
    int row(0);
    int col(0);

    //Open dialog
    DialogTable dialog(&row, &col, &titre, this);
    dialog.exec();

    if(row == 0 || col == 0)
        return;

    QString table("<table border=\"1\" cellspacing=\"0\" cellpadding=\"2\">");
    if(titre != "")
        table += "<caption>" + titre + "</caption>";
    for(int i=0 ; i<row ; i++)
    {
        table += "<tr>";
        for(int j=0 ; j<col ; j++)
            table += "<th>text</th>";
        table += "</tr>";
    }
    table += "</table>";

    insertHtml(table);
}

void TextEdit::insertLien() //Open a dialog to define url and text
{
    QString text("");
    QString url("");
    bool annuler = true;
    if(textCursor().document()->toPlainText() != "")
    {
        //Save the selected text
        QString selectedText(textCursor().selectedText());
        //Define regex
        QRegExp reg("(http://|www).*");
        reg.setCaseSensitivity(Qt::CaseInsensitive);
        if(reg.exactMatch(selectedText))
            //url find
            url = selectedText;
        else
            //selectedText is juste a text
            text = selectedText;
    }

    //Open the dialog
    DialogLien dialog(&url, &text, &annuler, this);
    dialog.exec();

    if(annuler || url.isEmpty())
        return;
    if(text.isEmpty())
        text = url;

    insertHtml("<a href=\"" + url + "\">" + text + "</a>");
}

void TextEdit::insertPicture()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Ouvrire image"), "", tr("Images (*.png *.jpg *.bmp *.jpeg)"));
}

void TextEdit::insertMovie()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Ouvrire video"), "", tr("Videos pour flash(*.flv)"));
}

void TextEdit::changeFontSize(int size)
{
    setFontPointSize(size);
}

void TextEdit::changeTextColor()
{
    QColor color = QColorDialog::getColor(textColor(), this, tr("Couleur du text"));

    setTextColor(color);
}

void TextEdit::changeBackgroundColor()
{
    QColor color = QColorDialog::getColor(textBackgroundColor(), this, tr("Couleur de fond"));

    setTextBackgroundColor(color);
}
