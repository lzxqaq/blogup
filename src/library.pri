isEmpty(QTLIBRARY_PRO_FILE_PWD):    QTLIBRARY_PRO_FILE_PWD = $$_PRO_FILE_PWD_


include($$replace(QTLIBRARY_PRO_FILE_PWD, ([^/]+$), \\1/\\1_dependencies.pri))
TARGET = $$QTC_LIB_NAME

include(../blogup.pri)

# use precompiled header for libraries by default
#isEmpty(PRECOMPILED_HEADER):PRECOMPILED_HEADER = $$PWD/shared/blogup_pch.h

win32 {
    DLLDESTDIR = $$IDE_APP_PATH
}

DESTDIR = $$IDE_LIBRARY_PATH
osx {
    QMAKE_LFLAGS_SONAME = -Wl,-install_name,@rpath/
    QMAKE_LFLAGS += -compatibility_version $$BLOGUP_COMPAT_VERSION
}

RPATH_BASE = $$IDE_LIBRARY_PATH
include(rpath_lib.pri)


TARGET = $$qtLibraryTargetName($$TARGET)


TEMPLATE = lib
CONFIG += shared dll

contains(QT_CONFIG, reduce_exports):CONFIG += hide_symbols

include(install_lib.pri)

