include(../../blogup.pri)

TEMPLATE = app
TARGET = blogup
DESTDIR = $$IDE_APP_PATH
QT       += core gui

SHARED_PATH = $$PWD/../../shared/

SOURCES += \
    main.cpp \
#    mainwindow.cpp \
#    statusdialog.cpp

RESOURCES += \
    app.qrc

HEADERS += \
#    mainwindow.h \
#    statusdialog.h \
#    ui_mainwindow.h \
#    ui_statusdialog.h



target.path = $$INSTALL_APP_PATH
INSTALLS += target

include(../rpath.pri)
