#include "mainwindow.h"
#include <QKeySequence>
#include <QDockWidget>
#include <QLabel>
#include <QTextDocumentFragment>
#include <QWindow>
#include <QMessageBox>
#include <QVBoxLayout>

#include <QStandardItem>
#include <QStandardItemModel>

#include "block.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    initWindows();

    statusBar = new QStatusBar(this);
    this->setStatusBar(statusBar);
}

void MainWindow::initWindows()
{
    this->resize(1200, 600);
    this->setWindowIcon(QIcon("ressources/images/icone128.png"));
    this->setWindowTitle("Web Administrator");
    this->setIconSize(QSize(32, 32));
}

MainWindow::~MainWindow()
{
}
