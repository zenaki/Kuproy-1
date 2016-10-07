#ifndef WORK_H
#define WORK_H

#include "util/global.h"

class work
{
public:
    work();

    void request_ENV(QNetworkAccessManager *manager, QNetworkReply *r, QString api_key);
    void request_Data(QNetworkAccessManager *manager, QNetworkReply *r, QString api_key, int id);
    struct tree respone_json(QByteArray data, struct tree t, QString key);
};

#endif // WORK_H
