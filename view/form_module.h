#ifndef FORM_MODULE_H
#define FORM_MODULE_H

#include <QDialog>

#include "util/global.h"
#include "control/work.h"

namespace Ui {
class Form_Module;
}

class Form_Module : public QDialog
{
    Q_OBJECT

public:
    explicit Form_Module(QWidget *parent = 0, QString key = 0, int id = 0);
    ~Form_Module();

    void getENV();
    void getDATA();
private:
    Ui::Form_Module *ui;

    QNetworkAccessManager *manager;
    QTimer *tmr;
    struct tree t;
    work w;
    QString api_key;
    int module_id;

    void setEnv();
    void setData();

    QStandardItemModel *tableModel;

    QMovie *loading;

//    void eventFilter(QObject *o, QEvent *e);

private slots:
    void replyFinished(QNetworkReply *reply);
    void TimeOut();
    void on_pb_refresh_clicked();
};

#endif // FORM_MODULE_H
