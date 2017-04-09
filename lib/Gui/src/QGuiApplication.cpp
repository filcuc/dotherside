#include "DOtherSide/Gui/Gui.h"

#include <QGuiApplication>

void dos_qguiapplication_create()
{
    static int argc = 1;
    static char empty[1] = {0};
    static char *argv[] = {empty};

    register_meta_types();

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
