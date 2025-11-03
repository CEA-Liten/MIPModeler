#pragma once

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
#ifndef BUILD_STATIC
#if defined(MODELERINTERFACE_LIB)
#  define ABSTRACTMODELER_EXPORT EXPORT
#else
#  define ABSTRACTMODELER_EXPORT IMPORT
#endif
#else
# define ABSTRACTMODELER_EXPORT
#endif