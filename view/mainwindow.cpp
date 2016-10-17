#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, QString key) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::setWindowTitle("Sarasvati - MONITA RTU Operational");
    MainWindow::showMaximized();

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply *)));

    tmr = new QTimer(this);
//    connect(tmr, SIGNAL(timeout()), this, SLOT(TimeOut()));

    ui->treeView->header()->setHidden(true);
    ui->treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tabWidget->setCurrentIndex(0);
    ui->toolBox->setCurrentIndex(0);
    ui->pte_log->clear();

    connect(ui->webView->page(), SIGNAL(loadFinished(bool)), this, SLOT(pageFinished()));

    modelTree = new QStandardItemModel(this);
    tableModel = new QStandardItemModel(this);
    ui->toolBox->setEnabled(false);
    mGr.setupGrafik(this, ui->customPlot);

    this->setIcon();

    loading = new QMovie(":/images/loadig-bar.gif");
    loading->start();

    lbl_GIF = new QLabel(this);
    lbl_GIF->setFrameStyle(QFrame::NoFrame);
    lbl_GIF->setMovie(loading);

    lbl_loading = new QLabel(this);
    lbl_loading->setFrameStyle(QFrame::NoFrame);
    lbl_loading->setText("Loading ...");

    this->statusBar()->addWidget(lbl_GIF);
    this->statusBar()->addWidget(lbl_loading);
    lbl_GIF->hide(); lbl_loading->hide(); tmr->stop();

    t.key = key;
    module_id = 0;
    this->on_actionRefresh_triggered();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::replyFinished(QNetworkReply *reply)
{
    lbl_GIF->hide(); lbl_loading->hide(); tmr->stop();
    QByteArray data;
    data = reply->readAll();

    t = w.respone_json(data, t, t.key);
    if (t.lastRequest == "env") {
        ui->pte_log->appendPlainText(
                    QDateTime::currentDateTime().toString("HH:mm:ss:zzz - ") +
                    "Get Environment ...");
        if (t.jml_module > 0) {
            this->refreshTree();
            this->setMap();
        } else {
            QMessageBox::critical(this, "Sarasvati Operational", "No Board has found in this user ..");
        }
    } else if (t.lastRequest == "data") {
        ui->pte_log->appendPlainText(
                    QDateTime::currentDateTime().toString("HH:mm:ss:zzz - ") +
                    "Get Data ...");
        this->setDATA();
    }
}

void MainWindow::refreshTree()
{
    modelTree->clear();
    int count = 0; QStringList parentTree;

    mTree.add_firstItem(modelTree, ui->treeView, "Module");
    for (int i = 0; i < t.jml_module; i++) {
        mTree.appendItem(modelTree, ui->treeView, t.module[i].module_name, 0);
        count++;
    }
    parentTree.append(QString::number(count));
    for (int i = 0; i < parentTree.length(); i++) {
        if (parentTree.at(i).toInt() > 0) {
            ui->treeView->setCurrentIndex(modelTree->index(i,0));
            for (int j = 0; j < parentTree.at(i).toInt(); j++) {
                ui->treeView->setCurrentIndex(modelTree->index(j,0,modelTree->index(i,0)));
                t.module[j].treeModule = mTree.getTreeID(ui->treeView);
            }
        }
    }
    ui->treeView->collapseAll();
}

void MainWindow::setMap()
{
    QString fileName = ":/map/gmap.html";
    if(!QFile(fileName).exists()) {
        QMessageBox::critical(this, tr("Attention !!"),
        "File not found: " + fileName);
        return;
    } else {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Sorry .."),
            "Cannot Set Map ..\n" + file.errorString());
            return;
        }
        QTextStream out(&file);
        QString output = out.readAll();

        // display contents
        ui->webView->setHtml(output);
        ui->pte_log->appendPlainText(
                    QDateTime::currentDateTime().toString("HH:mm:ss:zzz - ") +
                    "Set Map ...");
    }
}

void MainWindow::setLatLng()
{
//    Request = "-6.40333;106.88776;Module_1;RTU.01;-6.40;106.88776;Module_2;RTU.02";
    if (!t.ReqLatLng.isEmpty())
        ui->webView->page()->runJavaScript(QString("split_LatLng('%1');").arg(t.ReqLatLng));
    lbl_GIF->hide(); lbl_loading->hide(); tmr->stop();
    ui->pte_log->appendPlainText(
                QDateTime::currentDateTime().toString("HH:mm:ss:zzz - ") +
                "Map Finished ...");
}

void MainWindow::setPage()
{
    ui->toolBox->setEnabled(true);
    this->setENV();
    this->on_pb_Refresh_Data_clicked();
}

void MainWindow::setENV()
{
    for (int i = 0; i < t.jml_module; i++) {
        if (t.module[i].id == module_id) {
            ui->le_module_name->setText(t.module[i].module_name);
            ui->le_serial_number->setText(t.module[i].serial_number);
            ui->le_latitude->setText(t.module[i].latitude);
            ui->le_longitude->setText(t.module[i].longitude);
            ui->le_server_address->setText(t.module[i].server);
            ui->le_file_address->setText(t.module[i].file);
            if (t.module[i].web_client) {
                ui->le_web_client->setText("ACTIVE");
            } else {
                ui->le_web_client->setText("NOT ACTIVE");
            }
            ui->le_interval->setText(QString::number(t.module[i].interval));

            if (t.module[i].jml_gsm > 0) {
                if (!t.module[i].jml_gsm > 1) {
                    this->setGSM1(i, true);
                } else {
                    this->setGSM1(i, true);
                    this->setGSM2(i, true);
                }
            } else {
                this->setGSM1(i, false);
                this->setGSM2(i, false);
            }
            break;
        }
    }
}

void MainWindow::setGSM1(int index, bool act)
{
    if (act) {
        ui->le_operator_1->setText(t.module[index].gsm[0].opt);
        ui->le_device_name_1->setText(t.module[index].gsm[0].device_name);
        if (t.module[index].gsm[0].status) {
            ui->le_status_1->setText("ACTIVE");
        } else {
            ui->le_status_1->setText("NOT ACTIVE");
        }
        ui->le_communication_1->setText(t.module[index].gsm[0].communication);
        ui->le_number_1->setText(t.module[index].gsm[0].number);
        ui->le_apn_1->setText(t.module[index].gsm[0].apn);
        ui->le_username_1->setText(t.module[index].gsm[0].username);
        ui->le_password_1->setText(t.module[index].gsm[0].password);
    } else {
        ui->le_operator_1->clear();
        ui->le_device_name_1->clear();
        ui->le_status_1->clear();
        ui->le_communication_1->clear();
        ui->le_number_1->clear();
        ui->le_apn_1->clear();
        ui->le_username_1->clear();
        ui->le_password_1->clear();
    }
}

void MainWindow::setGSM2(int index, bool act)
{
    if (act) {
        ui->le_operator_2->setText(t.module[index].gsm[1].opt);
        ui->le_device_name_2->setText(t.module[index].gsm[1].device_name);
        if (t.module[index].gsm[1].status) {
            ui->le_status_2->setText("ACTIVE");
        } else {
            ui->le_status_2->setText("NOT ACTIVE");
        }
        ui->le_communication_2->setText(t.module[index].gsm[1].communication);
        ui->le_number_2->setText(t.module[index].gsm[1].number);
        ui->le_apn_2->setText(t.module[index].gsm[1].apn);
        ui->le_username_2->setText(t.module[index].gsm[1].username);
        ui->le_password_2->setText(t.module[index].gsm[1].password);
    } else {
        ui->le_operator_2->clear();
        ui->le_device_name_2->clear();
        ui->le_status_2->clear();
        ui->le_communication_2->clear();
        ui->le_number_2->clear();
        ui->le_apn_2->clear();
        ui->le_username_2->clear();
        ui->le_password_2->clear();
    }
}

void MainWindow::setDATA()
{
    for (int i = 0; i < t.jml_module; i++) {
        if ((t.module[i].id == module_id) && (!t.module[i].d.regData.isEmpty())) {
            tableModel->setRowCount(2);
            tableModel->setColumnCount(2);
            tableModel->setHorizontalHeaderItem(0, new QStandardItem(QString("Register")));
            tableModel->setHorizontalHeaderItem(1, new QStandardItem(QString("Value")));

            for (int j = 0; j < t.module[i].d.regData.length(); j++) {
                tableModel->setItem(j,0, new QStandardItem(t.module[i].d.regData.at(j)));
                tableModel->setItem(j,1, new QStandardItem(t.module[i].d.valData.at(j)));
            }

            ui->table_data->setModel(tableModel);
            break;
        } else {
            tableModel->clear();
            ui->table_data->setModel(tableModel);
        }
    }
}

void MainWindow::setIcon()
{
    QPixmap pixmap(":/images/arrow-2.png");

    ui->pb_hs_treeView->setIcon(QIcon(pixmap));
    ui->pb_hs_treeView->setIconSize(QSize(20,20));
    ui->pb_hs_treeView->setIcon(ui->pb_hs_treeView->icon().pixmap(QSize(20,20)).transformed(QMatrix().rotate(90)));

    ui->pb_hs_log->setIcon(QIcon(pixmap));
    ui->pb_hs_log->setIconSize(QSize(20,20));

    ui->pb_hs_toolBox->setIcon(QIcon(pixmap));
    ui->pb_hs_toolBox->setIconSize(QSize(20,20));
    ui->pb_hs_toolBox->setIcon(ui->pb_hs_toolBox->icon().pixmap(QSize(20,20)).transformed(QMatrix().rotate(270)));
}

void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    for (int i = 0; i < t.jml_module; i++) {
        if (t.module[i].treeModule == index) {
            module_id = t.module[i].id;
            this->setPage();
            break;
        }
    }
}

void MainWindow::pageFinished()
{
    this->setLatLng();
}

void MainWindow::TimeOut()
{
    lbl_GIF->hide(); lbl_loading->hide(); tmr->stop();
    QMessageBox::critical(this, "Sarasvati Operational", "Timeout !");
}

void MainWindow::on_actionRefresh_triggered()
{
    lbl_GIF->show(); lbl_loading->show(); tmr->start(TIMEOUT);
    t.jml_module = 0;
    ui->pte_log->appendPlainText(
                QDateTime::currentDateTime().toString("HH:mm:ss:zzz - ") +
                "Request Environment ...");
    w.request_ENV(manager, t.key);
}

void MainWindow::on_pb_Refresh_Data_clicked()
{
    lbl_GIF->show(); lbl_loading->show(); tmr->start(TIMEOUT);
    ui->pte_log->appendPlainText(
                QDateTime::currentDateTime().toString("HH:mm:ss:zzz - ") +
                "Request Data ...");
    w.request_Data(manager, t.key, module_id);
}

void MainWindow::on_pb_hs_treeView_clicked()
{
    if (ui->treeView->isHidden()) {
        ui->treeView->setHidden(false);
    } else {
        ui->treeView->setHidden(true);
    }
    ui->pb_hs_treeView->setIcon(ui->pb_hs_treeView->icon().pixmap(QSize(20,20)).transformed(QMatrix().rotate(180)));
}

void MainWindow::on_pb_hs_toolBox_clicked()
{
    if (ui->toolBox->isHidden()) {
        ui->toolBox->setHidden(false);
    } else {
        ui->toolBox->setHidden(true);
    }
    ui->pb_hs_toolBox->setIcon(ui->pb_hs_toolBox->icon().pixmap(QSize(20,20)).transformed(QMatrix().rotate(180)));

}

void MainWindow::on_pb_hs_log_clicked()
{
    if (ui->pte_log->isHidden()) {
        ui->pte_log->setHidden(false);
    } else {
        ui->pte_log->setHidden(true);
    }
    ui->pb_hs_log->setIcon(ui->pb_hs_log->icon().pixmap(QSize(20,20)).transformed(QMatrix().rotate(180)));
}

void MainWindow::grafik_selectionChanged()
{
    mGr.selectionChanged(ui->customPlot);
}

void MainWindow::grafik_axisLabelDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part)
{
    mGr.axisLabelDoubleClick(this, axis, part, ui->customPlot);
}

void MainWindow::grafik_legendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item)
{
    mGr.legendDoubleClick(this, legend, item, ui->customPlot);
}

void MainWindow::grafik_titleDoubleClick(QMouseEvent *event)
{
    mGr.titleDoubleClick(this, event, ui->customPlot);
}

void MainWindow::grafik_contextMenuRequest(QPoint pos)
{
    mGr.contextMenuRequest(this, pos, ui->customPlot);
}

void MainWindow::grafik_addRandomGraph()
{
    mGr.addRandomGraph(ui->customPlot);
}

void MainWindow::grafik_removeSelectedGraph()
{
    mGr.removeSelectedGraph(ui->customPlot);
}

void MainWindow::grafik_removeAllGraphs()
{
    mGr.removeAllGraphs(ui->customPlot);
}
