#include "dialoglien.h"
#include <QGridLayout>
#include <QLabel>

DialogLien::DialogLien(QString *url, QString *text, bool *annuler, QWidget *parent):
    QDialog(parent),
    parentUrl(url),
    parentText(text),
    parentAnnuler(annuler)
{
    urlEdit = new QLineEdit(*url);
    textEdit = new QLineEdit(*text);

    //Labels
    QLabel *urlLabel = new QLabel();
    urlLabel->setText(tr("URL") + " : ");
    QLabel *textLabel = new QLabel();
    textLabel->setText(tr("Text") + " : ");

    //Buttons
    ok = new QPushButton(tr("Valider"));
    cancel = new QPushButton(tr("Annuler"));

    //layout
    QGridLayout *layout = new QGridLayout();
    layout->addWidget(urlLabel, 2, 2);
    layout->addWidget(urlEdit, 2, 3, 1, 2);
    layout->addWidget(textLabel, 3, 2);
    layout->addWidget(textEdit, 3, 3, 1, 2);
    layout->addWidget(ok, 4, 3);
    layout->addWidget(cancel, 4, 4);

    this->setLayout(layout);

    //Event
    connect(ok, SIGNAL(released()), this, SLOT(valider()));
    connect(cancel, SIGNAL(released()), this, SLOT(close()));

    setModal(true);
}

void DialogLien::valider()
{
    *parentUrl = urlEdit->text();
    *parentText = textEdit->text();
    *parentAnnuler = false;

    close();
}
