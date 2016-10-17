#-------------------------------------------------
#
# Project created by QtCreator 2016-09-27T15:56:59
#
#-------------------------------------------------

QT       += core gui widgets webenginewidgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = sarasvati-operational
TEMPLATE = app


SOURCES += main.cpp\
        view/mainwindow.cpp \
        view/login.cpp \
        model/mtreeview.cpp \
    control/work.cpp \
    model/qcustomplot.cpp \
    model/mgraph.cpp

HEADERS  += view/mainwindow.h \
        view/login.h \
        util/global.h \
        model/mtreeview.h \
    control/work.h \
    model/qcustomplot.h \
    model/mgraph.h

FORMS    += view/mainwindow.ui \
        view/login.ui

RESOURCES += \
        sarasvati.qrc
