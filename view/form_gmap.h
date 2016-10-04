#ifndef FORM_GMAP_H
#define FORM_GMAP_H

#include <QDialog>
#include "util/global.h"

namespace Ui {
class Form_Gmap;
}

class Form_Gmap : public QDialog
{
    Q_OBJECT

public:
    explicit Form_Gmap(QWidget *parent = 0, QString key = 0);
    ~Form_Gmap();

    void setMap();
    void setLatLng(QString Request);
public slots:
    void pageFinished();
private:
    Ui::Form_Gmap *ui;

    QNetworkAccessManager *manager;
    QString api_key;

private slots:
    void replyFinished(QNetworkReply *reply);
};

#endif // FORM_GMAP_H
