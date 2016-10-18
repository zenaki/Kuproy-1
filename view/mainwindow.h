#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

#include "util/global.h"
#include "model/mtreeview.h"
#include "model/mweb.h"
#include "model/qcustomplot.h"
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
    void MapPageFinished();
    void GraphPageFinished();
    void TimeOut();
    void on_actionRefresh_triggered();
    void on_pb_Refresh_Data_clicked();

    void on_pb_hs_treeView_clicked();
    void on_pb_hs_toolBox_clicked();
    void on_pb_hs_log_clicked();

    void grafik_setGraph();

private:
    Ui::MainWindow *ui;

    QStandardItemModel *modelTree;
    QStandardItemModel *tableModel;
    mTreeView mTree;
    mWeb mWb;
    work w;

    QNetworkAccessManager *manager;
    QTimer *tmr;
    QLabel *lbl_GIF;
    QLabel *lbl_loading;
    QMovie *loading;

    struct tree t;
    int module_id;

    void refreshTree();
    void setMap();
    void setLatLng();

    void setPage();
    void setENV();
    void setGSM1(int index, bool act);
    void setGSM2(int index, bool act);
    void setDATA();

    void setIcon();
};

#endif // MAINWINDOW_H
