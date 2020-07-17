//
// Created by Ciaran on 5/25/2020.
//

#ifndef LIBOMEXMETA_SUPERBUILD_PREPROC_H
#define LIBOMEXMETA_SUPERBUILD_PREPROC_H

#pragma once

// macro helpful for debugging
#include <ostream>

/*
 * Macros defined in this header file will eventually
 * be used to enable portability of libomexmeta
 */


// https://stackoverflow.com/questions/2164827/explicitly-exporting-shared-library-functions-in-linux
//#if defined(_WIN32)
////  Microsoft
//#define EXPORT __declspec(dllexport)
//#define IMPORT __declspec(dllimport)
//#elif defined(__GNUC__)
////  GCC
//#define EXPORT __attribute__((visibility("default")))
//#define IMPORT
//#else
////  do nothing and hope for the best?
//#define EXPORT
//#define IMPORT
//#pragma warning Unknown dynamic link import/export semantics.
//#endif

#ifdef _WIN32
#   ifdef  BUILD_SHARED_LIBS
/*Enabled as "export" while compiling the dll project*/
#define SEMSIM_API __declspec(dllexport)
#   else
/*Enabled as "import" in the Client side for using already created dll file*/
#   define SEMSIM_API __declspec(dllimport)
#   endif
#else
// empty on other platforms. 
#   define SEMSIM_API
#endif


#endif //LIBOMEXMETA_SUPERBUILD_PREPROC_H
