#include "DOtherSide/Gui/Gui.h"

#include <QGuiApplication>
#include <QVector>

void dos_qguiapplication_create()
{
    static int argc = 1;
    static char empty[1] = {0};
    static char *argv[] = {empty};

    qRegisterMetaType<QVector<int>>();

    new QGuiApplication(argc, argv);
}

void dos_qguiapplication_delete()
{
    delete qGuiApp;
}

void dos_qguiapplication_exec()
{
    qGuiApp->exec();
}

void dos_qguiapplication_quit()
{
    qGuiApp->quit();
}
