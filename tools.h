#ifndef TOOLS_H
#define TOOLS_H

#include <QToolBar>
#include <QSpinBox>
#include <QObject>
#include <QMenuBar>
#include <QMenu>

#include "action.h"
#include "textedit.h"

class Tools : public QObject
{
    Q_OBJECT

private:
    //Text edition
    Action* cutAction;
    Action* pasteAction;
    Action* copyAction;
    Action* boldAction;
    Action* italicAction;
    Action* underlineAction;
    Action* alignLeftAction;
    Action* alignRightAction;
    Action* alignCenterAction;
    Action* justifyAction;
    Action* fontColorAction;
    Action* backgroundColorAction;
    Action* fontSizeAction;
    Action* insertListAction;
    Action* insertTableAction;
    Action* insertLienAction;
    Action* insertPictureAction;
    Action* insertMovieAction;
    Action* undoAction;
    Action* redoAction;
    //Switch edition mode
    Action* switchRicheAction;
    Action* switchHtmlAction;
    //Other action
    Action* connectAction;
    Action* refreshAction;
    Action* saveAction;
    Action* helpAction;
    Action* closeAction;
    Action* listServerAction;
    Action* aboutAction;
    Action* optionAction;

    //Widgets
    QMenuBar* menuBar;
    QToolBar* toolBar;
    QSpinBox *fontSizeSpinBox;

    //Menu
    QMenu* fileMenu;
    QMenu* EditMenu;
    QMenu* HelpMenu;
    QAction* separatorBeforInsert;

    TextEdit* editor;

public:
    Tools(TextEdit* editor);
    ~Tools();

    QMenuBar* getMenuBar();
    QToolBar* getToolBar();
    void addMenu(QMenu *menu);

private:
    void initActions();
    void initShortcut();
    void initToolBar();
    void initMenuBar();

public slots:
    void switchTools(bool richeMode);
    void majToolsValue();
    void openAbout();
    void openHelp();

    friend class MainControler;

};

#endif // TOOLS_H
