TEMPLATE = app
TARGET = tst_bench_qfileinfo

QT -= gui
QT += core-private testlib

CONFIG += release

SOURCES += main.cpp
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0
