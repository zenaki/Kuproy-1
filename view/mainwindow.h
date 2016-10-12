#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

#include "util/global.h"
#include "model/mtreeview.h"
#include "model/mdi.h"
#include "model/mgraph.h"
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
    void pageFinished();
    void TimeOut();
    void on_actionRefresh_triggered();
    void on_pb_Refresh_Data_clicked();

    void on_pb_hs_treeView_clicked();
    void on_pb_hs_toolBox_clicked();
    void on_pb_hs_log_clicked();

    void grafik_selectionChanged();
    void grafik_mousePress();
    void grafik_mouseWheel();
    void grafik_axisLabelDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part);
    void grafik_legendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item);
    void grafik_titleDoubleClick(QMouseEvent *event);
    void grafik_contextMenuRequest(QPoint pos);
    void grafik_addRandomGraph();
    void grafik_removeSelectedGraph();
    void grafik_removeAllGraphs();
private:
    Ui::MainWindow *ui;

    QStandardItemModel *modelTree;
    QStandardItemModel *tableModel;
    mTreeView mTree;
    mdi mDi;
    mGraph mGr;
    work w;

    QNetworkAccessManager *manager;
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

    void setIcon();

//    void setupGrafik();

};

#endif // MAINWINDOW_H
