TEMPLATE = app

QT += qml quick

CONFIG += c++11

SOURCES += main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DynamicQObject/release/ -lDynamicQObject
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DynamicQObject/debug/ -lDynamicQObject
else:unix: LIBS += -L$$OUT_PWD/../DynamicQObject/ -lDynamicQObject

INCLUDEPATH += $$PWD/../DynamicQObject
DEPENDPATH += $$PWD/../DynamicQObject

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../DynamicQObject/release/libDynamicQObject.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../DynamicQObject/debug/libDynamicQObject.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../DynamicQObject/release/DynamicQObject.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../DynamicQObject/debug/DynamicQObject.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../DynamicQObject/libDynamicQObject.a

HEADERS +=

