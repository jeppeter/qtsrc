#! [0]
TEMPLATE      = lib
CONFIG       += plugin
QT           += widgets
INCLUDEPATH  += ../../app
HEADERS       = extrafiltersplugin.h
SOURCES       = extrafiltersplugin.cpp
TARGET        = $$qtLibraryTarget(pnp_extrafilters)
DESTDIR       = ../../plugins

#! [0]
# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/tools/plugandpaint/plugins
INSTALLS += target

CONFIG += install_ok  # Do not cargo-cult this!
