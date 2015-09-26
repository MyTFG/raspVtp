TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    mytfgapi.cpp \
    parser.cpp

LIBS += -lcurl -ljson_linux-gcc-4.9.2_libmt

TARGET = curl

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    mytfgapi.h \
    parser.h
