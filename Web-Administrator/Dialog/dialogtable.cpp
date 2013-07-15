#include "dialogtable.h"
#include <QGridLayout>
#include <QLabel>

DialogTable::DialogTable(int *row, int *col, QString *titre, QWidget *parent):
        QDialog(parent),
        parentRow(row),
        parentCol(col),
        parentTitre(titre)
{
    editRow = 0;
    editCol = 0;
    editTitre = 0;
    ok = 0;
    cancel = 0;

    editRow = new QSpinBox();
    editCol = new QSpinBox();
    editRow->setValue(*row);
    editCol->setValue(*col);
    editTitre = new QLineEdit(*titre);

    //Labels
    QLabel *rowLabel = new QLabel(tr("Lignes") + " : ");
    QLabel *colLabel = new QLabel(tr("Colonnes") + " : ");
    QLabel *titreLabel = new QLabel(tr("titre") + " : ");

    //Buttons
    ok = new QPushButton(tr("Valider"));
    cancel = new QPushButton(tr("Annuler"));

    //layout
    QGridLayout *layout = new QGridLayout();
    layout->addWidget(rowLabel, 0, 0);
    layout->addWidget(colLabel, 1, 0);
    layout->addWidget(titreLabel, 2, 0);
    layout->addWidget(editRow, 0, 1, 1, 2);
    layout->addWidget(editCol, 1, 1, 1, 2);
    layout->addWidget(editTitre, 2, 1, 1, 2);
    layout->addWidget(ok, 3, 1);
    layout->addWidget(cancel, 3, 2);

    this->setLayout(layout);

    //Event
    connect(ok, SIGNAL(released()), this, SLOT(valider()));
    connect(cancel, SIGNAL(released()), this, SLOT(close()));

    setModal(true);
}


DialogTable::~DialogTable()
{
    delete editRow;
    delete editCol;
    delete editTitre;
    delete ok;
    delete cancel;
}

void DialogTable::valider()
{
    *parentRow = editRow->value();
    *parentCol = editCol->value();
    *parentTitre = editTitre->text();

    close();
}
