#-------------------------------------------------
#
# Project created by QtCreator 2014-07-13T10:05:38
#
#-------------------------------------------------

QT       -= gui

TARGET = StaticTestLib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += statictestlib.cpp

HEADERS += statictestlib.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
