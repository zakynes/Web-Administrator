#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QMenuBar>
#include <QTextEdit>
#include <QTreeView>
#include <QIcon>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    // --- Functions
    void initAction();
    void initIcon();
    void initShortcut();
    void initMenu();
    void initToolbar();
    void initWindows();
    void initTextEdit();
    void initTree();

    // --- Attributs
    Ui::MainWindow *ui;
    QMenuBar* menuBar;
    QToolBar* toolBar;
    QTextEdit* textEdit;
    QTreeView* tree;
    QDockWidget* dock;

    //Actions
    QAction* aCouper;
    QAction* aColler;
    QAction* aCopier;

    QAction* aConnexion;
    QAction* aNouveau;
    QAction* aSauver;

    QAction* aGras;
    QAction* aItalique;
    QAction* aSouligner;

    QAction* aAligneLeft;
    QAction* aAligneRight;
    QAction* aAligneCenter;
    QAction* aJustify;

    QAction* aListe;
    QAction* aTableau;

    QAction* aCouleur;
    QAction* aCouleurFond;
    QAction* aTaille;

    QAction* aLien;
    QAction* aImage;
    QAction* aVideo;

    QAction* aUndo;
    QAction* aRedo;

    QAction* aHelp;

    //Action menu
    QAction* aClose;
    QAction* aListServer;
    QAction* aAbout;
    QAction* aOption;

    //Icones
    QIcon* iCouper;
    QIcon* iColler;
    QIcon* iCopier;

    QIcon* iConnexion;
    QIcon* iNouveau;
    QIcon* iSauver;

    QIcon* iGras;
    QIcon* iItalique;
    QIcon* iSouligner;

    QIcon* iAligneLeft;
    QIcon* iAligneRight;
    QIcon* iAligneCenter;
    QIcon* iJustify;

    QIcon* iListe;
    QIcon* iTableau;

    QIcon* iCouleur;
    QIcon* iCouleurFond;

    QIcon* iLien;
    QIcon* iImage;
    QIcon* iVideo;

    QIcon* iUndo;
    QIcon* iRedo;

    QIcon* iHelp;

    //Menu
    QMenu* mFichier;
    QMenu* mEdition;
    QMenu* mAide;
};

#endif // MAINWINDOW_H
