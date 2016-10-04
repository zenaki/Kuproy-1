#include "form_gmap.h"
#include "ui_form_gmap.h"

Form_Gmap::Form_Gmap(QWidget *parent, QString key) :
    QDialog(parent),
    ui(new Ui::Form_Gmap)
{
    ui->setupUi(this);

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply *)));

    connect(ui->webView->page(), SIGNAL(loadFinished(bool)), this, SLOT(pageFinished()));
    this->setMap();
}

Form_Gmap::~Form_Gmap()
{
    delete ui;
//    this->destroy();
//    this->parentWidget()->close();
}

void Form_Gmap::setMap()
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
    }
}

void Form_Gmap::setLatLng(QString Request) {
    Request = "-6.40333;106.88776;Module_1;RTU.01;-6.40;106.88776;Module_2;RTU.02";
    ui->webView->page()->runJavaScript(QString("split_LatLng('%1');").arg(Request));
}

void Form_Gmap::pageFinished()
{
    this->setLatLng("Debug");
}

void Form_Gmap::replyFinished(QNetworkReply *reply)
{

}
