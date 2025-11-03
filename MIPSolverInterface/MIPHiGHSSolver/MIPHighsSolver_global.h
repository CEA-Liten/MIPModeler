#ifndef MIPHIGHSSOLVER_GLOBAL_H
#define MIPHIGHSSOLVER_GLOBAL_H

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

#if defined(MIPHIGHSSOLVER_LIBRARY)
#  define MIPHIGHSSOLVERSHARED_EXPORT EXPORT
#else
#  define MIPHIGHSSOLVERSHARED_EXPORT IMPORT
#endif

#endif // MIPHIGHSSOLVER_GLOBAL_H
