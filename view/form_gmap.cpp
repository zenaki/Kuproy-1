#include "form_gmap.h"
#include "ui_form_gmap.h"

Form_Gmap::Form_Gmap(QWidget *parent, QString ReqLatLng) :
    QDialog(parent),
    ui(new Ui::Form_Gmap)
{
    ui->setupUi(this);

    connect(ui->webView->page(), SIGNAL(loadFinished(bool)), this, SLOT(pageFinished()));
//    ui->webView->reload();

    tmr = new QTimer(this);
    connect(tmr, SIGNAL(timeout()), this, SLOT(TimeOut()));

    this->installEventFilter(this);

    Request = ReqLatLng;

    loading = new QMovie(":/images/loadig-bar.gif");
    ui->lbl_GIF->setMovie(loading);
    loading->start();

    this->on_pb_refresh_clicked();
}

Form_Gmap::~Form_Gmap()
{
    delete ui;
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

void Form_Gmap::setLatLng()
{
//    Request = "-6.40333;106.88776;Module_1;RTU.01;-6.40;106.88776;Module_2;RTU.02";
    ui->webView->page()->runJavaScript(QString("split_LatLng('%1');").arg(Request));
    ui->lbl_GIF->hide(); ui->lbl_loading->hide(); tmr->stop();
}

void Form_Gmap::pageFinished()
{
    this->setLatLng();
}

void Form_Gmap::TimeOut()
{

}

//void Form_Gmap::eventFilter(QObject *o, QEvent *e)
//{
//    if (e->type() == QEvent::FocusIn) {
//        this->setMap();
//    }
//}

void Form_Gmap::on_pb_refresh_clicked()
{
    ui->lbl_GIF->show(); ui->lbl_loading->show(); tmr->start(TIMEOUT);
    this->setMap();
}
