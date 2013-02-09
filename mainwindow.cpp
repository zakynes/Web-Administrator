#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initAction()
{
    aCouper = new QAction();
    aColler = new QAction();
    aCopier = new QAction();

    aConnexion = new QAction();
    aNouveau = new QAction();
    aSauver = new QAction();

    aGras = new QAction();
    aItalique = new QAction();
    aSouligner = new QAction();

    aAligneLeft = new QAction();
    aAligneRight = new QAction();
    aAlgneCenter = new QAction();
    aJustify = new QAction();

    aListe = new QAction();
    aTableau = new QAction();

    aCouleur = new QAction();
    aCouleurFond = new QAction();
    aTaille = new QAction();

    aLien = new QAction();
    aImage = new QAction();
    aVideo = new QAction();

    aHelp = new QAction();
}

void MainWindow::initIcon()
{
    iCouper = new QIcon("ressources/images/couper.png");
    iColler = new QIcon("ressources/images/coller.png");
    iCopier = new QIcon("ressources/images/copier.png");

    iConnexion = new QIcon("ressources/images/reseau.png");
    iNouveau = new QIcon("ressources/images/nouveau.png");
    isauver = new QIcon("ressources/images/nouveau.png");

    iGras = new QIcon("ressources/images/gras.png");
    iItalique = new QIcon("ressources/images/italique.png");
    iSouligner = new QIcon("ressources/images/souligner.png");

    iAligneLeft = new QIcon("ressources/images/alignerGauche.png");
    iAligneRight = new QIcon("ressources/images/alignerDroite.png");
    iAlgneCenter = new QIcon("ressources/images/centrer.png");
    iJustify = new QIcon("ressources/images/justifier.png");

    iListe = new QIcon("ressources/images/liste.png");
    iTableau = new QIcon("ressources/images/tableau.png");

    iCouleur = new QIcon("ressources/images/couleurText.png");
    iCouleurFond = new QIcon("ressources/images/couleurFond");

    iLien = new QIcon("ressources/images/lien.png");
    iImage = new QIcon("ressources/images/image.png");
    iVideo = new QIcon("ressources/images/video.png");

    iHelp = new QIcon("ressources/images/aide.png");
}

void MainWindow::initMenu()
{

    //test
}

void MainWindow::initToolbar()
{

}

void MainWindow::initWindows()
{

}

void MainWindow::initTextEdit()
{

}

void MainWindow::initTree()
{

}
