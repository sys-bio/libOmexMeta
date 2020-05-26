//
// Created by Ciaran on 5/25/2020.
//

#ifndef LIBSEMSIM_SUPERBUILD_PREPROC_H
#define LIBSEMSIM_SUPERBUILD_PREPROC_H

#pragma once

// macro helpful for debugging
#include <ostream>

/*
 * Macro handy for debugging seg faults.
 */
#define HERE(x)                              \
do {                                        \
  std::cout << __FILE__ << ":" << __LINE__ <<std::endl; \
} while (0)


/*
 * Logger, extension of HERE. Used for error messages
 */
#define LOG(x)                              \
do {                                        \
  std::cout << __FILE__ << ":" <<__FUNC__<<":"<< __LINE__ << ":" << x << std::endl; \
} while (0)





// https://stackoverflow.com/questions/2164827/explicitly-exporting-shared-library-functions-in-linux
#if defined(_MSC_VER)
//  Microsoft
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


#endif //LIBSEMSIM_SUPERBUILD_PREPROC_H
