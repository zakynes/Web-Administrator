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
#include <QLabel>
#include <QTreeWidget>
#include <QStatusBar>

#include "sqlinterface.h"
#include "textedit.h"
#include "highlighter.h"
#include "action.h"
#include "navigationdock.h"

namespace WA_UI {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void initWindows();

    QStatusBar* statusBar;
};

#endif // MAINWINDOW_H
