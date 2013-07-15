#include "app.h"
#include <QStyleFactory>

App::App(int argc, char *argv[]):
    QApplication(argc, argv)
{
    setStyle(QStyleFactory::create("Fusion"));
}

void App::connectFocusEvent(MainWindow *windows)
{
    connect(this, SIGNAL(focusObjectChanged(QObject*)), windows, SLOT(focusWidgetChanged(QObject*)));
}

void App::connectRestartEvent()
{
}
