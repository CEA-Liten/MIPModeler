/**
 * @file MIPModeler_Global.h
 * @version 1.0
 * @author Yacine Gaoua (yacine.gaoua@cea.fr)
 * @date 07/2018
*/

#ifndef MIPMODELER_GLOBAL_H
#define MIPMODELER_GLOBAL_H

#if defined(_MSC_VER)
#define EXPORT __declspec(dllexport)
#define IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
//  GCC
#define EXPORT __attribute__((visibility("default")))
#define IMPORT
#else
//  do nothing and hope for the best?
#define EXPORT
#define IMPORT
#pragma warning Unknown dynamic link import/export semantics.
#endif

#ifdef MIPMODELER_LIBRARY
#define MIPMODELERSHARED_EXPORT EXPORT
#else
#define MIPMODELERSHARED_EXPORT IMPORT
#endif

#endif // MIPMODELER_GLOBAL_H
