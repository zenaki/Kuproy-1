#include "view/login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qApp->setStyleSheet( "QStatusBar::item { border: 0px}" ) ;
    Login l;
    l.show();
    l.setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            l.size(),
            qApp->desktop()->availableGeometry()
        )
    );

    return a.exec();
}
