#ifndef NETSTD_GLOBAL_H
#define NETSTD_GLOBAL_H

//#include <QtCore/qglobal.h>

#if defined(NETSTD_LIBRARY)
#  define NETSTDSHARED_EXPORT// Q_DECL_EXPORT
#else
#  define NETSTDSHARED_EXPORT// Q_DECL_IMPORT
#endif

#endif // NETSTD_GLOBAL_H
