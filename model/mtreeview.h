#ifndef MTREEVIEW_H
#define MTREEVIEW_H

#include "util/global.h"

class mTreeView
{
public:
    mTreeView();

    void add_firstItem(QStandardItemModel *tree, QTreeView *treeView, QString name);
    void appendItem(QStandardItemModel *tree, QTreeView *treeView, QString name, int row, int col = 0);
    QModelIndex getTreeID(QTreeView *treeView);
};

#endif // MTREEVIEW_H
