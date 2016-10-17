#ifndef MWEB_H
#define MWEB_H

#include <QObject>

#include "util/global.h"

class mWeb : public QObject
{
    Q_OBJECT
public:
    explicit mWeb(QObject *parent = 0);

    void setupWeb(QWidget *parent, QWebEngineView *webGmap);
    void setLatLng(QWebEngineView *webGmap, QPlainTextEdit *pte_log, struct tree t, QLabel *lbl_GIF, QLabel *lbl_loading, QTimer *tmr);
    void setMap(QWidget *parent, QWebEngineView *webGmap, QWebEngineView *webGraph, QPlainTextEdit *pte_log);
signals:

public slots:
};

#endif // MWEB_H
