CONFIG += testcase
TARGET = tst_qaudiorecorder

QT += multimedia-private testlib

SOURCES += tst_qaudiorecorder.cpp

include (../qmultimedia_common/mock.pri)
include (../qmultimedia_common/mockrecorder.pri)

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0
