#include "action.h"
#include <QIcon>

Action::Action(const QString &iconName, const QString &actionName, QObject* parent):
    QAction(parent)
{
    if(!iconName.isEmpty())
    {
        QIcon icon("ressources/images/" + iconName + ".png");
        this->setIcon(icon);
    }

    this->setText(actionName);
}
