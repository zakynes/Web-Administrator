#include "editblockdialog.h"
#include <QDateTime>
#include <QGridLayout>
#include <QPushButton>

EditBlockDialog::EditBlockDialog(QWidget *parent) :
    QDialog(parent)
{
    int width = 350;
    int height = 200;
    startIndex = 0;
    titre = new QLineEdit(this);
    index = new QSpinBox(this);
    pageName = new QLabel("", this);
    createDate = new QLabel("", this);
    lastModifDate = new QLabel("", this);
    QLabel* titreLabel = new QLabel(tr("Titre : "), this);
    QLabel* indexLabel = new QLabel(tr("Position : "), this);
    QLabel* createDateLabel = new QLabel(tr("Date de Creation : "), this);
    QLabel* modifDateLabel = new QLabel(tr("Date de modification : "), this);
    index->setMinimum(1);

    QPushButton* okButton = new QPushButton(tr("Valider"), this);
    QPushButton* cancelButton = new QPushButton(tr("Annuler"), this);
    QPushButton* touch = new QPushButton(tr("Touch"), this);

    QGridLayout* layout = new QGridLayout(this);

    layout->addWidget(pageName, 0, 1, 1, 3);
    layout->addWidget(titre, 2, 1, 1, 3);
    layout->addWidget(index, 4, 1, 1, 1);
    layout->addWidget(createDate, 6, 2, 1, 2);
    layout->addWidget(lastModifDate, 7, 2, 1, 2);
    layout->addWidget(titreLabel, 2, 0, 1, 1);
    layout->addWidget(indexLabel, 4, 0, 1, 1);
    layout->addWidget(createDateLabel, 6, 0, 1, 2);
    layout->addWidget(modifDateLabel, 7, 0, 1, 2);
    layout->addWidget(touch, 10, 0, 1, 1);
    layout->addWidget(okButton, 10, 2, 1, 1);
    layout->addWidget(cancelButton, 10, 3, 1, 1);

    layout->setContentsMargins(5,5,5,5);

    this->setContentsMargins(5,5,5,5);
    this->setLayout(layout);
    this->resize(width, height);
    this->setMaximumWidth(width);
    this->setMaximumHeight(height);
    this->setMinimumWidth(width);
    this->setMinimumHeight(height);

    connect(touch, SIGNAL(clicked()), this, SLOT(launcheTouchModifDate()));
    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

void EditBlockDialog::EditBlockDialog::setTitre(QString const& titre){
    this->titre->setText(titre);
}

void EditBlockDialog::setIndex(int const& index){
    this->startIndex = index;
    this->index->setValue(index + 1);
}

void EditBlockDialog::setMaxIndex(int const& max){
    index->setMaximum(max);
}

void EditBlockDialog::setIndexModifiable(bool const& flag){
    index->setEnabled(flag);
}

void EditBlockDialog::setPageName(QString const name){
    pageName->setText("Page : " + name);
}

void EditBlockDialog::setCreateDate(QString const date){
    createDate->setText(date);
}

void EditBlockDialog::setLastModifDate(QString const& date){
    lastModifDate->setText(date);
}

void EditBlockDialog::launcheTouchModifDate(){
    emit touchModifDate(startIndex);
}

QString EditBlockDialog::getTitre(){
    return titre->text();
}

int EditBlockDialog::getIndex(){
    return index->value() - 1;
}
