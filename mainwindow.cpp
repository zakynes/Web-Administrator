#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeySequence>
#include <QDockWidget>
#include <QLabel>
#include <QLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initWindows();
    initTextEdit();
    initTree();

    initAction();
    initToolbar();
    initMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initAction()
{
    initIcon();

    aCouper = new QAction(*iCouper, tr("Couper"), this);
    aColler = new QAction(*iColler, tr("Coller"), this);
    aCopier = new QAction(*iCopier, tr("Copier"), this);

    aConnexion = new QAction(*iConnexion, tr("Connexion"), this);
    aNouveau = new QAction(*iNouveau, tr("Nouveau"), this);
    aSauver = new QAction(*iSauver, tr("Sauvegarder"), this);

    aGras = new QAction(*iGras, tr("Gras"), this);
    aItalique = new QAction(*iItalique, tr("Italique"), this);
    aSouligner = new QAction(*iSouligner, tr("Souligner"), this);

    aAligneLeft = new QAction(*iAligneLeft, tr("Gauche"), this);
    aAligneRight = new QAction(*iAligneRight, tr("Droite"), this);
    aAligneCenter = new QAction(*iAligneCenter, tr("Centrer"), this);
    aJustify = new QAction(*iJustify, tr("Justifier"), this);

    aListe = new QAction(*iListe, tr("Liste"), this);
    aTableau = new QAction(*iTableau, tr("Tableau"), this);

    aCouleur = new QAction(*iCouleur, tr("Couleur du text"), this);
    aCouleurFond = new QAction(*iCouleurFond, tr("Couleur de fond"), this);
    aTaille = new QAction(tr("Taille de police"), this);

    aLien = new QAction(*iLien, tr("Lien"), this);
    aImage = new QAction(*iImage, tr("Image"), this);
    aVideo = new QAction(*iVideo, tr("Video"), this);

    aUndo = new QAction(*iUndo, tr("Annuler"), this);
    aRedo = new QAction(*iRedo, tr("Refaire"), this);

    aHelp = new QAction(*iHelp, tr("Aide"), this);

    aClose = new QAction(tr("Fermer"), this);
    aListServer = new QAction(tr("Liste de serveurs"), this);
    aAbout = new QAction(tr("A propos"), this);
    aOption = new QAction(tr("Options"), this);

    initShortcut();

    //Event
    connect(aClose, SIGNAL(triggered()), this, SLOT(close()));
}

void MainWindow::initIcon()
{
    iCouper = new QIcon("ressources/images/couper.png");
    iColler = new QIcon("ressources/images/coller.png");
    iCopier = new QIcon("ressources/images/copier.png");

    iConnexion = new QIcon("ressources/images/reseau.png");
    iNouveau = new QIcon("ressources/images/nouveau.png");
    iSauver = new QIcon("ressources/images/sauver.png");

    iGras = new QIcon("ressources/images/gras.png");
    iItalique = new QIcon("ressources/images/italique.png");
    iSouligner = new QIcon("ressources/images/souligner.png");

    iAligneLeft = new QIcon("ressources/images/alignerGauche.png");
    iAligneRight = new QIcon("ressources/images/alignerDroite.png");
    iAligneCenter = new QIcon("ressources/images/centrer.png");
    iJustify = new QIcon("ressources/images/justifier.png");

    iListe = new QIcon("ressources/images/liste.png");
    iTableau = new QIcon("ressources/images/tableau.png");

    iCouleur = new QIcon("ressources/images/couleurText.png");
    iCouleurFond = new QIcon("ressources/images/couleurFond");

    iLien = new QIcon("ressources/images/lien.png");
    iImage = new QIcon("ressources/images/image.png");
    iVideo = new QIcon("ressources/images/video.png");

    iUndo = new QIcon("ressources/images/retour.png");
    iRedo = new QIcon("ressources/images/refaire.png");

    iHelp = new QIcon("ressources/images/aide.png");
}

void MainWindow::initShortcut()
{
    aCouper->setShortcut(QKeySequence(QKeySequence::Cut));
    aColler->setShortcut(QKeySequence(QKeySequence::Paste));
    aCopier->setShortcut(QKeySequence(QKeySequence::Copy));

    aConnexion->setShortcut(QKeySequence(QKeySequence::Open));
    aNouveau->setShortcut(QKeySequence(QKeySequence::New));
    aSauver->setShortcut(QKeySequence(QKeySequence::Save));

    aGras->setShortcut(QKeySequence(QKeySequence::Bold));
    aItalique->setShortcut(QKeySequence(QKeySequence::Italic));
    aSouligner->setShortcut(QKeySequence(QKeySequence::Underline));

    aUndo->setShortcut(QKeySequence(QKeySequence::Undo));
    aRedo->setShortcut(QKeySequence(QKeySequence::Redo));

    aOption->setShortcut(QKeySequence(QKeySequence::Preferences));
}

void MainWindow::initMenu()
{
    menuBar = new QMenuBar();
    mFichier = new QMenu(tr("Fichier"));
    mEdition = new QMenu(tr("Edition"));
    mAide = new QMenu(tr("Aide"));

    //Fichier
    mFichier->addAction(aConnexion);
    mFichier->addSeparator();
    mFichier->addAction(aNouveau);
    mFichier->addAction(aSauver);
    mFichier->addSeparator();
    mFichier->addAction(aClose);
    menuBar->addMenu(mFichier);

    //Edition
    mEdition->addAction(aUndo);
    mEdition->addAction(aRedo);
    mEdition->addSeparator();
    mEdition->addAction(aCopier);
    mEdition->addAction(aCouper);
    mEdition->addAction(aColler);
    mEdition->addSeparator();
    mEdition->addAction(aGras);
    mEdition->addAction(aItalique);
    mEdition->addAction(aSouligner);
    mEdition->addSeparator();
    mEdition->addAction(aAligneLeft);
    mEdition->addAction(aAligneRight);
    mEdition->addAction(aAligneCenter);
    mEdition->addAction(aJustify);
    mEdition->addSeparator();
    mEdition->addAction(aListe);
    mEdition->addAction(aTableau);
    mEdition->addSeparator();
    mEdition->addAction(aTaille);
    mEdition->addAction(aCouleur);
    mEdition->addAction(aCouleurFond);
    mEdition->addSeparator();
    mEdition->addAction(aLien);
    mEdition->addAction(aImage);
    mEdition->addAction(aVideo);
    menuBar->addMenu(mEdition);

    //Aide
    mAide->addAction(aOption);
    mAide->addAction(aListServer);
    mAide->addSeparator();
    mAide->addAction(aAbout);
    mAide->addAction(aHelp);
    menuBar->addMenu(mAide);

    this->setMenuBar(menuBar);
}

void MainWindow::initToolbar()
{
    toolBar = new QToolBar();

    //Fichier
    toolBar->addAction(aConnexion);
    toolBar->addSeparator();
    toolBar->addAction(aNouveau);
    toolBar->addAction(aSauver);
    toolBar->addSeparator();

    //Edition
    toolBar->addAction(aUndo);
    toolBar->addAction(aRedo);
    toolBar->addSeparator();
    toolBar->addAction(aCopier);
    toolBar->addAction(aCouper);
    toolBar->addAction(aColler);
    toolBar->addSeparator();
    toolBar->addAction(aGras);
    toolBar->addAction(aItalique);
    toolBar->addAction(aSouligner);
    toolBar->addSeparator();
    toolBar->addAction(aAligneLeft);
    toolBar->addAction(aAligneRight);
    toolBar->addAction(aAligneCenter);
    toolBar->addAction(aJustify);
    toolBar->addSeparator();
    toolBar->addAction(aListe);
    toolBar->addAction(aTableau);
    toolBar->addSeparator();
    toolBar->addAction(aTaille);
    toolBar->addAction(aCouleur);
    toolBar->addAction(aCouleurFond);
    toolBar->addSeparator();
    toolBar->addAction(aLien);
    toolBar->addAction(aImage);
    toolBar->addAction(aVideo);
    toolBar->addSeparator();

    //Option
    toolBar->addAction(aOption);
    toolBar->addAction(aListServer);

    this->addToolBar(toolBar);
}

void MainWindow::initWindows()
{
    this->resize(1200, 600);
    this->setWindowIcon(QIcon("ressources/images/icone128.png"));
    this->setWindowTitle("Web Administrator");
    this->setIconSize(QSize(32, 32));
}

void MainWindow::initTextEdit()
{
    textEdit = new QTextEdit();
    textEdit->setContentsMargins(20, 20, 20, 20);
    this->setCentralWidget(textEdit);
}

void MainWindow::initTree()
{
    this->setDockOptions(QMainWindow::VerticalTabs);
    dock = new QDockWidget();
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock->setTitleBarWidget(new QLabel(tr("Navigateur")));
    tree = new QTreeView();
    tree->setMaximumWidth(400);
    tree->setMinimumWidth(10);
    dock->setWidget(tree);
    this->addDockWidget(Qt::LeftDockWidgetArea, dock);
}
