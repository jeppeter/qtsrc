TARGET = tst_qapplicationargumentparser
CONFIG += testcase
SOURCES += tst_qapplicationargumentparser.cpp                           \
           ../../../tools/xmlpatterns/qapplicationargument.cpp          \
           ../../../tools/xmlpatterns/qapplicationargumentparser.cpp
QT = core testlib
INCLUDEPATH += ../../../tools/xmlpatterns/
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0
