TEMPLATE  = subdirs
CONFIG   += ordered

SUBDIRS = \
    advanceddockingsystem \

QTC_LIB_DEPENDS =
include(advanceddockingsystem/advanceddockingsystem_dependencies.pri)
lv = advanceddockingsystem.depends
$$lv = $$QTC_LIB_DEPENDS
