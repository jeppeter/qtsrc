CONFIG += testcase
TARGET = tst_qdir
QT = core core-private testlib
SOURCES = tst_qdir.cpp
RESOURCES += qdir.qrc

TESTDATA += testdir testData searchdir resources entrylist types tst_qdir.cpp

contains(CONFIG, builtin_testdata): DEFINES += BUILTIN_TESTDATA

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0

android:!android-no-sdk {
    RESOURCES += android_testdata.qrc
}
