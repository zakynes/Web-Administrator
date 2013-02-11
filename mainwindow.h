#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QMenuBar>
#include <QTreeView>
#include <QIcon>
#include <QStackedWidget>
#include <QSpinBox>

#include "textedit.h"
#include "highlighter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void switchTextEdit();
    void selectColor();
    void selectBackgroundColor();
    void majToolsValue();
    void openAbout();
    void openHelp();
    
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
    TextEdit* textEdit;
    QTextEdit* plainTextEdit;
    QTreeView* tree;
    QDockWidget* dock;
    bool richText;
    QStackedWidget* editWidget;
    Highlighter *highlighter;
    QSpinBox *fontSize;

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

    QAction* aSwitchRiche;
    QAction* aSwitchHtml;

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

    QIcon* iSwitchRiche;
    QIcon* iSwitchHtml;

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

    QIcon* iListServer;
    QIcon* iOption;

    //Menu
    QMenu* mFichier;
    QMenu* mEdition;
    QMenu* mAide;
};

#endif // MAINWINDOW_H
