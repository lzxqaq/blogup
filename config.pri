!isEmpty(CONFIG_PRI_INCLUDED):error("config.pri already included")
BLOGUP_PRI_INCLUDED = 1

isEmpty(QTCANPOOL_DIR):             QTCANPOOL_DIR = $$PWD

# config branding and variables
isEmpty(BLOGUP_VERSION):         BLOGUP_VERSION = 1.1.0
isEmpty(BLOGUP_COMPAT_VERSION):  BLOGUP_COMPAT_VERSION = 1.1.0
isEmpty(BLOGUP_DISPLAY_VERSION): BLOGUP_DISPLAY_VERSION = 1.1.0
isEmpty(BLOGUP_COPYRIGHT_YEAR):  BLOGUP_COPYRIGHT_YEAR = 2021
isEmpty(BINARY_ARTIFACTS_BRANCH):   BINARY_ARTIFACTS_BRANCH = 1.1

isEmpty(IDE_DISPLAY_NAME):          IDE_DISPLAY_NAME = carmes
isEmpty(IDE_ID):                    IDE_ID = carmes
isEmpty(IDE_CASED_ID):              IDE_CASED_ID = Carmes

isEmpty(PRODUCT_BUNDLE_IDENTIFIER): PRODUCT_BUNDLE_IDENTIFIER = org.qt-project.$$IDE_ID


isEmpty(BLOGUP_DIR):             BLOGUP_DIR = $$PWD
isEmpty(BLOGUP_OUT_PWD):         BLOGUP_OUT_PWD = $$OUT_PWD
isEmpty(BLOGUP_PRO_FILE_PWD):    BLOGUP_PRO_FILE_PWD = $$_PRO_FILE_PWD_
isEmpty(BLOGUP_PRO_FILE):        BLOGUP_PRO_FILE = $$_PRO_FILE_

#message("_PRO_FILE_=")
#message($$_PRO_FILE_)

isEmpty(IDE_LIBRARY_BASENAME) {
    IDE_LIBRARY_BASENAME = lib
}

# config IDE_SOURCE_TREE
IDE_SOURCE_TREE = $$BLOGUP_DIR

isEmpty(IDE_BUILD_TREE) {
    sub_dir = $$BLOGUP_PRO_FILE_PWD
    sub_dir ~= s,^$$re_escape($$IDE_SOURCE_TREE),,
    greaterThan(QT_MAJOR_VERSION, 4) {
        IDE_BUILD_TREE = $$clean_path($$BLOGUP_OUT_PWD) # qt5
    } else {
        IDE_BUILD_TREE = $$BLOGUP_OUT_PWD  # qt4
    }
    IDE_BUILD_TREE ~= s,$$re_escape($$sub_dir)$,,
}


IDE_APP_PATH = $$IDE_BUILD_TREE/bin
osx {
    IDE_APP_TARGET   = "$$IDE_DISPLAY_NAME"

    # check if IDE_BUILD_TREE is actually an existing Qt Canpool.app,
    # for building against a binary package
    exists($$IDE_BUILD_TREE/Contents/MacOS/$$IDE_APP_TARGET): IDE_APP_BUNDLE = $$IDE_BUILD_TREE
    else: IDE_APP_BUNDLE = $$IDE_APP_PATH/$${IDE_APP_TARGET}.app

    # set output path if not set manually
    isEmpty(IDE_OUTPUT_PATH): IDE_OUTPUT_PATH = $$IDE_APP_BUNDLE/Contents

    IDE_LIBRARY_PATH = $$IDE_OUTPUT_PATH/Frameworks
    IDE_PLUGIN_PATH  = $$IDE_OUTPUT_PATH/PlugIns
    IDE_LIBEXEC_PATH = $$IDE_OUTPUT_PATH/Resources/libexec
    IDE_DATA_PATH    = $$IDE_OUTPUT_PATH/Resources
    IDE_DOC_PATH     = $$IDE_DATA_PATH/doc
    IDE_BIN_PATH     = $$IDE_OUTPUT_PATH/MacOS
    copydata = 1

    LINK_LIBRARY_PATH = $$IDE_APP_BUNDLE/Contents/Frameworks
    LINK_PLUGIN_PATH  = $$IDE_APP_BUNDLE/Contents/PlugIns

    INSTALL_LIBRARY_PATH = $$QTC_PREFIX/$${IDE_APP_TARGET}.app/Contents/Frameworks
    INSTALL_PLUGIN_PATH  = $$QTC_PREFIX/$${IDE_APP_TARGET}.app/Contents/PlugIns
    INSTALL_LIBEXEC_PATH = $$QTC_PREFIX/$${IDE_APP_TARGET}.app/Contents/Resources/libexec
    INSTALL_DATA_PATH    = $$QTC_PREFIX/$${IDE_APP_TARGET}.app/Contents/Resources
    INSTALL_DOC_PATH     = $$INSTALL_DATA_PATH/doc
    INSTALL_BIN_PATH     = $$QTC_PREFIX/$${IDE_APP_TARGET}.app/Contents/MacOS
    INSTALL_APP_PATH     = $$QTC_PREFIX/
} else {
    contains(TEMPLATE, vc.*):vcproj = 1
    IDE_APP_TARGET   = $$IDE_ID

    # target output path if not set manually
    isEmpty(IDE_OUTPUT_PATH): IDE_OUTPUT_PATH = $$IDE_BUILD_TREE

    IDE_LIBRARY_PATH = $$IDE_OUTPUT_PATH/$$IDE_LIBRARY_BASENAME/blogup
    IDE_PLUGIN_PATH  = $$IDE_LIBRARY_PATH/plugins
    IDE_DATA_PATH    = $$IDE_OUTPUT_PATH/share/blogup
    IDE_DOC_PATH     = $$IDE_OUTPUT_PATH/share/doc/blogup
    IDE_BIN_PATH     = $$IDE_OUTPUT_PATH/bin
    win32: \
        IDE_LIBEXEC_PATH = $$IDE_OUTPUT_PATH/bin
    else: \
        IDE_LIBEXEC_PATH = $$IDE_OUTPUT_PATH/libexec/blogup
    !isEqual(IDE_SOURCE_TREE, $$IDE_OUTPUT_PATH):copydata = 1

    LINK_LIBRARY_PATH = $$IDE_BUILD_TREE/$$IDE_LIBRARY_BASENAME/blogup
    LINK_PLUGIN_PATH  = $$LINK_LIBRARY_PATH/plugins

    INSTALL_LIBRARY_PATH = $$QTC_PREFIX/$$IDE_LIBRARY_BASENAME/blogup
    INSTALL_PLUGIN_PATH  = $$INSTALL_LIBRARY_PATH/plugins
    win32: \
        INSTALL_LIBEXEC_PATH = $$QTC_PREFIX/bin
    else: \
        INSTALL_LIBEXEC_PATH = $$QTC_PREFIX/libexec/blogup
    INSTALL_DATA_PATH    = $$QTC_PREFIX/share/blogup
    INSTALL_DOC_PATH     = $$QTC_PREFIX/share/doc/blogup
    INSTALL_BIN_PATH     = $$QTC_PREFIX/bin
    INSTALL_APP_PATH     = $$QTC_PREFIX/bin
}

msvc{
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
}
