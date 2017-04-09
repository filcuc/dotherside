#include "DOtherSide/Widgets/Widgets.h"

#include <QApplication>
#include <QVector>

void dos_qapplication_create()
{
    static int argc = 1;
    static char empty[1] = {0};
    static char *argv[] = {empty};

    qRegisterMetaType<QVector<int>>();

    new QApplication(argc, argv);
}

void dos_qapplication_delete()
{
    delete qApp;
}

void dos_qapplication_exec()
{
    qApp->exec();
}

void dos_qapplication_quit()
{
    qApp->quit();
}
