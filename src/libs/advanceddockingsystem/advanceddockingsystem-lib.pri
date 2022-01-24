QT += core gui widgets

windows {
        # MinGW
        *-g++* {
                QMAKE_CXXFLAGS += -Wall -Wextra -pedantic
        }
        # MSVC
        *-msvc* {
                QMAKE_CXXFLAGS += /utf-8
        }
}

DEFINES += ADS_SHARED_EXPORT

RESOURCES += $$PWD/ads.qrc

HEADERS += \
    $$PWD/ads_globals.h \
    $$PWD/DockAreaWidget.h \
    $$PWD/DockAreaTabBar.h \
    $$PWD/DockContainerWidget.h \
    $$PWD/DockManager.h \
    $$PWD/DockWidget.h \
    $$PWD/DockWidgetTab.h \
    $$PWD/DockingStateReader.h \
    $$PWD/FloatingDockContainer.h \
    $$PWD/FloatingDragPreview.h \
    $$PWD/DockOverlay.h \
    $$PWD/DockSplitter.h \
    $$PWD/DockAreaTitleBar_p.h \
    $$PWD/DockAreaTitleBar.h \
    $$PWD/ElidingLabel.h \
    $$PWD/IconProvider.h \
    $$PWD/DockComponentsFactory.h  \
    $$PWD/DockFocusController.h


SOURCES += \
        $$PWD/ads_globals.cpp \
        $$PWD/DockAreaWidget.cpp \
        $$PWD/DockAreaTabBar.cpp \
        $$PWD/DockContainerWidget.cpp \
        $$PWD/DockManager.cpp \
        $$PWD/DockWidget.cpp \
        $$PWD/DockingStateReader.cpp \
        $$PWD/DockWidgetTab.cpp \
        $$PWD/FloatingDockContainer.cpp \
        $$PWD/FloatingDragPreview.cpp \
        $$PWD/DockOverlay.cpp \
        $$PWD/DockSplitter.cpp \
        $$PWD/DockAreaTitleBar.cpp \
        $$PWD/ElidingLabel.cpp \
        $$PWD/IconProvider.cpp \
        $$PWD/DockComponentsFactory.cpp \
        $$PWD/DockFocusController.cpp


unix:!macx {
        HEADERS += $$PWD/linux/FloatingWidgetTitleBar.h
        SOURCES += $$PWD/linux/FloatingWidgetTitleBar.cpp
        INCLUDEPATH += $$PWD/linux
        QT += x11extras
        LIBS += -lxcb
}

INCLUDEPATH += $$PWD/
