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
    explicit Form_Gmap(QWidget *parent = 0, QString ReqLatLng = 0);
    ~Form_Gmap();

    void setMap();
    void setLatLng();

public slots:
    void pageFinished();

private slots:
    void TimeOut();
    void on_pb_refresh_clicked();

private:
    Ui::Form_Gmap *ui;

    QTimer *tmr;
    QMovie *loading;
    QString Request;

//    void eventFilter(QObject *o, QEvent *e);
};

#endif // FORM_GMAP_H
