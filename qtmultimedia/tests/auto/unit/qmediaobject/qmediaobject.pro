CONFIG += testcase
TARGET = tst_qmediaobject
QT += multimedia-private testlib

include (../qmultimedia_common/mockrecorder.pri)
include (../qmultimedia_common/mock.pri)

SOURCES += tst_qmediaobject.cpp
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0
