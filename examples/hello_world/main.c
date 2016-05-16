// This file implements a basic QML Hello World application
// ref: https://doc.qt.io/qt-5/qml-tutorial1.html

#include "DOtherSide/DOtherSide.h"

static const char *app =
"import QtQuick 2.2\n"
"import QtQuick.Controls 1.4\n"
"\n"
"ApplicationWindow {\n"
"    id: app\n"
"    title: \"Hello World Example\"\n"
"    width: 300; height: 100\n"
"    color: \"lightgray\"\n"
"    Component.onCompleted: visible = true\n"
"\n"
"    Text {\n"
"        text: \"Hello world!\"\n"
"        y: 30\n"
"        anchors.horizontalCenter: app.contentItem.horizontalCenter\n"
"        font.pointSize: 24; font.bold: true\n"
"    }\n"
"}";

int main(int argc, char* argv[])
{
   dos_qapplication_create();
   DosQQmlApplicationEngine *engine = dos_qqmlapplicationengine_create();
   dos_qqmlapplicationengine_load_data(engine, app);

   dos_qapplication_exec();

   dos_qqmlapplicationengine_delete(engine);
   dos_qapplication_delete();

   return 0;
}
