#-------------------------------------------------
#
# Project created by QtCreator 2014-02-01T19:04:39
#
#-------------------------------------------------

QT       += quick

CONFIG += c++11

QMAKE_CXXFLAGS += "-O1 -fpic"

TARGET = DOtherSide
TEMPLATE = lib

DEFINES += DOTHERSIDE_LIBRARY

SOURCES += \
    DOtherSide.cpp

HEADERS += \
    DOtherSide.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

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
