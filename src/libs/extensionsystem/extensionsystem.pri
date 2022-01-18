QT += core gui

DEFINES += EXTENSIONSYSTEM_LIBRARY

HEADERS += \
    $$PWD/extensionsystem_global.h \
    $$PWD/iplugin.h \
    $$PWD/iplugin_p.h \
    $$PWD/pluginmanager.h \
    $$PWD/pluginmanager_p.h \
    $$PWD/pluginspec.h \
    $$PWD/pluginspec_p.h


SOURCES += \
    $$PWD/iplugin.cpp \
    $$PWD/iplugin_p.cpp \
    $$PWD/pluginmanager.cpp \
    $$PWD/pluginmanager_p.cpp \
    $$PWD/pluginspec.cpp \
    $$PWD/pluginspec_p.cpp

