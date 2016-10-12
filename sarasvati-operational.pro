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
        model/mdi.cpp \
    view/form_gmap.cpp \
    view/form_module.cpp \
    control/work.cpp \
    model/qcustomplot.cpp \
    model/mgraph.cpp

HEADERS  += view/mainwindow.h \
        view/login.h \
        util/global.h \
        model/mtreeview.h \
        model/mdi.h \
    view/form_gmap.h \
    view/form_module.h \
    control/work.h \
    model/qcustomplot.h \
    model/mgraph.h

FORMS    += view/mainwindow.ui \
        view/login.ui \
    view/form_gmap.ui \
    view/form_module.ui

RESOURCES += \
        sarasvati.qrc
