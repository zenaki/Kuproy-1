#include "view/login.h"
//#include "view/form_gmap.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login l;
    l.show();
//    Form_Gmap g;
//    g.show();

    return a.exec();
}
