#ifndef DIALOGTABLE_H
#define DIALOGTABLE_H

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>

namespace WA_UI {
class DialogTable;
}

class DialogTable : public QDialog
{
    Q_OBJECT

public:
    explicit DialogTable(int *row, int *col, QString *titre, QWidget *parent = 0);
    ~DialogTable();

public slots:
    void valider();

protected:
    int* parentRow;
    int* parentCol;
    QString* parentTitre;
    QSpinBox* editRow;
    QSpinBox* editCol;
    QLineEdit* editTitre;
    QPushButton* ok;
    QPushButton* cancel;
};

#endif // DIALOGTABLE_H
