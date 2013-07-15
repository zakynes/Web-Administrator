#include "navigationdock.h"
#include "page.h"
#include "editblockdialog.h"
#include <QMessageBox>

NavigationDock::NavigationDock(QString titre, QWidget* parent):
    QDockWidget(titre, parent)
{
    this->setFeatures(QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetMovable);
    this->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    this->setContentsMargins(0,0,0,0);

    initAction();
    initToolBar();
    initMenu();
    initTree();
    initSignalSlotsConnexion();

    setDockedStyleSheet();

    disableTools();
}
NavigationDock::~NavigationDock()
{
    delete upAction;
    delete downAction;
    delete editBlockAction;
    delete newBlockAction;
    delete deleteBlockAction;

    //Menu for export
    delete menu;

    //Widgets
    delete toolBar;
    delete tree;
}

QMenu* NavigationDock::getMenu(){
    return menu;
}

void NavigationDock::initAction()
{
    upAction = new Action("haut", "Monter", this);
    downAction = new Action("bas", "Decendre", this);
    editBlockAction = new Action("editer", "Editer", this);
    newBlockAction = new Action("nouveau", "Nouveau", this);
    deleteBlockAction = new Action("annuler", "Suprimer", this);

    newBlockAction->setShortcut(QKeySequence(QKeySequence::New));
}

void NavigationDock::initToolBar()
{
    toolBar = new QToolBar();
    toolBar->addAction(newBlockAction);
    toolBar->addAction(deleteBlockAction);
    toolBar->addAction(editBlockAction);
    toolBar->addAction(upAction);
    toolBar->addAction(downAction);

    this->setTitleBarWidget(toolBar);
}

void NavigationDock::initMenu()
{
    menu = new QMenu(tr("Site"));
    menu->addAction(upAction);
    menu->addAction(downAction);
    menu->addAction(editBlockAction);
    menu->addAction(newBlockAction);
    menu->addAction(deleteBlockAction);
}

void NavigationDock::initTree()
{
    tree = new QTreeView();
    tree->setMaximumWidth(400);
    tree->setMinimumWidth(10);
    this->setWidget(tree);
}

void NavigationDock::initSignalSlotsConnexion()
{
    connect(upAction, SIGNAL(triggered()), this, SLOT(moveUpBlock()));
    connect(downAction, SIGNAL(triggered()), this, SLOT(moveDownBlock()));
    connect(editBlockAction, SIGNAL(triggered()), this, SLOT(openEditWindows()));
    connect(newBlockAction, SIGNAL(triggered()), this, SLOT(newBlock()));
    connect(deleteBlockAction, SIGNAL(triggered()), this, SLOT(deleteBlock()));
    connect(tree, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(openBlock(QModelIndex)));
    connect(tree, SIGNAL(clicked(QModelIndex)), this, SLOT(majTools(QModelIndex)));
    connect(this, SIGNAL(dockLocationChanged(Qt::DockWidgetArea)), this, SLOT(locationHasChanged(Qt::DockWidgetArea)));
    connect(this, SIGNAL(topLevelChanged(bool)), this, SLOT(topLevelHasChanged(bool)));
}

void NavigationDock::setModel(QStandardItemModel* model)
{
    tree->setModel(model);
}

void NavigationDock::locationHasChanged(Qt::DockWidgetArea area)
{
    if(area == Qt::LeftDockWidgetArea)
    {
        setDockedStyleSheet();
        emit sendMarginEditWidget(0, 5);
    }
    else if(area == Qt::RightDockWidgetArea)
    {
        setDockedStyleSheet(false);
        emit sendMarginEditWidget(5, 0);
    }
}

void NavigationDock::setDockedStyleSheet(bool const& left)
{
    QString margin;
    if(left)
        margin = "margin-left";
    else
        margin = "margin-right";

    this->setStyleSheet("NavigationDock , QDockWidget {"
                            "background-color: rgba(0,0,0,0);"
                            "border: 0px solid black;"
                            "border-radius: 0px;"
                            "padding: 0px"
                        "}"
                        "QTreeView{ "
                            "border: 1px solid black;"
                            "border-top: 0px;"
                            "margin: 0px;"
                            "margin-bottom: 5px;"
                            + margin + ": 5px;"
                        "}"
                        "QToolBar { "
                            "background: qlineargradient(x1:0, y1:0, x2:1, y2:1,stop:0 rgb(0, 0, 0), stop:1 rgb(200, 200, 230));"
                            "margin: 0px;"
                            "margin-top: 5px;"
                            + margin + ": 5px;"
                            "border: 1px solid black;"
                            "border-bottom: 0px solid black"
                        "}");
}

void NavigationDock::topLevelHasChanged(bool topLevel)
{
    setFloatingStyleSheet();
    emit sendMarginEditWidget(5, 5);
}

void NavigationDock::majTools(QModelIndex index)
{
    int parentRow = index.parent().row();
    int row = index.row();

    QStandardItemModel* model = (QStandardItemModel*)tree->model();
    Page* parentItem = (Page*)model->item(parentRow);

    upAction->setEnabled(true);
    downAction->setEnabled(true);
    newBlockAction->setEnabled(true);
    deleteBlockAction->setEnabled(true);

    if(parentRow == -1)
    {
        disableTools();

        if(!parentItem->canAddBlock())
            newBlockAction->setEnabled(true);
    }
    else
    {
        disableTools();
        editBlockAction->setEnabled(true);

        if(!parentItem->isOrdonable())
        {
            upAction->setEnabled(true);
            downAction->setEnabled(true);
        }

        if(!parentItem->canAddBlock())
        {
            newBlockAction->setEnabled(true);
            deleteBlockAction->setEnabled(true);
        }

        if(row -1 < 0)
        {
            upAction->setEnabled(false);
        }
        if(row +1 >= parentItem->rowCount())
        {
            downAction->setEnabled(false);
        }
    }
}

void NavigationDock::disableTools()
{
    upAction->setEnabled(false);
    downAction->setEnabled(false);
    editBlockAction->setEnabled(false);
    newBlockAction->setEnabled(false);
    deleteBlockAction->setEnabled(false);
}

void NavigationDock::setFloatingStyleSheet()
{
    this->setStyleSheet("NavigationDock , QDockWidget {"
                            "background-color: rgb(0,0,0);"
                            "border: 1px solid black;"
                        "}"
                        "QTreeView {"
                            "border: 0px;"
                            "margin: 0px;"
                        "}"
                        "QToolBar {"
                            "background: qlineargradient(x1:0, y1:0, x2:1, y2:1,stop:0 rgb(0, 0, 0), stop:1 rgb(200, 200, 230)); "
                            "margin: 0px;"
                            "border: 0px;"
                        "}");
}

void NavigationDock::openBlock(QModelIndex index)
{
    int parentRow = index.parent().row();
    int row = index.row();

    if(parentRow == -1)
        return;

    QStandardItemModel* model = (QStandardItemModel*)tree->model();
    Page* page = (Page*)model->item(parentRow);
    Block* block = page->getBlockAt(row);

    emit sendOpeningBlock(block);
}

void NavigationDock::moveUpBlock()
{
    moveBlock(true);
}

void NavigationDock::moveDownBlock()
{
    moveBlock(false);
}

void NavigationDock::moveBlock(bool const& up)
{
    int move = 0;
    QModelIndex selectedIndex = tree->currentIndex();
    QModelIndex parentIndex = selectedIndex.parent();
    int row = selectedIndex.row();
    int parentRow = parentIndex.row();
    move = row;
    if(up)
        move--;
    else
        move++;

    if(parentRow == -1)
        return;

    QStandardItemModel* model = (QStandardItemModel*)tree->model();
    QStandardItem* parentItem = model->item(parentRow);

    if(move < 0
            || move >= parentItem->rowCount())
        return;

    QStandardItem* moveItem = parentItem->takeChild(row);
    parentItem->removeRow(row);
    parentItem->insertRow(move, moveItem);
    tree->setCurrentIndex(parentIndex.child(move, 0));
}

void NavigationDock::openEditWindows()
{
    EditBlockDialog* dialog = new EditBlockDialog(tree);
    QModelIndex selectedIndex = tree->currentIndex();
    QModelIndex parentIndex = selectedIndex.parent();
    int row = selectedIndex.row();
    int parentRow = parentIndex.row();
    QStandardItemModel* model = (QStandardItemModel*)tree->model();
    Page* parentItem = (Page*)model->item(parentRow);
    Block* item = parentItem->getBlockAt(row);

    dialog->setTitre(item->text());
    dialog->setIndex(row);
    dialog->setMaxIndex(parentItem->rowCount());
    dialog->setIndexModifiable(parentItem->isOrdonable());
    dialog->setPageName(parentItem->accessibleText());
    dialog->setCreateDate(item->getCreateDateTime());
    dialog->setLastModifDate(item->getlastModifDateTime());

    connect(dialog, SIGNAL(touchModifDate(unsigned short)), this, SIGNAL(touchModifDate(unsigned short)));
    connect(this, SIGNAL(sendNewModifDate(QString)), dialog, SLOT(setLastModifDate(QString)));

    if(dialog->exec() == QDialog::Accepted)
    {
        item->setTitre(dialog->getTitre());

        int index = dialog->getIndex();

        if(index != row)
        {
            QStandardItem* moveItem = parentItem->takeChild(row);
            parentItem->removeRow(row);
            parentItem->insertRow(index, moveItem);
        }
    }

    disconnect(dialog, SIGNAL(touchModifDate(unsigned short)), this, SIGNAL(touchModifDate(unsigned short)));
    disconnect(this, SIGNAL(sendNewModifDate(QString)), dialog, SLOT(setLastModifDate(QString)));
    delete dialog;
}

void NavigationDock::newBlock()
{
    EditBlockDialog* dialog = new EditBlockDialog(tree);
    QModelIndex selectedIndex = tree->currentIndex();

    if(!selectedIndex.parent().row() == -1)
        selectedIndex = selectedIndex.parent();

    int row = selectedIndex.row();
    QStandardItemModel* model = (QStandardItemModel*)tree->model();
    Page* parentItem = (Page*)model->item(row);

    dialog->setTitre("Titre");
    dialog->setIndex(1);
    dialog->setMaxIndex(1);
    dialog->setIndexModifiable(false);
    dialog->setPageName(parentItem->accessibleText());
    dialog->setCreateDate("");
    dialog->setLastModifDate("");

    if(dialog->exec() == QDialog::Accepted)
    {
        Block* item = new Block(dialog->getTitre(), "");
        parentItem->insertRow(0, item);
    }

    delete dialog;
}

void NavigationDock::deleteBlock()
{
    QMessageBox msgBox;
    msgBox.setText(tr("Supprimer definitivement le document?"));
    msgBox.setInformativeText(tr("Aucun retour ne sera possible."));
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);

    if(msgBox.exec() == QMessageBox::Ok)
    {
        emit blockHasDelete();

        QModelIndex selectedIndex = tree->currentIndex();
        QModelIndex parentIndex = selectedIndex.parent();
        int row = selectedIndex.row();
        int parentRow = parentIndex.row();

        QStandardItemModel* model = (QStandardItemModel*)tree->model();
        QStandardItem* parentItem = model->item(parentRow);
        parentItem->removeRow(row);

        emit sendDeleteBlock(parentRow +1, row +1);
    }
}

void NavigationDock::clearTree()
{
    tree->clearFocus();
    tree->clearMask();
    disableTools();
}
