#ifndef APP_H
#define APP_H

#include <QApplication>
#include "mainwindow.h"

class App : public QApplication
{
public:
    App(int argc, char *argv[]);
    void connectFocusEvent(MainWindow* windows);
    void connectRestartEvent();
};

#endif // APP_H
