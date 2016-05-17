// This file implements a basic QML Hello World application that runs an embedded qml file.
// ref: https://doc.qt.io/qt-5/qml-tutorial1.html

#include "DOtherSide/DOtherSide.h"

int main(int argc, char* argv[])
{
   dos_qapplication_create();
   DosQQmlApplicationEngine *engine = dos_qqmlapplicationengine_create();
   dos_qqmlapplicationengine_load_url(engine, dos_qurl_create("qrc:///hello.qml", 1)); // Strict mode

   dos_qapplication_exec();

   dos_qqmlapplicationengine_delete(engine);
   dos_qapplication_delete();

   return 0;
}
