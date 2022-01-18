include(../../blogup.pri)

TEMPLATE = app
TARGET = blogup
DESTDIR = $$IDE_APP_PATH
QT       += core gui

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    statusdialog.cpp

RESOURCES += \
    app.qrc

HEADERS += \
    mainwindow.h \
    statusdialog.h \
    ui_mainwindow.h \
    ui_statusdialog.h



target.path = $$INSTALL_APP_PATH
INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../3plibs/advanceddockingsystem/release/ -lqtadvanceddocking
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../3plibs/advanceddockingsystem/debug/ -lqtadvanceddocking
else:unix: LIBS += -L$$OUT_PWD/../3plibs/advanceddockingsystem/ -lqtadvanceddocking

INCLUDEPATH += $$PWD/../3plibs/advanceddockingsystem
DEPENDPATH += $$PWD/../3plibs/advanceddockingsystem
