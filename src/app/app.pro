include(../../blogup.pri)

include(../3plibs/advanceddockingsystem/advanceddockingsystem-include.pri)
include(../3plibs/qsimpleupdater/qsimpleupdater-include.pri)
include(../3plibs/singleapplication/singleapplication-include.pri)
include(../3plibs/scintilla/scintilla-include.pri)

include(../libs/pluginmanager/pluginmanager-include.pri)
TEMPLATE = app
TARGET = blogup
DESTDIR = $$IDE_APP_PATH
QT       += core gui

SHARED_PATH = $$PWD/../../shared/

SOURCES += \
    main.cpp \
    mainwindow.cpp

RESOURCES += \
    app.qrc

HEADERS += \
    mainwindow.h

LIBS *= \
    -l$$qtLibraryName(AdvancedDockingSystem) \
    -l$$qtLibraryName(QSimpleUpdater) \
    -l$$qtLibraryName(SingleApplication) \
    -l$$qtLibraryName(Scintilla) \
    -l$$qtLibraryName(PluginManager) \

target.path = $$INSTALL_APP_PATH
INSTALLS += target

include(../rpath.pri)

FORMS += \
    mainwindow.ui
