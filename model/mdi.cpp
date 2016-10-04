#include "mdi.h"

mdi::mdi()
{

}

void mdi::new_Gmap_Window(QWidget *parent, QMdiArea *mdiArea, QString title, QString key)
{
    Form_Gmap *fGmap;

    fGmap = new Form_Gmap(parent, key);
    fGmap->setModal(true);
    fGmap->setWindowTitle(title);
    fGmap->setMaximumSize(mdiArea->maximumSize());
    fGmap->setGeometry(0,0,mdiArea->maximumWidth(),mdiArea->maximumHeight());

    mdiArea->addSubWindow(fGmap, 0);
    fGmap->exec();
//    fGmap->setFocus();
}

void mdi::new_Module_Window(QWidget *parent, QMdiArea *mdiArea, QString title, QString key)
{
    Form_Module *fModule;

    fModule = new Form_Module(parent, key);
    fModule->setModal(true);
    fModule->setWindowTitle(title);
//    fModule->setFixedWidth(800);
//    fModule->setFixedHeight(600);
    fModule->setMaximumSize(mdiArea->maximumSize());
    fModule->setGeometry(0,0,mdiArea->maximumWidth(),mdiArea->maximumHeight());

    mdiArea->addSubWindow(fModule, 0);
    fModule->exec();
//    fModule->setFocus();
}
