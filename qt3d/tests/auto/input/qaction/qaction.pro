TEMPLATE = app

TARGET = tst_qaction

QT += core-private 3dcore 3dcore-private 3dinput 3dinput-private testlib

CONFIG += testcase

SOURCES += tst_qaction.cpp

include(../../render/commons/commons.pri)
