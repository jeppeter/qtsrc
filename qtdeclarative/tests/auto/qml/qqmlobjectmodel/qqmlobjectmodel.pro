CONFIG += testcase
TARGET = tst_qqmlobjectmodel
osx:CONFIG -= app_bundle

SOURCES += tst_qqmlobjectmodel.cpp

CONFIG += parallel_test

QT += qml testlib
QT += core-private qml-private
