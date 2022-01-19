include(../../blogup.pri)

include(../3plibs/advanceddockingsystem/advanceddockingsystem-lib.pri)
include(../3plibs/qsimpleupdater/qsimpleupdater.pri)
include(../3plibs/singleapplication/singleapplication.pri)

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

LIBS *= -l$$qtLibraryName(AdvancedDockingSystem) -l$$qtLibraryName(QSimpleUpdater)  -l$$qtLibraryName(SingleApplication)

target.path = $$INSTALL_APP_PATH
INSTALLS += target

include(../rpath.pri)

FORMS += \
    mainwindow.ui
