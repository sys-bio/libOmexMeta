//
// Created by Ciaran on 5/25/2020.
//

#ifndef LIBSEMSIM_SUPERBUILD_PREPROC_H
#define LIBSEMSIM_SUPERBUILD_PREPROC_H

#pragma once

// macro helpful for debugging
#include <ostream>

/*
 * Macros defined in this header file will eventually
 * be used to enable portability of libsemsim
 */

// https://stackoverflow.com/questions/2164827/explicitly-exporting-shared-library-functions-in-linux
#if defined(_WIN32)
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
