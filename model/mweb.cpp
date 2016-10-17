#include "mweb.h"

mWeb::mWeb(QObject *parent) : QObject(parent)
{

}

void mWeb::setupWeb(QWidget *parent, QWebEngineView *webGmap)
{
    connect(webGmap->page(), SIGNAL(loadFinished(bool)), parent, SLOT(pageFinished()));
}

void mWeb::setLatLng(QWebEngineView *webGmap, QPlainTextEdit *pte_log, struct tree t, QLabel *lbl_GIF, QLabel *lbl_loading, QTimer *tmr)
{
    //    Request = "-6.40333;106.88776;Module_1;RTU.01;-6.40;106.88776;Module_2;RTU.02";
        if (!t.ReqLatLng.isEmpty())
            webGmap->page()->runJavaScript(QString("split_LatLng('%1');").arg(t.ReqLatLng));
        lbl_GIF->hide(); lbl_loading->hide(); tmr->stop();
        pte_log->appendPlainText(
                    QDateTime::currentDateTime().toString("HH:mm:ss:zzz - ") +
                    "Map Finished ...");
}

void mWeb::setMap(QWidget *parent, QWebEngineView *webGmap, QWebEngineView *webGraph ,QPlainTextEdit *pte_log)
{
    QString fileName = ":/html/gmap.html";
    if(!QFile(fileName).exists()) {
        QMessageBox::critical(parent, tr("Attention !!"),
        "File not found: " + fileName);
        return;
    } else {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(parent, tr("Sorry .."),
            "Cannot Set Map ..\n" + file.errorString());
            return;
        }
        QTextStream out(&file);
        QString output = out.readAll();

        // display contents
        webGmap->setHtml(output);
        pte_log->appendPlainText(
                    QDateTime::currentDateTime().toString("HH:mm:ss:zzz - ") +
                    "Set Map ...");
    }

    fileName = ":/html/graph.html";
    if(!QFile(fileName).exists()) {
        QMessageBox::critical(parent, tr("Attention !!"),
        "File not found: " + fileName);
        return;
    } else {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(parent, tr("Sorry .."),
            "Cannot Set Graph ..\n" + file.errorString());
            return;
        }
        QTextStream out(&file);
        QString output = out.readAll();

        // display contents
        webGraph->setHtml(output);
    }
}
