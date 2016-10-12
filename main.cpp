#include "view/login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qApp->setStyleSheet( "QStatusBar::item { border: 0px}" ) ;
    Login l;
    l.show();

    return a.exec();
}
