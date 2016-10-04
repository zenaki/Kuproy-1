#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply *)));

    connect(ui->leUsername, SIGNAL(returnPressed()), ui->pbOK, SIGNAL(clicked()));
    connect(ui->lePassword, SIGNAL(returnPressed()), ui->pbOK, SIGNAL(clicked()));
}

Login::~Login()
{
    delete ui;
}

void Login::on_pbOK_clicked()
{
    QNetworkRequest request;

    QUrl url =  QUrl::fromEncoded("http://localhost/sarasvati/api/sarasvati.php?get=user&format=json");
    request.setUrl(url);
    manager->get(request);
}

void Login::on_pbExit_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Sarasvati Operational", "Are you sure ??", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QApplication::quit();
    }
    //    QApplication::exit();
}

void Login::replyFinished(QNetworkReply *reply)
{
    QByteArray data;
    data.clear();
    data = reply->readAll();

    QJsonObject object = QJsonDocument::fromJson(data).object();
    QJsonArray jsonArray = object.value("Sarasvati").toArray();
    bool success = false; QString api_key;
    foreach (const QJsonValue & v, jsonArray) {
        if (v.toObject().value("username").toString() == ui->leUsername->text() &&
                v.toObject().value("password").toString() == ui->lePassword->text()) {
            api_key = v.toObject().value("api_key").toString();
            success = true;
            break;
        }
    }
    if (success) {
        QMessageBox::information(this, "Sarasvati Operational", "Login Success ..!!");
        mainwindow = new MainWindow(this, api_key);
        mainwindow->show();
        this->hide();
    } else {
        QMessageBox::information(this, "Sarasvati Operational", "Login Fail ..!! \r\n Please check your username and password ..");
    }
}
