#ifndef NETSTD_GLOBAL_H
#define NETSTD_GLOBAL_H

//#include <QtCore/qglobal.h>

#if defined(NTSTD_LIBRARY)
#  define NTSTDSHARED_EXPORT// Q_DECL_EXPORT
#else
#  define NTSTDSHARED_EXPORT// Q_DECL_IMPORT
#endif

#endif // NETSTD_GLOBAL_H
