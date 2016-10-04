#ifndef FORM_MODULE_H
#define FORM_MODULE_H

#include <QDialog>
#include "util/global.h"

namespace Ui {
class Form_Module;
}

class Form_Module : public QDialog
{
    Q_OBJECT

public:
    explicit Form_Module(QWidget *parent = 0, QString key = 0);
    ~Form_Module();

    void getENV();
    void getDATA();
private:
    Ui::Form_Module *ui;

    QNetworkAccessManager *manager;
    QString api_key;

private slots:
    void replyFinished(QNetworkReply *reply);
};

#endif // FORM_MODULE_H
