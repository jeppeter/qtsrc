QT  += core gui widgets

HEADERS = $$PWD/glwindow.h \
          $$PWD/../hellogl2/logo.h \
          $$PWD/mainwindow.h \
          $$PWD/window.h \
          $$PWD/glwidget.h \
          $$PWD/logo.h

SOURCES = $$PWD/glwindow.cpp \
          $$PWD/main.cpp \
          $$PWD/../hellogl2/logo.cpp \
          $$PWD/mainwindow.cpp \
          $$PWD/window.cpp \
          $$PWD/glwidget.cpp \
          $$PWD/logo.cpp

RESOURCES += hellogles3.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/opengl/hellogles3
INSTALLS += target
