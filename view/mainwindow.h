#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "util/global.h"
#include "model/mtreeview.h"
#include "model/mdi.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, QString key = 0);
    ~MainWindow();

private slots:
    void replyFinished(QNetworkReply *reply);
    void on_treeView_doubleClicked(const QModelIndex &index);
    void on_actionRefresh_triggered();

private:
    Ui::MainWindow *ui;

    QStandardItemModel *modelTree;
    mTreeView mTree;
    mdi mDi;

    QNetworkAccessManager *manager;
    int jml_module; QString api_key;
    struct module module_rtu[MAX_RTU];

    void getENV();
    void getDATA();
    void refreshTree();
    void refreshData();
};

#endif // MAINWINDOW_H
