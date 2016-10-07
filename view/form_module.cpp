#include "form_module.h"
#include "ui_form_module.h"

Form_Module::Form_Module(QWidget *parent, QString key, int id) :
    QDialog(parent),
    ui(new Ui::Form_Module)
{
    ui->setupUi(this);

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply *)));

    tmr = new QTimer(this);
    connect(tmr, SIGNAL(timeout()), this, SLOT(TimeOut()));

    tableModel = new QStandardItemModel(this);

    this->installEventFilter(this);

    api_key = key; module_id = id;

    loading = new QMovie(":/images/loadig-bar.gif");
    ui->lbl_GIF->setMovie(loading);
    loading->start();
    ui->lbl_GIF->hide(); ui->lbl_loading->hide();

    this->on_pb_refresh_clicked();
}

Form_Module::~Form_Module()
{
    delete ui;
}

void Form_Module::setEnv()
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
        }

        if (t.module[i].jml_gsm > 0) {
            if (!t.module[i].jml_gsm > 1) {
                ui->le_operator_1->setText(t.module[i].gsm[0].opt);
                ui->le_device_name_1->setText(t.module[i].gsm[0].device_name);
                if (t.module[i].gsm[0].status) {
                    ui->le_status_1->setText("ACTIVE");
                } else {
                    ui->le_status_1->setText("NOT ACTIVE");
                }
                ui->le_communication_1->setText(t.module[i].gsm[0].communication);
                ui->le_number_1->setText(t.module[i].gsm[0].number);
                ui->le_apn_1->setText(t.module[i].gsm[0].apn);
                ui->le_username_1->setText(t.module[i].gsm[0].username);
                ui->le_password_1->setText(t.module[i].gsm[0].password);
            } else {
                ui->le_operator_1->setText(t.module[i].gsm[0].opt);
                ui->le_device_name_1->setText(t.module[i].gsm[0].device_name);
                if (t.module[i].gsm[0].status) {
                    ui->le_status_1->setText("ACTIVE");
                } else {
                    ui->le_status_1->setText("NOT ACTIVE");
                }
                ui->le_communication_1->setText(t.module[i].gsm[0].communication);
                ui->le_number_1->setText(t.module[i].gsm[0].number);
                ui->le_apn_1->setText(t.module[i].gsm[0].apn);
                ui->le_username_1->setText(t.module[i].gsm[0].username);
                ui->le_password_1->setText(t.module[i].gsm[0].password);

                ui->le_operator_2->setText(t.module[i].gsm[1].opt);
                ui->le_device_name_2->setText(t.module[i].gsm[1].device_name);
                if (t.module[i].gsm[1].status) {
                    ui->le_status_2->setText("ACTIVE");
                } else {
                    ui->le_status_2->setText("NOT ACTIVE");
                }
                ui->le_communication_2->setText(t.module[i].gsm[1].communication);
                ui->le_number_2->setText(t.module[i].gsm[1].number);
                ui->le_apn_2->setText(t.module[i].gsm[1].apn);
                ui->le_username_2->setText(t.module[i].gsm[1].username);
                ui->le_password_2->setText(t.module[i].gsm[1].password);
            }
        }
    }
}

void Form_Module::setData()
{
    tableModel->setRowCount(2);
    tableModel->setColumnCount(2);
    tableModel->setHorizontalHeaderItem(0, new QStandardItem(QString("Register")));
    tableModel->setHorizontalHeaderItem(1, new QStandardItem(QString("Value")));

    for (int i = 0; i < t.d.regData.length(); i++) {
        tableModel->setItem(i,0, new QStandardItem(t.d.regData.at(i)));
        tableModel->setItem(i,1, new QStandardItem(t.d.valData.at(i)));
    }

    ui->table_data->setModel(tableModel);
}

//void Form_Module::eventFilter(QObject *o, QEvent *e)
//{
//    if (e->type() == QEvent::FocusIn) {
//        w.request_ENV(manager, api_key);
//        w.request_Data(manager, api_key, module_id);
//    }
//}

void Form_Module::replyFinished(QNetworkReply *reply)
{
    ui->lbl_GIF->hide(); ui->lbl_loading->hide(); tmr->stop();
    QByteArray data;
    data.clear();
    data = reply->readAll();

    t = w.respone_json(data, t, api_key);
    if (t.jml_module > 0) {
        this->setEnv();
    }
    if (!t.d.regData.isEmpty()) {
        tableModel->clear();
        this->setData();
    } else {
        tableModel->clear();
        tableModel->setRowCount(2);
        tableModel->setColumnCount(2);
        tableModel->setHorizontalHeaderItem(0, new QStandardItem(QString("Register")));
        tableModel->setHorizontalHeaderItem(1, new QStandardItem(QString("Value")));
        tableModel->setItem(1,0, new QStandardItem(QString("N/A")));
        tableModel->setItem(1,1, new QStandardItem(QString("N/A")));
        ui->table_data->setModel(tableModel);
    }
    ui->lbl_GIF->hide(); ui->lbl_loading->hide();
}

void Form_Module::TimeOut()
{
    ui->lbl_GIF->hide(); ui->lbl_loading->hide(); tmr->stop();
    QMessageBox::critical(this, "Sarasati Opearational - " + this->windowTitle(), "Cannot login ,,\r\nPlease check your internet connection ..");
}

void Form_Module::on_pb_refresh_clicked()
{
    ui->lbl_GIF->show(); ui->lbl_loading->show(); tmr->start(TIMEOUT);
//    w.request_ENV(manager, api_key);
//    w.request_Data(manager, api_key, module_id);
}
