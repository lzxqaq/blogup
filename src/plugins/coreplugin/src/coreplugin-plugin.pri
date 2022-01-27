INCLUDEPATH += $$PWD

DISTFILES += Core.json

FORMS += \
    $$PWD/mainwindow.ui

HEADERS += \
    $$PWD/coreplugin.h \
    $$PWD/dockededitortitlebar.h \
    $$PWD/dockmanager.h \
    $$PWD/mainwindow.h \
    $$PWD/fileexplorerwidget.h \
    $$PWD/editormanager/customedit.h \
    $$PWD/editormanager/editormanager.h

SOURCES += \
    $$PWD/coreplugin.cpp \
    $$PWD/dockmanager.cpp \
    $$PWD/mainwindow.cpp \
    $$PWD/fileexplorerwidget.cpp \
    $$PWD/editormanager/customedit.cpp \
    $$PWD/editormanager/editormanager.cpp

FORMS += \
    $$PWD/fileexplorerwidget.ui
