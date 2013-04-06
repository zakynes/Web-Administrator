#ifndef SITEVIEW_H
#define SITEVIEW_H

#include <QTreeView>
#include <QModelIndexList>

namespace WA_UI {
class SiteView;
}

class SiteView : public QTreeView
{
    Q_OBJECT

public:
    explicit SiteView(QWidget* parent = 0);

protected:
    //Tree
    QModelIndexList tree;
    //For upload
    QModelIndexList upload;
};

#endif // SITEVIEW_H
