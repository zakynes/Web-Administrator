#ifndef NAVIGATIONDOCK_H
#define NAVIGATIONDOCK_H

#include <QDockWidget>
#include <QToolBar>
#include <QTreeView>
#include <QStandardItemModel>
#include <QMenu>
#include "block.h"
#include "action.h"

class NavigationDock : public QDockWidget
{
    Q_OBJECT

private:
    //Tools
    Action* upAction;
    Action* downAction;
    Action* editBlockAction;
    Action* newBlockAction;
    Action* deleteBlockAction;

    //Menu for export
    QMenu* menu;

    //Widgets
    QToolBar* toolBar;
    QTreeView* tree;

public:
    explicit NavigationDock(QString titre, QWidget* parent = 0);
    ~NavigationDock();
    QMenu* getMenu();

private:
    void initAction();
    void initToolBar();
    void initTree();
    void initMenu();
    void initSignalSlotsConnexion();
    void setDockedStyleSheet(bool const& left = true);
    void setFloatingStyleSheet();
    void moveBlock(bool const& up = true);

public slots:
    void setModel(QStandardItemModel* model);
    void locationHasChanged(Qt::DockWidgetArea area);
    void topLevelHasChanged(bool topLevel);
    void majTools(QModelIndex index);
    void openBlock(QModelIndex index);
    void moveUpBlock();
    void moveDownBlock();
    void openEditWindows();
    void newBlock();
    void deleteBlock();
    void clearTree();
    void disableTools();

signals:
    void sendOpeningBlock(Block* block);
    void sendMarginEditWidget(int left, int right);
    void touchModifDate(const unsigned short &index);
    void sendDeleteBlock(const unsigned short &PageIndex, const unsigned short &index);
    void blockHasDelete();
    void sendNewModifDate(QString date);
};

#endif // NAVIGATIONDOCK_H
