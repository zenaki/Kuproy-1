#ifndef MWEB_H
#define MWEB_H

#include <QObject>

#include "util/global.h"

class mWeb : public QObject
{
    Q_OBJECT
public:
    explicit mWeb(QObject *parent = 0);

    void setupWeb(QWidget *parent, QWebEngineView *webGmap, QWebEngineView *webGraph);
    void setLatLng(QWebEngineView *webGmap, QPlainTextEdit *pte_log, struct tree t, QLabel *lbl_GIF, QLabel *lbl_loading);
    void setMap(QWidget *parent, QWebEngineView *webGmap, QWebEngineView *webGraph, QWebEngineView *webHMI, QPlainTextEdit *pte_log);

    QTimer *tmr;

public slots:
    void setGraph(QWebEngineView *webGraph, QPlainTextEdit *pte_log, int mX, int mY);
};

#endif // MWEB_H
