//
// Created by Ciaran on 5/6/2020.
//

#ifndef LIBOMEXMETA_EXPORT_H
#define LIBOMEXMETA_EXPORT_H

/*
 * Used for portability
 */


#pragma once
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


#endif //LIBOMEXMETA_SUPERBUILD_EXPORT_H
