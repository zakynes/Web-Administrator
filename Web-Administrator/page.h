#ifndef PAGE_H
#define PAGE_H

#include <QObject>
#include <QVector>
#include <QStandardItem>

#include "block.h"

namespace WA_DATA {
class Page;
}

class Page : public QStandardItem
{
public:
    explicit Page(QString const& name);

    //Getters
    QString getPageName();
    bool isMultiblock();
    bool isOrdonable();
    bool canAddBlock();
    bool isDateOrder();
    Block *getBlockAt(const unsigned short &index);
    int getIndexRow();
    void setMultiblock(bool const& flag);
    void setOrdonable(bool const& flag);
    void setAddBlock(bool const& flag);
    void setOrderByDate(bool const& flag);
    void buildToolTip();

protected:
    bool ordonable;
    bool multiblock;
    bool addBlock;
    bool dateOrder;
};

#endif // PAGE_H
