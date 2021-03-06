QT += core network
CONFIG += c++11

DEFINES += SINGLEAPP_SHARED

HEADERS += \
    $$PWD/SingleApplication \
    $$PWD/singleapplication.h \
    $$PWD/singleapplication_p.h

SOURCES += \
    $$PWD/singleapplication.cpp \
    $$PWD/singleapplication_p.cpp

INCLUDEPATH += $$PWD

win32 {
    msvc:LIBS += Advapi32.lib
    gcc:LIBS += -ladvapi32
}

