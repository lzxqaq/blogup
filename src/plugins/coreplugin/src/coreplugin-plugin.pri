INCLUDEPATH += $$PWD

DISTFILES += Core.json

FORMS += \
    $$PWD/mainwindow.ui

HEADERS += \
    $$PWD/coreplugin.h \
    $$PWD/mainwindow.h \
    $$PWD/editormanager/customedit.h \
    $$PWD/editormanager/editormanager.h

SOURCES += \
    $$PWD/coreplugin.cpp \
    $$PWD/mainwindow.cpp \
    $$PWD/editormanager/customedit.cpp \
    $$PWD/editormanager/editormanager.cpp

