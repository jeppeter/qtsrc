QT       += multimedia testlib
QT       -= gui

TARGET = tst_qaudiobuffer
CONFIG   += testcase
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += tst_qaudiobuffer.cpp
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0
