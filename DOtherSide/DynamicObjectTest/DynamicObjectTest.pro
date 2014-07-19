#-------------------------------------------------
#
# Project created by QtCreator 2014-07-13T10:03:29
#
#-------------------------------------------------

QT       += testlib

QT       -= gui


TARGET = tst_dynamicobjecttest
CONFIG   += console c++11
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_dynamicobjecttest.cpp \
    Mockprinter.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

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

HEADERS += \
    Mockprinter.h
