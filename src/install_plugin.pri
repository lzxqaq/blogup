win32 {
    _srcDir = $${IDE_PLUGIN_PATH}/$${TARGET}*.dll
    _destDir = $${IDE_BIN_PATH}/plugins/$${TARGET}*.dll
    _srcDir ~= s,/,\\,g
    _destDir ~= s,/,\\,g
    QMAKE_POST_LINK += xcopy /D/Y $$quote($$_srcDir) $$quote($$_destDir)
} else:linux* {
    _srcDir = $${IDE_PLUGIN_PATH}/*$${TARGET}*.so
    _destDir = $${IDE_BIN_PATH}/plugins/
    QMAKE_POST_LINK += mkdir -p $$quote($$_destDir) && cp -f -r $$quote($$_srcDir) $$quote($$_destDir)
}
