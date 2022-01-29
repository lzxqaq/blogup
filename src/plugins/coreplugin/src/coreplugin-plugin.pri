INCLUDEPATH += $$PWD

DISTFILES += Core.json

DEFINES += CORE_LIBRARY

FORMS += \
    $$PWD/mainwindow.ui \
    $$PWD/newpostdialog.ui \
    $$PWD/newsitedialog.ui

HEADERS += \
    $$PWD/actionmanager/actioncontainer.h \
    $$PWD/actionmanager/actioncontainer_p.h \
    $$PWD/actionmanager/actionmanager.h \
    $$PWD/actionmanager/actionmanager_p.h \
    $$PWD/actionmanager/command.h \
    $$PWD/actionmanager/command_p.h \
    $$PWD/actionmanager/commandbutton.h \
    $$PWD/actionmanager/commandmappings.h \
    $$PWD/actionmanager/commandsfile.h \
    $$PWD/core_global.h \
    $$PWD/coreconstants.h \
    $$PWD/coreplugin.h \
    $$PWD/dockededitortitlebar.h \
    $$PWD/dockmanager.h \
    $$PWD/icontext.h \
    $$PWD/mainwindow.h \
    $$PWD/fileexplorerwidget.h \
    $$PWD/editormanager/customedit.h \
    $$PWD/editormanager/editormanager.h

SOURCES += \
    $$PWD/actionmanager/actioncontainer.cpp \
    $$PWD/actionmanager/actionmanager.cpp \
    $$PWD/actionmanager/command.cpp \
    $$PWD/actionmanager/commandbutton.cpp \
    $$PWD/actionmanager/commandmappings.cpp \
    $$PWD/actionmanager/commandsfile.cpp \
    $$PWD/coreplugin.cpp \
    $$PWD/dockmanager.cpp \
    $$PWD/mainwindow.cpp \
    $$PWD/fileexplorerwidget.cpp \
    $$PWD/editormanager/customedit.cpp \
    $$PWD/editormanager/editormanager.cpp

FORMS +=
