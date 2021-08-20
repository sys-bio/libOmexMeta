/* -*- Mode: c; c-basic-offset: 2 -*-
 *
 * win32_config.h - Rasqal WIN32 hard-coded config
 *
 * Copyright (C) 2004-2008, David Beckett http://www.dajobe.org/
 * Copyright (C) 2004-2005, University of Bristol, UK http://www.bristol.ac.uk/
 * 
 * This package is Free Software and part of Redland http://librdf.org/
 * 
 * It is licensed under the following three licenses as alternatives:
 *   1. GNU Lesser General Public License (LGPL) V2.1 or any newer version
 *   2. GNU General Public License (GPL) V2 or any newer version
 *   3. Apache License, V2.0 or any newer version
 * 
 * You may not use this file except in compliance with at least one of
 * the above three licenses.
 * 
 * See LICENSE.html or LICENSE.txt at the top of this package for the
 * complete terms and further detail along with the license texts for
 * the licenses in COPYING.LIB, COPYING and LICENSE-2.0.txt respectively.
 * 
 */


#ifndef WIN32_RASQAL_CONFIG_H
#define WIN32_RASQAL_CONFIG_H


#ifdef __cplusplus
extern "C" {
#endif



#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>


/* getopt is not in standard win32 C library - define if we have it */
/* #define HAVE_GETOPT_H 1 */

#define HAVE_STDLIB_H 1

#define HAVE_ERRNO_H 1

#define HAVE_STRICMP 1

/* MS names for these functions */
// next line breaks docs-build on wntmsci12
//#define vsnprintf _vsnprintf
//#define snprintf _snprintf
#define access _access
#define stricmp _stricmp
//#define strnicmp _strnicmp

/* definition from winsock2.h */
#ifndef _TIMEVAL_DEFINED
#define _TIMEVAL_DEFINED
typedef struct timeval {
    long tv_sec;
    long tv_usec;
} timeval;
#endif

struct timezone {
    int tz_minuteswest; /* minutes West of Greenwich */
    int tz_dsttime;     /* type of dst correction */
};

int rasqal_gettimeofday(struct timeval *tv, struct timezone *tz);

#undef HAVE_GETTIMEOFDAY



/* These are SPARQL token definitions */
#ifdef OPTIONAL
#undef OPTIONAL
#endif

#ifdef DELETE
#undef DELETE
#endif

#ifdef IN
#undef IN
#endif

#ifdef GROUP
#undef GROUP
#endif

// File on Linux, HFile on windows
//#ifdef __linux
//#define FILE FILE
//#elif defined(WIN32)
//#define HFILE FILE
//#endif

// We can use mpfr on windows as well
//#define RASQAL_DECIMAL_MPFR 1
//#define HAVE_MPFR_H 1


/*
 * Added by ciaran welsh
 */
#define HAVE_FLOAT_H 1 // we have on windows and linux.
#define HAVE_LIMITS_H 1 // we have on windows and linux.
#define HAVE_CONFIG_H 1

//#ifdef __cplusplus
//
//#else
//
//#endif


#define RASQAL_DECIMAL_NONE 1

#define HAVE_C99_VSNPRINTF 1

/* for access() which is POSIX but doesn't seem to have the defines in VC */
#ifndef R_OK
#define R_OK 4
#endif

/* __func__ doesn't exist in Visual Studio 6 */
#define __func__ ""

/* 
 * Defines that come from config.h
 */

#include <io.h>
#include <memory.h>


/* Release version as a decimal */
#define RASQAL_VERSION 933

/* Version number of package */
#define RASQAL_VERSION_STRING "0.9.33"

/* Major version number */
#define RASQAL_VERSION_MAJOR 0

/* Minor version number */
#define RASQAL_VERSION_MINOR 9

/* Release version number */
#define RASQAL_VERSION_RELEASE 33


/* This is a SPARQL token define */
#ifdef OPTIONAL
#undef OPTIONAL
#endif

/* bison: output uses ERROR in an enum which breaks if this is defined */
#ifdef ERROR
#undef ERROR
#endif

/* flex: const is available */
#define YY_USE_CONST
/* looks like the .c files define this anyway */
/* #define YY_NO_UNISTD_H */

#undef RASQAL_INLINE
#define RASQAL_INLINE __inline

/* Building SPARQL query */
#define RASQAL_QUERY_SPARQL 1

/* Use raptor to provide triples */
#define RAPTOR_TRIPLES_SOURCE_RAPTOR 1

/* Use redland to provide triples */
/* #define RAPTOR_TRIPLES_SOURCE_REDLAND 1 */

/* Use PCRE regex library */
//#define RASQAL_REGEX_PCRE 1



#define HAVE_LIBXML_SCHEMASINTERNALS_H 1
#define HAVE_LIBXML_XMLSCHEMASTYPES_H 1
#define HAVE_LIBXML_XMLSCHEMAS_H 1

#define RASQAL_UUID_INTERNAL 1
#define RASQAL_DIGEST_INTERNAL 1

#ifdef _DEBUG
// uncomment to get rasqal debugging messages. These are long and not that useful to libomexmeta
//#define RASQAL_DEBUG 1
#endif

#ifdef __cplusplus
}
#endif



#endif
