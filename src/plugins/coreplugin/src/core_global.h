#ifndef COREGLOBAL_H
#define COREGLOBAL_H

#include <qglobal.h>

#if defined(CORE_LIBRARY)
#  define CORE_EXPORT Q_DECL_EXPORT
#elif defined(CORE_STATIC_LIBRARY) // Abuse single files for manual tests
#  define CORE_EXPORT
#else
#  define CORE_EXPORT Q_DECL_IMPORT
#endif


#endif
