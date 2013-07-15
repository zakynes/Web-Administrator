#include "maincontroler.h"
#include "serverlistdialog.h"
#include <QInputDialog>
#include <QMessageBox>

MainControler::MainControler(QObject *parent) :
    QObject(parent)
{
    //TODO*** Chargement des option (plus tard)(next version)

    settings = new Settings(this);
    sqlInterface = new SqlInterface(this);
    windows = new MainWindow();
    dock = new NavigationDock(tr("Navigation"), windows);
    editWidget = new EditWidget(windows);
    tools = new Tools(editWidget->getRicheEditor());
    windows->setCentralWidget(editWidget);
    windows->addDockWidget(Qt::LeftDockWidgetArea, dock);
    windows->setMenuBar(tools->getMenuBar());
    windows->addToolBar(tools->getToolBar());

    tools->addMenu(dock->getMenu());

    initSignalSlotConnexion();
}

void MainControler::start()
{
    windows->show();
    tools->majToolsValue();
    tools->switchTools(true);
}

void MainControler::initSignalSlotConnexion()
{
    //Event
    connect(tools->connectAction, SIGNAL(triggered()), this, SLOT(connectDB()));
    connect(tools->refreshAction, SIGNAL(triggered()), this, SLOT(refreshEvent()));
    connect(tools->listServerAction, SIGNAL(triggered()), this, SLOT(openServerList()));
    connect(tools->closeAction, SIGNAL(triggered()), windows, SLOT(close()));
    connect(tools->optionAction, SIGNAL(triggered()), this, SLOT(openOption()));
    connect(tools->helpAction, SIGNAL(triggered()), tools, SLOT(openHelp()));
    connect(tools->aboutAction, SIGNAL(triggered()), tools, SLOT(openAbout()));
    connect(tools->switchRicheAction, SIGNAL(triggered()), editWidget, SLOT(switchEditor()));
    connect(tools->switchHtmlAction, SIGNAL(triggered()), editWidget, SLOT(switchEditor()));
    connect(editWidget, SIGNAL(setStatTools(bool)), tools, SLOT(switchTools(bool)));
    connect(dock, SIGNAL(sendMarginEditWidget(int,int)), editWidget, SLOT(majMargin(int,int)));
    connect(dock, SIGNAL(sendOpeningBlock(Block*)), editWidget, SLOT(setDocument(Block*)));
    connect(dock, SIGNAL(blockHasDelete()), editWidget, SLOT(setDefault()));
    connect(dock, SIGNAL(touchModifDate(unsigned short)), sqlInterface, SLOT(touche(unsigned short)));
    connect(dock, SIGNAL(sendDeleteBlock(unsigned short,unsigned short)), sqlInterface, SLOT(deleteBlock(unsigned short,unsigned short)));
    connect(sqlInterface, SIGNAL(sendNewModifDate(QString)), dock, SIGNAL(sendNewModifDate(QString)));
    connect(sqlInterface, SIGNAL(sendOpenError(QSqlError)), this, SLOT(dbError(QSqlError)));
    connect(sqlInterface, SIGNAL(sendModel(QStandardItemModel*)), dock, SLOT(setModel(QStandardItemModel*)));

    //Editing event
    connect(tools->undoAction, SIGNAL(triggered()), editWidget->richeEditor, SLOT(undo()));
    connect(tools->redoAction, SIGNAL(triggered()), editWidget->richeEditor, SLOT(redo()));
    connect(tools->copyAction, SIGNAL(triggered()), editWidget->richeEditor, SLOT(copy()));
    connect(tools->cutAction, SIGNAL(triggered()), editWidget->richeEditor, SLOT(cut()));
    connect(tools->pasteAction, SIGNAL(triggered()), editWidget->richeEditor, SLOT(paste()));
    connect(tools->boldAction, SIGNAL(triggered()), editWidget->richeEditor, SLOT(bold()));
    connect(tools->italicAction, SIGNAL(triggered()), editWidget->richeEditor, SLOT(italic()));
    connect(tools->underlineAction, SIGNAL(triggered()), editWidget->richeEditor, SLOT(underline()));
    connect(tools->alignLeftAction, SIGNAL(triggered()), editWidget->richeEditor, SLOT(alignLeft()));
    connect(tools->alignRightAction, SIGNAL(triggered()), editWidget->richeEditor, SLOT(alignRight()));
    connect(tools->alignCenterAction, SIGNAL(triggered()), editWidget->richeEditor, SLOT(center()));
    connect(tools->justifyAction, SIGNAL(triggered()), editWidget->richeEditor, SLOT(justify()));
    connect(tools->insertListAction, SIGNAL(triggered()), editWidget->richeEditor, SLOT(insertList()));
    connect(tools->insertTableAction, SIGNAL(triggered()), editWidget->richeEditor, SLOT(insertTable()));
    connect(tools->insertLienAction, SIGNAL(triggered()), editWidget->richeEditor, SLOT(insertLien()));
    connect(tools->insertPictureAction, SIGNAL(triggered()), editWidget->richeEditor, SLOT(insertPicture()));
    connect(tools->insertMovieAction, SIGNAL(triggered()), editWidget->richeEditor, SLOT(insertMovie()));
    connect(tools->fontSizeSpinBox, SIGNAL(valueChanged(int)), editWidget->richeEditor, SLOT(changeFontSize(int)));
    connect(tools->fontColorAction, SIGNAL(triggered()), editWidget->richeEditor, SLOT(executeRightColorAction()));
    connect(tools->backgroundColorAction, SIGNAL(triggered()), editWidget->richeEditor, SLOT(executeRightBackgroundColorAction()));

    //maj tools
    connect(editWidget->richeEditor, SIGNAL(cursorPositionChanged()), tools, SLOT(majToolsValue()));
    connect(editWidget->richeEditor, SIGNAL(selectionChanged()), tools, SLOT(majToolsValue()));
    connect(editWidget->richeEditor, SIGNAL(textChanged()), tools, SLOT(majToolsValue()));
    connect(editWidget->richeEditor, SIGNAL(copyAvailable(bool)), tools->copyAction, SLOT(setEnabled(bool)));
    connect(editWidget->richeEditor, SIGNAL(copyAvailable(bool)), tools->cutAction, SLOT(setEnabled(bool)));
    connect(editWidget, SIGNAL(redoAvailable(bool)), tools->redoAction, SLOT(setEnabled(bool)));
    connect(editWidget, SIGNAL(undoAvailable(bool)), tools->undoAction, SLOT(setEnabled(bool)));
}

void MainControler::openOption()
{
    QStringList items;
    items << tr("rapide") << tr("avec verification");

    bool ok;
    QString fast = QInputDialog::getItem(windows, tr("Option"),
                                         tr("connection type:"), items, 0, false, &ok);
    if (ok && !fast.isEmpty())
    {
        if(fast == "rapide")
            settings->setFastConnexion(true);
        else
            settings->setFastConnexion(false);
    }

}
void MainControler::refreshEvent()
{
    dock->clearTree();
    editWidget->setDefault();
    sqlInterface->download();
}

void MainControler::openServerList()
{
    ServerListDialog* dialog = new ServerListDialog(settings->listServer(), settings->defaultServeur().index, windows);

    connect(dialog, SIGNAL(sendDeleteServer(int)), settings, SLOT(deleteServer(int)));
    connect(dialog, SIGNAL(sendAddServer(ServerInfo)), settings, SLOT(addServer(ServerInfo)));
    connect(dialog, SIGNAL(sendModifiedServer(ServerInfo)), settings, SLOT(modifyServer(ServerInfo)));
    connect(dialog, SIGNAL(setDefautServer(ServerInfo)), settings, SLOT(setDefautServer(ServerInfo)));
    connect(dialog, SIGNAL(sendConnect(ServerInfo)), sqlInterface, SLOT(connectDB(ServerInfo)));

    dialog->exec();

    disconnect(dialog, SIGNAL(sendDeleteServer(int)), settings, SLOT(deleteServer(int)));
    disconnect(dialog, SIGNAL(sendAddServer(ServerInfo)), settings, SLOT(addServer(ServerInfo)));
    disconnect(dialog, SIGNAL(sendModifiedServer(ServerInfo)), settings, SLOT(modifyServer(ServerInfo)));
    disconnect(dialog, SIGNAL(setDefautServer(ServerInfo)), settings, SLOT(setDefautServer(ServerInfo)));
    disconnect(dialog, SIGNAL(sendConnect(ServerInfo)), sqlInterface, SLOT(connectDB(ServerInfo)));
}

void MainControler::connectDB()
{
    if(settings->fastConnexion())
        sqlInterface->connectDB(settings->defaultServeur());
    else
        openServerList();
}

void MainControler::dbError(QSqlError error)
{
    QMessageBox warning;
    warning.setText(tr("Connexion Error"));
    warning.setInformativeText(error.text());
    warning.setStandardButtons(QMessageBox::Ok);
    warning.setIcon(QMessageBox::Critical);
    warning.exec();
}
