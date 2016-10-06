#ifndef MDI_H
#define MDI_H

#include "util/global.h"
#include "view/form_gmap.h"
#include "view/form_module.h"

class mdi
{
public:
    mdi();

    void new_Gmap_Window(QWidget *parent, QMdiArea *mdiArea, QString title, QString ReqLatLng);
    void new_Module_Window(QWidget *parent, QMdiArea *mdiArea, QString title, QString key, int id);
};

#endif // MDI_H
