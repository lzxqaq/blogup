
#include "qtcassert.h"

#include <QByteArray>
#include <QDebug>

#if defined(Q_OS_UNIX)
#include <stdio.h>
#include <signal.h>
#include <execinfo.h>
#endif

namespace Utils {

void dumpBacktrace(int maxdepth)
{
    if (maxdepth == -1)
        maxdepth = 1000;
#if defined(Q_OS_UNIX)
    void *bt[1000] = {nullptr};
    int size = backtrace(bt, sizeof(bt) / sizeof(bt[0]));
    char **lines = backtrace_symbols(bt, size);
    for (int i = 0; i < size; ++i)
        qDebug() << "0x" + QByteArray::number(quintptr(bt[i]), 16) << lines[i];
    free(lines);
#endif
}

void writeAssertLocation(const char *msg)
{
    static bool goBoom = qEnvironmentVariableIsSet("QTC_FATAL_ASSERTS");
    if (goBoom)
        qFatal("SOFT ASSERT made fatal: %s", msg);
    else
        qDebug("SOFT ASSERT: %s", msg);

    static int maxdepth = qEnvironmentVariableIntValue("QTC_BACKTRACE_MAXDEPTH");
    if (maxdepth != 0)
        dumpBacktrace(maxdepth);
}

} // namespace Utils
