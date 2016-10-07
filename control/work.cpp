#include "work.h"

work::work()
{

}

void work::request_ENV(QNetworkAccessManager *manager, QString api_key)
{
    QNetworkRequest request;
    QString server = SERVER;
    QString strURL = server + "/sarasvati/api/sarasvati.php?get=environment&api_key=" + api_key + "&format=json";
    QUrl url =  QUrl::fromEncoded(strURL.toUtf8());
    request.setUrl(url);
    manager->get(request);
}

void work::request_Data(QNetworkAccessManager *manager, QString api_key, int id)
{
    QNetworkRequest request;
    QString server = SERVER;
    QString strURL = server + "/sarasvati/api/sarasvati.php?get=data&api_key=" + api_key + "&id=" + QString::number(id) + "&format=json";
    QUrl url =  QUrl::fromEncoded(strURL.toUtf8());
    request.setUrl(url);
    manager->get(request);
}

struct tree work::respone_json(QByteArray data, struct tree t, QString key)
{
    QJsonObject object = QJsonDocument::fromJson(data).object();
    QJsonArray env_jsonArray = object.value("Sarasvati").toObject().value("env").toArray();
    QJsonArray data_jsonArray = object.value("Sarasvati").toObject().value("data").toArray();
    if (!env_jsonArray.isEmpty()) {
        t.jml_module = 0;
        foreach (const QJsonValue & v, env_jsonArray) {
            if (!v.toObject().value("latitude").isNull() && !v.toObject().value("longitude").isNull()) {
                if (!t.ReqLatLng.isEmpty()) {
                    t.ReqLatLng = t.ReqLatLng +
                            ";" + v.toObject().value("latitude").toString() +
                            ";" + v.toObject().value("longitude").toString() +
                            ";" + v.toObject().value("module_name").toString() +
                            ";" + v.toObject().value("serial_number").toString();
                } else {
                    t.ReqLatLng = v.toObject().value("latitude").toString() +
                            ";" + v.toObject().value("longitude").toString() +
                            ";" + v.toObject().value("module_name").toString() +
                            ";" + v.toObject().value("serial_number").toString();
                }
            }

            t.key = key;
            t.module[t.jml_module].id = v.toObject().value("id").toString().toInt();
            t.module[t.jml_module].module_name = v.toObject().value("module_name").toString();
            t.module[t.jml_module].serial_number = v.toObject().value("serial_number").toString();
            t.module[t.jml_module].latitude = v.toObject().value("latitude").toString();
            t.module[t.jml_module].longitude = v.toObject().value("longitude").toString();
            t.module[t.jml_module].server = v.toObject().value("server").toString();
            t.module[t.jml_module].file = v.toObject().value("file").toString();
            if (v.toObject().value("web_client").toString().toInt()) {
                t.module[t.jml_module].web_client = true;
            } else {
                t.module[t.jml_module].web_client = false;
            }
            t.module[t.jml_module].interval = v.toObject().value("interval").toString().toInt();

            if (!v.toObject().value("gsm").toArray().isEmpty()) {
                t.module[t.jml_module].jml_gsm = 0;
                foreach (const QJsonValue & vGSM, v.toObject().value("gsm").toArray()) {
                    t.module[t.jml_module].gsm[t.module[t.jml_module].jml_gsm].opt =
                            vGSM.toObject().value("operator").toString();
                    t.module[t.jml_module].gsm[t.module[t.jml_module].jml_gsm].device_name =
                            vGSM.toObject().value("device_name").toString();
                    if (vGSM.toObject().value("status").toString().toInt()) {
                        t.module[t.jml_module].gsm[t.module[t.jml_module].jml_gsm].status = true;
                    } else {
                        t.module[t.jml_module].gsm[t.module[t.jml_module].jml_gsm].status = false;
                    }
                    t.module[t.jml_module].gsm[t.module[t.jml_module].jml_gsm].communication =
                            vGSM.toObject().value("communication").toString();
                    t.module[t.jml_module].gsm[t.module[t.jml_module].jml_gsm].number =
                            vGSM.toObject().value("number").toString();
                    t.module[t.jml_module].gsm[t.module[t.jml_module].jml_gsm].apn =
                            vGSM.toObject().value("apn").toString();
                    t.module[t.jml_module].gsm[t.module[t.jml_module].jml_gsm].username =
                            vGSM.toObject().value("username").toString();
                    t.module[t.jml_module].gsm[t.module[t.jml_module].jml_gsm].password =
                            vGSM.toObject().value("password").toString();

                    t.module[t.jml_module].jml_gsm++;
                }
            }

            t.jml_module++;
        }
        t.lastRequest = "env";
    } else if (!data_jsonArray.isEmpty()) {
        for (int i = 0; i < t.jml_module; i++) {
            t.module[i].d.regData.clear();
            t.module[i].d.valData.clear();
        }
        foreach (const QJsonValue & v, data_jsonArray) {
            for (int i = 0; i < t.jml_module; i++) {
                if (v.toObject().value("id").toString().toInt() == t.module[i].id) {
                    t.module[i].d.regData.append(v.toObject().value("register").toString());
                    t.module[i].d.valData.append(v.toObject().value("value").toString());
                    break;
                }
            }
        }
        t.lastRequest = "data";
    }
    return t;
}
