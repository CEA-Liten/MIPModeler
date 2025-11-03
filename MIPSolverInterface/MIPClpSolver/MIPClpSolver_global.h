#ifndef MIPCLPSOLVER_GLOBAL_H
#define MIPCLPSOLVER_GLOBAL_H

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

#if defined(MIPCLPSOLVER_LIBRARY)
#  define MIPCLPSOLVERSHARED_EXPORT EXPORT
#else
#  define MIPCLPSOLVERSHARED_EXPORT IMPORT
#endif


#endif // MIPCLPSOLVER_GLOBAL_H
