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
#include <QMovie>
#include <QTimer>

#define MAX_RTU 10
#define TIMEOUT 5000
#define SERVER "http://66.228.59.91:8080"
//#define SERVER "http://localhost"

struct data {
    QStringList regData;
    QStringList valData;
};

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
    QModelIndex treeModule;
    int id;
    QString module_name;
    QString serial_number;
    QString latitude;
    QString longitude;
    QString server;
    QString file;
    bool web_client;
    int interval;

//    QStringList regData;
//    QStringList valData;
    struct data d;

    struct gsm_mod gsm[2];
    int jml_gsm;
};

struct tree {
    QModelIndex maps;
    QString ReqLatLng;
    QString key;
    struct module module[MAX_RTU];
    int jml_module;

    struct data d;

    QString lastRequest;
};

#endif // GLOBAL_H
