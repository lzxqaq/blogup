win32 {
    #新增
    DLLDESTDIR = $$IDE_APP_PATH
    dlltarget.path = $$INSTALL_BIN_PATH
    INSTALLS += dlltarget
    #
} else:linux* {
    _srcDir = $${IDE_LIBRARY_PATH}/*$${TARGET}*.so*
    _destDir = $${IDE_BIN_PATH}/lib/
    QMAKE_POST_LINK += mkdir -p $$quote($$_destDir) && cp -f -r $$quote($$_srcDir) $$quote($$_destDir)
} else {
    target.path = $$INSTALL_LIBRARY_PATH
    INSTALLS += target
}


