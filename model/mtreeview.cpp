#include "mtreeview.h"

mTreeView::mTreeView()
{

}

void mTreeView::add_firstItem(QStandardItemModel *tree, QTreeView *treeView, QString name){
    QStandardItem *item;

    item = new QStandardItem(name);
    tree->appendRow(item);

    treeView->setModel(tree);
}

void mTreeView::appendItem(QStandardItemModel *tree, QTreeView *treeView, QString name, int row, int col){
    QStandardItem *sd;
    QStandardItem *item;

    item = new QStandardItem(name);

//    sd = tree->itemFromIndex(treeView->indexAt(QPoint(0,0)));
    sd = tree->item(1);
    sd->appendRow(item);

    treeView->setModel(tree);
}
