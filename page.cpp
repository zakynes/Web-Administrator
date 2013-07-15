#include "page.h"
#include <QModelIndex>

Page::Page(QString const& name):
    QStandardItem(name)
{
    setAccessibleText(name);
    setEditable(false);
    multiblock = false;
    ordonable = false;
    addBlock = false;
    dateOrder = false;
}

//Getters
QString Page::getPageName(){
    return accessibleText();
}

bool Page::isMultiblock(){
    return multiblock;
}

bool Page::isOrdonable(){
    return ordonable;
}

bool Page::canAddBlock(){
    return addBlock;
}

bool Page::isDateOrder(){
    return dateOrder;
}

void Page::setMultiblock(bool const& flag){
    multiblock = flag;
}

void Page::setOrdonable(bool const& flag){
    ordonable = flag;
}

void Page::setAddBlock(bool const& flag){
    addBlock = flag;
}

void Page::setOrderByDate(bool const& flag){
    dateOrder = flag;
    if(flag)
        ordonable = false;
}

Block* Page::getBlockAt(unsigned short int const& index){
    return (Block*)child(index);
}

int Page::getIndexRow(){
    QModelIndex index = this->index();
    return index.row();
}

void Page::buildToolTip()
{
    QString description = "Parametres :";

    if(isMultiblock())
        description.append("\n  -Mutiblock");
    if(isOrdonable())
        description.append("\n  -Ordonable");
    if(isDateOrder())
        description.append("\n  -Tri par date");
    if(isMultiblock())
        description.append("\n  -Ajout de block");

    setToolTip(description);

}
