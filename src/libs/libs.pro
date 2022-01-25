include(../../blogup.pri)

TEMPLATE  = subdirs

SUBDIRS =   \
    advanceddockingsystem \
    qsimpleupdater \
    singleapplication \
    scintilla \
    uchardet \
    extensionsystem


for(l, SUBDIRS) {
    QTC_LIB_DEPENDS =
    include($$l/$${l}_dependencies.pri)
    lv = $${l}.depends
    $$lv = $$QTC_LIB_DEPENDS
}
