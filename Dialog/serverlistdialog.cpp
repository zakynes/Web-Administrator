#include "serverlistdialog.h"
#include <QMessageBox>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>

ServerListDialog::ServerListDialog(QVector<ServerInfo> serverList, int defautServerIndex, QWidget *parent) :
    QDialog(parent)
{
    int fixHeight = 400;
    int fixWidth = 600;

    this->serverList = serverList;
    defaultIndex = defautServerIndex;
    currentIndex = -1;

    listView = new QListView(this);
    nameEdit = new QLineEdit(this);
    hostEdit = new QLineEdit(this);
    dbEdit = new QLineEdit(this);
    userEdit = new QLineEdit(this);
    passwordEdit = new QLineEdit(this);

    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    QGridLayout* editLayout = new QGridLayout(this);
    QVBoxLayout* rightLayout = new QVBoxLayout(this);
    QHBoxLayout* buttonLayout = new QHBoxLayout(this);
    QHBoxLayout* buttonLayout2 = new QHBoxLayout(this);

    QPushButton* okButton = new QPushButton(tr("Valider"), this);
    QPushButton* connectButton = new QPushButton(tr("Connecter"), this);
    QPushButton* defaultButton = new QPushButton(tr("Default"), this);
    QPushButton* newButton = new QPushButton(tr("Nouveau"), this);
    QPushButton* deleteButton = new QPushButton(tr("Suprimer"), this);

    QLabel* nameLabel = new QLabel(tr("Nom") + " : ", this);
    QLabel* hostLabel = new QLabel(tr("Host") + " : ", this);
    QLabel* dbLabel = new QLabel(tr("DB") + " : ", this);
    QLabel* userLabel = new QLabel(tr("User") + " : ", this);
    QLabel* passwordLabel = new QLabel(tr("Password") + " : ", this);

    QStandardItemModel* model = new QStandardItemModel();
    for(int i=0 ; i<serverList.size() ; i++)
    {
        QStandardItem* item = new QStandardItem(serverList.at(i).name);
        item->setEditable(false);

        if(i == defautServerIndex - 1)
            item->setIcon(QIcon("ressources/images/valider.png"));

        model->appendRow(item);
    }

    listView->setModel(model);

    editLayout->addWidget(nameLabel, 0,0,1,1);
    editLayout->addWidget(nameEdit, 0,1,1,3);
    editLayout->addWidget(hostLabel, 1,0,1,1);
    editLayout->addWidget(hostEdit, 1,1,1,3);
    editLayout->addWidget(dbLabel, 2,0,1,1);
    editLayout->addWidget(dbEdit, 2,1,1,3);
    editLayout->addWidget(userLabel, 3,0,1,1);
    editLayout->addWidget(userEdit, 3,1,1,3);
    editLayout->addWidget(passwordLabel, 4,0,1,1);
    editLayout->addWidget(passwordEdit, 4,1,1,3);

    buttonLayout->addWidget(defaultButton);
    buttonLayout->addWidget(newButton);
    buttonLayout->addWidget(deleteButton);

    buttonLayout2->addSpacing(50);
    buttonLayout2->addWidget(okButton);
    buttonLayout2->addWidget(connectButton);

    rightLayout->addLayout(editLayout);
    rightLayout->addSpacing(300);
    rightLayout->addLayout(buttonLayout);
    rightLayout->addLayout(buttonLayout2);

    mainLayout->addWidget(listView);
    mainLayout->addLayout(rightLayout);

    this->setContentsMargins(5,5,5,5);
    this->setLayout(mainLayout);
    this->resize(fixWidth, fixHeight);
    this->setMaximumWidth(fixWidth);
    this->setMaximumHeight(fixHeight);
    this->setMinimumWidth(fixWidth);
    this->setMinimumHeight(fixHeight);

    connect(okButton, SIGNAL(clicked()), this, SLOT(okPressedCustom()));
    connect(connectButton, SIGNAL(clicked()), this, SLOT(connectPressed()));
    connect(defaultButton, SIGNAL(clicked()), this, SLOT(defaultChanged()));
    connect(newButton, SIGNAL(clicked()), this, SLOT(newServer()));
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deletePressed()));

    connect(listView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(editServerInfo(QModelIndex)));

    listView->setCurrentIndex(listView->model()->index(0,0,QModelIndex()));
}

void ServerListDialog::defaultChanged()
{
    QModelIndex selectedIndex = listView->currentIndex();
    emit setDefautServer(serverList.at(selectedIndex.row()));

    QStandardItemModel* model = (QStandardItemModel*)listView->model();
    QStandardItem* item = model->item(defaultIndex -1);

    item->setIcon(QIcon());
    item = model->item(selectedIndex.row());
    item->setIcon(QIcon("ressources/images/valider.png"));

    defaultIndex = selectedIndex.row() + 1;
}

void ServerListDialog::editServerInfo(QModelIndex index)
{
    saveCurrentServerInfo();

    ServerInfo server = serverList.at(index.row());

    nameEdit->setText(server.name);
    hostEdit->setText(server.host);
    dbEdit->setText(server.dbName);
    userEdit->setText(server.user);
    passwordEdit->setText(server.password);

    currentIndex = index.row();
}

void ServerListDialog::okPressedCustom()
{
    saveCurrentServerInfo();
    accept();
}

void ServerListDialog::connectPressed()
{
    saveCurrentServerInfo();

    emit sendConnect(serverList.at(currentIndex));
    accept();
}

void ServerListDialog::newServer()
{
    if(!serverList.isEmpty())
        saveCurrentServerInfo();

    nameEdit->setText("name");
    hostEdit->setText("host");
    dbEdit->setText("dbName");
    userEdit->setText("user");
    passwordEdit->setText("password");

    ServerInfo server;
    server.name = "name";
    server.host = "host";
    server.dbName = "dbName";
    server.user = "user";
    server.password = "password";

    serverList.append(server);
    server.index = serverList.count();
    currentIndex = serverList.count() - 1;

    emit sendAddServer(server);

    QStandardItemModel* model = (QStandardItemModel*)listView->model();
    QStandardItem* item = new QStandardItem("name");
    item->setEditable(false);
    model->appendRow(item);
}

void ServerListDialog::deletePressed()
{
    if(serverList.size() == 0)
        return;

    emit sendDeleteServer(currentIndex);

    serverList.remove(currentIndex);

    QStandardItemModel* model = (QStandardItemModel*)listView->model();
    model->removeRow(currentIndex);

    if(currentIndex == defaultIndex - 1)
    {
        QModelIndex selectedIndex = listView->currentIndex();
        emit setDefautServer(serverList.at(selectedIndex.row()));

        QStandardItemModel* model = (QStandardItemModel*)listView->model();
        QStandardItem* item = model->item(selectedIndex.row());
        item->setIcon(QIcon("ressources/images/valider.png"));

        defaultIndex = selectedIndex.row() + 1;
    }
}

void ServerListDialog::saveCurrentServerInfo()
{
    if(serverList.size() == 0
            || nameEdit->text().isEmpty()
            || hostEdit->text().isEmpty()
            || dbEdit->text().isEmpty()
            || userEdit->text().isEmpty())
        return;

    ServerInfo server = serverList.at(currentIndex);
    server.name = nameEdit->text();
    server.host = hostEdit->text();
    server.dbName = dbEdit->text();
    server.user = userEdit->text();
    server.password = passwordEdit->text();

    emit sendModifiedServer(server);
}
