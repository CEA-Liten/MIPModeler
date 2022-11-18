/*
 * GAMSModeler - General Algebraic Modeling System C++ API
 *
 * Author: Yacine Gaoua
 * @mail : yacine.gaoua@cea.fr
 */

#ifndef GAMSMODELER_GLOBAL_H
#define GAMSMODELER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(GAMSMODELER_LIBRARY)
#  define GAMSMODELERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define GAMSMODELERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // GAMSMODELER_GLOBAL_H
