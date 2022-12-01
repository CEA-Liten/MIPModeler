/**
 * @file MIPModeler_Global.h
 * @version 1.0
 * @author Yacine Gaoua (yacine.gaoua@cea.fr)
 * @date 07/2018
*/

#ifndef MIPMODELER_GLOBAL_H
#define MIPMODELER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MIPMODELER_LIBRARY)
#  define MIPMODELERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MIPMODELERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MIPMODELER_GLOBAL_H
