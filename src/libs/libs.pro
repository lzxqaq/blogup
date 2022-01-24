include(../../blogup.pri)

TEMPLATE  = subdirs

SUBDIRS =   \
    extensionsystem \
    pluginmanager


for(l, SUBDIRS) {
    QTC_LIB_DEPENDS =
    include($$l/$${l}_dependencies.pri)
    lv = $${l}.depends
    $$lv = $$QTC_LIB_DEPENDS
}
