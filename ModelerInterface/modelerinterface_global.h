#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(MODELERINTERFACE_LIB)
#  define ABSTRACTMODELER_EXPORT Q_DECL_EXPORT
# else
#  define ABSTRACTMODELER_EXPORT Q_DECL_IMPORT
# endif
#else
# define ABSTRACTMODELER_EXPORT
#endif
