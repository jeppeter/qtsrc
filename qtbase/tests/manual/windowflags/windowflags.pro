HEADERS       = controllerwindow.h \
                previewwindow.h \
                controls.h

SOURCES       = controllerwindow.cpp \
                previewwindow.cpp \
                main.cpp \
                controls.cpp

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0
