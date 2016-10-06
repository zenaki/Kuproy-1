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
    connect(tmr, SIGNAL(timeout()), this, SLOT(TimeOut()));

    ui->treeView->header()->setHidden(true);
    ui->treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    modelTree = new QStandardItemModel(this);

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
    if (t.jml_module > 0) {
        this->refreshTree();
    } else {
        QMessageBox::critical(this, "Sarasvati Operational", "No Board has found in this user ..");
    }
}

void MainWindow::refreshTree()
{
    modelTree->clear();
    int count = 0; QStringList parentTree;

    if (!t.ReqLatLng.isEmpty()) {
        mTree.add_firstItem(modelTree, ui->treeView, "Maps");
        parentTree.append("0");
        mTree.add_firstItem(modelTree, ui->treeView, "Module");
        for (int i = 0; i < t.jml_module; i++) {
            mTree.appendItem(modelTree, ui->treeView, t.module[i].module_name, 1);
            count++;
        }
        parentTree.append(QString::number(count));
    } else {
        mTree.add_firstItem(modelTree, ui->treeView, "Module");
        for (int i = 0; i < t.jml_module; i++) {
            mTree.appendItem(modelTree, ui->treeView, t.module[i].module_name, 0);
            count++;
        }
        parentTree.append(QString::number(count));
    }

    for (int i = 0; i < parentTree.length(); i++) {
        if (parentTree.at(i).toInt() > 0) {
            ui->treeView->setCurrentIndex(modelTree->index(i,0));
            for (int j = 0; j < parentTree.at(i).toInt(); j++) {
                ui->treeView->setCurrentIndex(modelTree->index(j,0,modelTree->index(i,0)));
                t.module[j].treeModule = mTree.getTreeID(ui->treeView);
            }
        } else {
            ui->treeView->setCurrentIndex(modelTree->index(i,0));
            if (mTree.getTreeID(ui->treeView).data().toString() == "Maps") {
                t.maps = mTree.getTreeID(ui->treeView);
            }
        }
    }
    ui->treeView->collapseAll();
}

void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    QString name = index.data(Qt::DisplayRole).toString();
    QList<QMdiSubWindow *> windows = ui->mdiArea->subWindowList();
    bool cek = false;
    for (int i = 0; i < windows.size(); i++){
        QWidget *sublist = qobject_cast<QWidget *>(windows.at(i)->widget());
        if (name == sublist->windowTitle()) {
//            if (name == "Maps") {
//                sublist->close();
//                windows.at(i)->close();
//                ui->mdiArea->removeSubWindow(sublist);
//                mDi.new_Gmap_Window(this, ui->mdiArea, name);
//                sublist->setFocus();
//            } else {
//                sublist->close();
//                windows.at(i)->close();
//                ui->mdiArea->removeSubWindow(sublist);
//                mDi.new_Module_Window(this, ui->mdiArea, name);
//                sublist->setFocus();
//            }
            sublist->setFocus();
            cek = true;
        }
    }

    if (cek) {
        return;
    } else {
        if (t.maps == index) {
            mDi.new_Gmap_Window(this, ui->mdiArea, name, t.ReqLatLng);
        } else {
            for (int i = 0; i < t.jml_module; i++) {
                if (t.module[i].treeModule == index) {
                    mDi.new_Module_Window(this, ui->mdiArea, name, t.key, t.module[i].id);
                }
            }
        }
    }
}

void MainWindow::on_actionRefresh_triggered()
{
    lbl_GIF->show(); lbl_loading->show(); tmr->start(TIMEOUT);
    t.jml_module = 0;
    w.request_ENV(manager, t.key);
}
