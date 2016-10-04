#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

#include "util/global.h"
#include "view/mainwindow.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_pbOK_clicked();
    void on_pbExit_clicked();
    void replyFinished(QNetworkReply *reply);

private:
    Ui::Login *ui;

    QNetworkAccessManager *manager;
    MainWindow *mainwindow;
};

#endif // LOGIN_H
