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
    sd = tree->item(row, col);
    sd->appendRow(item);

    treeView->setModel(tree);
}

QModelIndex mTreeView::getTreeID(QTreeView *treeView)
{
//    QAbstractItemModel *am = treeView->model();
    QModelIndexList modelindex = treeView->selectionModel()->selectedIndexes();
    QList<QModelIndex> index(modelindex);

//    if (index.at(0).data(Qt::DisplayRole).toString() == "Maps") {
//        t.maps = index.at(0);
//    } else {
//        if (index.at(0).parent().data(Qt::DisplayRole).toString() == "Module") {
//            t.module[t.jml_module].treeModule = index.at(0);
//            t.module[t.jml_module].id = module_rtu[tree.jml_module].id;
//        }
//    }

//    for(int i = 0; i < index.size(); i++) {
//        QModelIndex mi=index.at(i);
//        QVariant data=am->data(mi,0);

//        QString s = data.toString();
//        QByteArray bytArr = s.toLatin1();
//        char *pr = bytArr.data();

//        QModelIndex mi2= index.at(i).parent();
//        QVariant data2=am->data(mi2,0);
//        QString s2 = data2.toString();
//        QByteArray bytArr2 = s2.toLatin1();
//        char *pr2 = bytArr2.data();

//        qDebug() << "child:::" << pr << "---parent:::" << pr2 << endl;
//    }

    return index.at(0);
}
