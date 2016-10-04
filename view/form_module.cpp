#include "form_module.h"
#include "ui_form_module.h"

Form_Module::Form_Module(QWidget *parent, QString key) :
    QDialog(parent),
    ui(new Ui::Form_Module)
{
    ui->setupUi(this);

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply *)));

}

Form_Module::~Form_Module()
{
    delete ui;
//    this->destroy();
    //    this->parentWidget()->close();
}

void Form_Module::getENV()
{
    QNetworkRequest request;
    QString strURL = "http://localhost/sarasvati/api/sarasvati.php?get=environment&api_key=" + api_key + "&format=json";
    QUrl url =  QUrl::fromEncoded(strURL.toUtf8());
    request.setUrl(url);
    manager->get(request);
}

void Form_Module::getDATA()
{
    QNetworkRequest request;
    QString strURL = "http://localhost/sarasvati/api/sarasvati.php?get=data&api_key=" + api_key + "&format=json";
    QUrl url =  QUrl::fromEncoded(strURL.toUtf8());
    request.setUrl(url);
    manager->get(request);
}

void Form_Module::replyFinished(QNetworkReply *reply)
{
    QByteArray data;
    data.clear();
    data = reply->readAll();

    QJsonObject object = QJsonDocument::fromJson(data).object();
    QJsonArray env_jsonArray = object.value("Sarasvati").toObject().value("env").toArray();
    QJsonArray data_jsonArray = object.value("Sarasvati").toObject().value("data").toArray();
    if (!env_jsonArray.isEmpty()) {
        foreach (const QJsonValue & v, env_jsonArray) {
            if (this->windowTitle() == v.toObject().value("module_name").toString()) {
//                module_rtu[jml_module].id = v.toObject().value("id").toString().toInt();
//                module_rtu[jml_module].module_name = v.toObject().value("module_name").toString();
//                module_rtu[jml_module].serial_number = v.toObject().value("serial_number").toString();
//                module_rtu[jml_module].latitude = v.toObject().value("latitude").toString();
//                module_rtu[jml_module].longitude = v.toObject().value("longitude").toString();
//                module_rtu[jml_module].server = v.toObject().value("server").toString();
//                module_rtu[jml_module].file = v.toObject().value("file").toString();
//                module_rtu[jml_module].web_client = v.toObject().value("web_client").toString().toInt();
//                module_rtu[jml_module].interval = v.toObject().value("interval").toString().toInt();

                ui->le_module_name->setText(v.toObject().value("module_name").toString());
                ui->le_serial_number->setText(v.toObject().value("serial_number").toString());
//                ui->le_server_address
            }
        }
    } else if (!data_jsonArray.isEmpty()) {
        foreach (const QJsonValue & v, data_jsonArray) {
//            for (int i = 0; i < jml_module; i++) {
//                if (module_rtu[i].id == v.toObject().value("id").toString().toInt()) {
//                    foreach (const QJsonValue & vData, v.toObject().value("titik_ukur").toArray()) {
//                        module_rtu[i].regData.append(vData.toObject().value("register").toString());
//                        module_rtu[i].regData.append(vData.toObject().value("value").toString());
//                    }
//                }
//            }
        }
    }
}
