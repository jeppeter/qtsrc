CONFIG += testcase
CONFIG += parallel_test
win32:testcase.timeout = 1800   # test runtime varies greatly on Windows, QTBUG-26006
TARGET = tst_languagechange
QT += widgets core-private gui-private testlib
SOURCES += tst_languagechange.cpp
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0
