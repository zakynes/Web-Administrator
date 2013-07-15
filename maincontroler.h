#ifndef MAINCONTROLER_H
#define MAINCONTROLER_H

#include <QObject>
#include <QSqlError>

#include "sqlinterface.h"
#include "editwidget.h"
#include "navigationdock.h"
#include "tools.h"
#include "mainwindow.h"
#include "settings.h"

class MainControler : public QObject
{
    Q_OBJECT

private:
    SqlInterface* sqlInterface;
    EditWidget* editWidget;
    NavigationDock* dock;
    Tools* tools;
    MainWindow* windows;
    Settings* settings;

public:
    explicit MainControler(QObject *parent = 0);
    void start();

private:
    void initSignalSlotConnexion();
    
signals:
    void restart();
    
public slots:
    void openOption();
    void refreshEvent();
    void openServerList();
    void connectDB();
    void dbError(QSqlError error);
    
};

#endif // MAINCONTROLER_H
