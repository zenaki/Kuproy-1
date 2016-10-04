#ifndef GLOBAL_H
#define GLOBAL_H

#include <QDebug>
#include <QMessageBox>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QTreeView>
#include <QTableView>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QMdiArea>
#include <QMdiSubWindow>

#include <QFile>

#define MAX_RTU 10

struct gsm_mod {
    QString opt;
    QString device_name;
    bool status;
    QString communication;
    QString number;
    QString apn;
    QString username;
    QString password;
};

struct module {
    int id;
    QString module_name;
    QString serial_number;
    QString latitude;
    QString longitude;
    QString server;
    QString file;
    bool web_client;
    int interval;

    QStringList regData;
    QStringList valData;

    struct gsm_mod gsm[2];
};

#endif // GLOBAL_H
