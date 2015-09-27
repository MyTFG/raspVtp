TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    mytfgapi.cpp \
    parser.cpp \
    plan.cpp \
    vplanscroller.cpp

LIBS += -lcurl -ljson_linux-gcc-4.9.2_libmt

TARGET = raspvtp

RESOURCES += qml.qrc

CONFIG += c++11

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    mytfgapi.h \
    parser.h \
    plan.h \
    vplanscroller.h
