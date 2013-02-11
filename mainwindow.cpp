#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeySequence>
#include <QDockWidget>
#include <QLabel>
#include <QTextDocumentFragment>

#include <QMessageBox>

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

    majToolsValue();
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

    aSwitchRiche = new QAction(*iSwitchRiche, tr("Mode riche"), this);
    aSwitchHtml = new QAction(*iSwitchHtml, tr("Mode HTML"), this);
    aSwitchRiche->setEnabled(false);

    aListe = new QAction(*iListe, tr("Liste"), this);
    aTableau = new QAction(*iTableau, tr("Tableau"), this);

    aCouleur = new QAction(*iCouleur, tr("Couleur du text"), this);
    aCouleurFond = new QAction(*iCouleurFond, tr("Couleur de fond"), this);
    aTaille = new QAction(tr("Taille de police"), this);
    fontSize = new QSpinBox();

    aLien = new QAction(*iLien, tr("Lien"), this);
    aImage = new QAction(*iImage, tr("Image"), this);
    aVideo = new QAction(*iVideo, tr("Video"), this);

    aUndo = new QAction(*iUndo, tr("Annuler"), this);
    aRedo = new QAction(*iRedo, tr("Refaire"), this);

    aHelp = new QAction(*iHelp, tr("Aide"), this);

    aClose = new QAction(tr("Fermer"), this);
    aListServer = new QAction(*iListServer, tr("Liste de serveurs"), this);
    aAbout = new QAction(tr("A propos"), this);
    aOption = new QAction(*iOption, tr("Options"), this);

    initShortcut();

    //Event
    connect(aClose, SIGNAL(triggered()), this, SLOT(close()));
    connect(aHelp, SIGNAL(triggered()), this, SLOT(openHelp()));
    connect(aAbout, SIGNAL(triggered()), this, SLOT(openAbout()));
    connect(aSwitchRiche, SIGNAL(triggered()), this, SLOT(switchTextEdit()));
    connect(aSwitchHtml, SIGNAL(triggered()), this, SLOT(switchTextEdit()));

    //Editing event
    connect(aUndo, SIGNAL(triggered()), textEdit, SLOT(undo()));
    connect(aRedo, SIGNAL(triggered()), textEdit, SLOT(redo()));
    connect(aCopier, SIGNAL(triggered()), textEdit, SLOT(copy()));
    connect(aCouper, SIGNAL(triggered()), textEdit, SLOT(cut()));
    connect(aColler, SIGNAL(triggered()), textEdit, SLOT(paste()));
    connect(aGras, SIGNAL(triggered()), textEdit, SLOT(bold()));
    connect(aItalique, SIGNAL(triggered()), textEdit, SLOT(italic()));
    connect(aSouligner, SIGNAL(triggered()), textEdit, SLOT(underligne()));
    connect(aAligneLeft, SIGNAL(triggered()), textEdit, SLOT(alignLeft()));
    connect(aAligneRight, SIGNAL(triggered()), textEdit, SLOT(alignRight()));
    connect(aAligneCenter, SIGNAL(triggered()), textEdit, SLOT(center()));
    connect(aJustify, SIGNAL(triggered()), textEdit, SLOT(justify()));
    connect(aListe, SIGNAL(triggered()), textEdit, SLOT(insertList()));
    connect(aTableau, SIGNAL(triggered()), textEdit, SLOT(insertTable()));
    connect(aLien, SIGNAL(triggered()), textEdit, SLOT(insertLien()));
    connect(aImage, SIGNAL(triggered()), textEdit, SLOT(insertPicture()));
    connect(aVideo, SIGNAL(triggered()), textEdit, SLOT(insertMovie()));
    connect(fontSize, SIGNAL(valueChanged(int)), textEdit, SLOT(changeFontSize(int)));
    connect(aCouleur, SIGNAL(triggered()), textEdit, SLOT(changeTextColor()));
    connect(aCouleurFond, SIGNAL(triggered()), textEdit, SLOT(changeBackgroundColor()));

    //For test
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

    iSwitchRiche = new QIcon("ressources/images/page.png");
    iSwitchHtml = new QIcon("ressources/images/html.png");

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

    iListServer = new QIcon("ressources/images/listeServer.png");
    iOption = new QIcon("ressources/images/options.png");
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
    mEdition->addAction(aSwitchRiche);
    mEdition->addAction(aSwitchHtml);
    mEdition->addSeparator();
    mEdition->addAction(aListe);
    mEdition->addAction(aTableau);
    mEdition->addSeparator();
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
    toolBar->addAction(aSwitchRiche);
    toolBar->addAction(aSwitchHtml);
    toolBar->addSeparator();
    toolBar->addAction(aListe);
    toolBar->addAction(aTableau);
    toolBar->addSeparator();
    //toolBar->addAction(aTaille);
    toolBar->addWidget(fontSize);
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
    //Define riche text editing default
    richText = true;

    //Set the layout
    editWidget = new QStackedWidget();

    //Rich text
    textEdit = new TextEdit();
    textEdit->setContentsMargins(20, 20, 20, 20);
    textEdit->insertHtml("<h1>titre test</h1><p>text <strong>test</strong><br />test pour le bold<p/>");
    editWidget->addWidget(textEdit);
    //maj tools
    connect(textEdit, SIGNAL(cursorPositionChanged()), this, SLOT(majToolsValue()));
    connect(textEdit, SIGNAL(selectionChanged()), this, SLOT(majToolsValue()));
    connect(textEdit, SIGNAL(textChanged()), this, SLOT(majToolsValue()));

    //Plain text
    plainTextEdit = new QTextEdit();
    highlighter = new Highlighter(plainTextEdit->document());
    editWidget->addWidget(plainTextEdit);

    editWidget->setCurrentIndex(0);
    this->setCentralWidget(editWidget);
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

void MainWindow::switchTextEdit()
{
    if(richText)
    {
        //switch to plain text to edit html
        plainTextEdit->setPlainText(textEdit->toHtml());
        editWidget->setCurrentIndex(1);
        richText = false;
    }
    else
    {
        //switch to rich text
        textEdit->setHtml(plainTextEdit->toPlainText());
        editWidget->setCurrentIndex(0);
        richText = true;
    }

    //switch tools
    aGras->setEnabled(richText);
    aItalique->setEnabled(richText);
    aSouligner->setEnabled(richText);
    aAligneLeft->setEnabled(richText);
    aAligneRight->setEnabled(richText);
    aAligneCenter->setEnabled(richText);
    aJustify->setEnabled(richText);
    aSwitchRiche->setEnabled(!richText);
    aSwitchHtml->setEnabled(richText);
    aListe->setEnabled(richText);
    aTableau->setEnabled(richText);
    fontSize->setEnabled(richText);
    aCouleur->setEnabled(richText);
    aCouleurFond->setEnabled(richText);
    aLien->setEnabled(richText);
    aImage->setEnabled(richText);
    aVideo->setEnabled(richText);
}
void MainWindow::selectColor()
{

}

void MainWindow::selectBackgroundColor()
{

}

void MainWindow::majToolsValue()
{
    //Font size
    fontSize->setValue(textEdit->textCursor().charFormat().font().pointSize());

    //Bold
    aGras->setCheckable(true);
    if(textEdit->fontWeight() == QFont::Bold)
        aGras->setChecked(true);
    else
        aGras->setChecked(false);

    //Italic
    aItalique->setCheckable(true);
    if(textEdit->fontItalic())
        aItalique->setChecked(true);
    else
        aItalique->setChecked(false);

    //Underline
    aSouligner->setCheckable(true);
    if(textEdit->fontUnderline())
        aSouligner->setChecked(true);
    else
        aSouligner->setChecked(false);

    //Alignment
    aAligneLeft->setEnabled(true);
    aAligneRight->setEnabled(true);
    aAligneCenter->setEnabled(true);
    aJustify->setEnabled(true);
    switch(textEdit->alignment())
    {
    case Qt::AlignLeft:
            aAligneLeft->setEnabled(false);
            break;
    case Qt::AlignRight:
            aAligneRight->setEnabled(false);
            break;
    case Qt::AlignCenter:
            aAligneCenter->setEnabled(false);
            break;
    case Qt::AlignJustify:
            aJustify->setEnabled(false);
            break;
    default:
        break;
    }
}

void MainWindow::openAbout()
{
    QMessageBox message;

    message.setText(tr("<strong>A propos!</strong>"));
    message.setInformativeText(tr("Version : 1.0.1 \n Auteur : Zakynes"));
    message.setStandardButtons(QMessageBox::Ok);
    message.setDefaultButton(QMessageBox::Ok);

    message.exec();
}

void MainWindow::openHelp()
{
    QMessageBox message;

    message.setText(tr("<strong>Aide</strong>"));
    message.setInformativeText(tr("Il n'y a pas de document d'aide encore disponible"));
    message.setStandardButtons(QMessageBox::Ok);
    message.setDefaultButton(QMessageBox::Ok);

    message.exec();
}
