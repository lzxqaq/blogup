linux* {
    QMAKE_LFLAGS += "-Wl,-rpath,\'\$$ORIGIN/lib\'"
}
