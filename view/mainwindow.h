#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

#include "util/global.h"
#include "model/mtreeview.h"
#include "model/mdi.h"
#include "control/work.h"

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
    void pageFinished();
    void TimeOut();
    void on_actionRefresh_triggered();
    void on_pb_Refresh_Data_clicked();

private:
    Ui::MainWindow *ui;

    QStandardItemModel *modelTree;
    QStandardItemModel *tableModel;
    mTreeView mTree;
    mdi mDi;
    work w;

    QNetworkAccessManager *manager;
    QNetworkReply *r; bool t_out;
//    int jml_module; QString api_key;
//    struct module module_rtu[MAX_RTU];
    QTimer *tmr;
    QLabel *lbl_GIF;
    QLabel *lbl_loading;
    QMovie *loading;

    struct tree t;
    int module_id;

//    void getENV();
//    void getDATA();
    void refreshTree();
//    void getTreeID();

    void setMap();
    void setLatLng();

    void setPage();
    void setENV();
    void setGSM1(int index, bool act);
    void setGSM2(int index, bool act);
    void setDATA();
};

#endif // MAINWINDOW_H
