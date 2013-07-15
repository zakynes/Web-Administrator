#ifndef ACTION_H
#define ACTION_H

#include <QAction>
#include <QObject>

class Action : public QAction
{
public:
    explicit Action(QString const& iconName, QString const& actionName, QObject* parent = 0);
};

#endif // ACTION_H
