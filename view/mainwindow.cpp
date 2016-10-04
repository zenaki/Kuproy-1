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

    ui->treeView->header()->setHidden(true);
    ui->treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    modelTree = new QStandardItemModel(this);

    jml_module = 0;
    api_key = key;
    this->getENV();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::replyFinished(QNetworkReply *reply)
{
    QByteArray data;
    data.clear();
    data = reply->readAll();

    QJsonObject object = QJsonDocument::fromJson(data).object();
    QJsonArray env_jsonArray = object.value("Sarasvati").toObject().value("env").toArray();
    QJsonArray data_jsonArray = object.value("Sarasvati").toObject().value("data").toArray();
    if (!env_jsonArray.isEmpty()) {
        foreach (const QJsonValue & v, env_jsonArray) {
            module_rtu[jml_module].id = v.toObject().value("id").toString().toInt();
            module_rtu[jml_module].module_name = v.toObject().value("module_name").toString();
            module_rtu[jml_module].serial_number = v.toObject().value("serial_number").toString();
            module_rtu[jml_module].latitude = v.toObject().value("latitude").toString();
            module_rtu[jml_module].longitude = v.toObject().value("longitude").toString();
            module_rtu[jml_module].server = v.toObject().value("server").toString();
            module_rtu[jml_module].file = v.toObject().value("file").toString();
            module_rtu[jml_module].web_client = v.toObject().value("web_client").toString().toInt();
            module_rtu[jml_module].interval = v.toObject().value("interval").toString().toInt();
            jml_module++;
        }
        this->refreshTree();
    } else if (!data_jsonArray.isEmpty()) {
        foreach (const QJsonValue & v, data_jsonArray) {
            for (int i = 0; i < jml_module; i++) {
                if (module_rtu[i].id == v.toObject().value("id").toString().toInt()) {
                    foreach (const QJsonValue & vData, v.toObject().value("titik_ukur").toArray()) {
                        module_rtu[i].regData.append(vData.toObject().value("register").toString());
                        module_rtu[i].regData.append(vData.toObject().value("value").toString());
                    }
                }
            }
        }
        this->refreshData();
    }
}

void MainWindow::getENV()
{
    QNetworkRequest request;
    QString strURL = "http://localhost/sarasvati/api/sarasvati.php?get=environment&api_key=" + api_key + "&format=json";
    QUrl url =  QUrl::fromEncoded(strURL.toUtf8());
    request.setUrl(url);
    manager->get(request);
}

void MainWindow::getDATA()
{
    QNetworkRequest request;
    QString strURL = "http://localhost/sarasvati/api/sarasvati.php?get=data&api_key=" + api_key + "&format=json";
    QUrl url =  QUrl::fromEncoded(strURL.toUtf8());
    request.setUrl(url);
    manager->get(request);
}

void MainWindow::refreshTree()
{
    modelTree->clear(); bool gmap;
    if (jml_module > 0) {
        for (int i = 0; i < jml_module; i++) {
            if (!module_rtu[i].latitude.isEmpty() and !module_rtu[i].longitude.isEmpty()) {
                gmap = true;
            }
        }
        if (gmap) {
            mTree.add_firstItem(modelTree, ui->treeView, "Maps");
        }
        mTree.add_firstItem(modelTree, ui->treeView, "Module");
        for (int i = 0; i < jml_module; i++) {
            mTree.appendItem(modelTree, ui->treeView, module_rtu[i].module_name, 1);
        }
    }
}

void MainWindow::refreshData()
{

}

void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    QString name = index.data(Qt::DisplayRole).toString();
    QList<QMdiSubWindow *> windows = ui->mdiArea->subWindowList();
    bool cek = false;
    for (int i = 0; i < windows.size(); i++){
        QWidget *sublist = qobject_cast<QWidget *>(windows.at(i)->widget());
        if (name == sublist->windowTitle()) {
            if (name == "Maps") {
//                sublist->close();
//                windows.at(i)->close();
//                ui->mdiArea->removeSubWindow(sublist);
//                mDi.new_Gmap_Window(this, ui->mdiArea, name);
                sublist->setFocus();
            } else {
//                sublist->close();
//                windows.at(i)->close();
//                ui->mdiArea->removeSubWindow(sublist);
//                mDi.new_Module_Window(this, ui->mdiArea, name);
                sublist->setFocus();
            }
            cek = true;
        }
    }

    if (cek) {
        return;
    } else {
        if (name == "Maps") {
            mDi.new_Gmap_Window(this, ui->mdiArea, name, api_key);
        } else {
            mDi.new_Module_Window(this, ui->mdiArea, name, api_key);
        }
    }

//    if(work->checkIfmodule(name))
//        work->showModule(this, this->ui->mdiArea, name, SerialPort);
//    else
//        return;
}

void MainWindow::on_actionRefresh_triggered()
{
    this->getENV();
}
