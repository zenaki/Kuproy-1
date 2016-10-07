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

    ui->pte_log->clear();

    connect(ui->webView->page(), SIGNAL(loadFinished(bool)), this, SLOT(pageFinished()));

    modelTree = new QStandardItemModel(this);
    tableModel = new QStandardItemModel(this);

    loading = new QMovie(":/images/loadig-bar.gif");
    loading->start();

    lbl_GIF = new QLabel(this);
    lbl_GIF->setMovie(loading);

    lbl_loading = new QLabel(this);
    lbl_loading->setText("loading ...");

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

//    if (!t.ReqLatLng.isEmpty()) {
//        mTree.add_firstItem(modelTree, ui->treeView, "Maps");
//        parentTree.append("0");
//        mTree.add_firstItem(modelTree, ui->treeView, "Module");
//        for (int i = 0; i < t.jml_module; i++) {
//            mTree.appendItem(modelTree, ui->treeView, t.module[i].module_name, 1);
//            count++;
//        }
//        parentTree.append(QString::number(count));
//    } else {
        mTree.add_firstItem(modelTree, ui->treeView, "Module");
        for (int i = 0; i < t.jml_module; i++) {
            mTree.appendItem(modelTree, ui->treeView, t.module[i].module_name, 0);
            count++;
        }
        parentTree.append(QString::number(count));
//    }

    for (int i = 0; i < parentTree.length(); i++) {
        if (parentTree.at(i).toInt() > 0) {
            ui->treeView->setCurrentIndex(modelTree->index(i,0));
            for (int j = 0; j < parentTree.at(i).toInt(); j++) {
                ui->treeView->setCurrentIndex(modelTree->index(j,0,modelTree->index(i,0)));
                t.module[j].treeModule = mTree.getTreeID(ui->treeView);
            }
        }/* else {
            ui->treeView->setCurrentIndex(modelTree->index(i,0));
            if (mTree.getTreeID(ui->treeView).data().toString() == "Maps") {
                t.maps = mTree.getTreeID(ui->treeView);
            }
        }*/
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

void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
//    QString name = index.data(Qt::DisplayRole).toString();
//    QList<QMdiSubWindow *> windows = ui->mdiArea->subWindowList();
//    bool cek = false;
//    for (int i = 0; i < windows.size(); i++){
//        QWidget *sublist = qobject_cast<QWidget *>(windows.at(i)->widget());
//        if (name == sublist->windowTitle()) {
////            if (name == "Maps") {
////                sublist->close();
////                windows.at(i)->close();
////                ui->mdiArea->removeSubWindow(sublist);
////                mDi.new_Gmap_Window(this, ui->mdiArea, name);
////                sublist->setFocus();
////            } else {
////                sublist->close();
////                windows.at(i)->close();
////                ui->mdiArea->removeSubWindow(sublist);
////                mDi.new_Module_Window(this, ui->mdiArea, name);
////                sublist->setFocus();
////            }
//            sublist->setFocus();
//            cek = true;
//        }
//    }

//    if (cek) {
//        return;
//    } else {
//        if (t.maps == index) {
//            mDi.new_Gmap_Window(this, ui->mdiArea, name, t.ReqLatLng);
//        } else {
//            for (int i = 0; i < t.jml_module; i++) {
//                if (t.module[i].treeModule == index) {
//                    mDi.new_Module_Window(this, ui->mdiArea, name, t.key, t.module[i].id);
//                }
//            }
//        }
    //    }
    for (int i = 0; i < t.jml_module; i++) {
        if (t.module[i].treeModule == index) {
            module_id = t.module[i].id;
            this->setPage();
//            this->setENV(i);
//            this->setDATA(i, !t.d.regData.isEmpty());
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
