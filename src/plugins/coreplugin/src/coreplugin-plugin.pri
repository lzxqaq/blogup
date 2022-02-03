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
    $$PWD/dialog/newpostdialog.h \
    $$PWD/dialog/newsitedialog.h \
    $$PWD/dockededitortitlebar.h \
    $$PWD/dockmanager.h \
    $$PWD/icontext.h \
    $$PWD/mainwindow.h \
    $$PWD/fileexplorerwidget.h \
    $$PWD/editormanager/customedit.h \
    $$PWD/editormanager/editormanager.h \
    $$PWD/remote/hugo.h \
    $$PWD/remote/process.h

SOURCES += \
    $$PWD/actionmanager/actioncontainer.cpp \
    $$PWD/actionmanager/actioncontainer_p.cpp \
    $$PWD/actionmanager/actionmanager.cpp \
    $$PWD/actionmanager/actionmanager_p.cpp \
    $$PWD/actionmanager/command.cpp \
    $$PWD/coreplugin.cpp \
    $$PWD/dialog/newpostdialog.cpp \
    $$PWD/dialog/newsitedialog.cpp \
    $$PWD/dockmanager.cpp \
    $$PWD/mainwindow.cpp \
    $$PWD/fileexplorerwidget.cpp \
    $$PWD/editormanager/customedit.cpp \
    $$PWD/editormanager/editormanager.cpp \
    $$PWD/remote/hugo.cpp \
    $$PWD/remote/process.cpp

FORMS +=
