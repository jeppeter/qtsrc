!include( ../examples.pri ) {
    error( "Couldn't find the examples.pri file!" )
}

QT += 3dcore 3drender 3dinput 3dquick qml quick

HEADERS += \

SOURCES += \
    main.cpp

OTHER_FILES += \
    main.qml \
    Wine.qml

RESOURCES += \
    gltf_example.qrc \
    ../exampleresources/gltf.qrc \
