/**
 * @file    libcombine-namespace.h
 * @brief   Defines C++ namespace of libCombine
 */
 

#ifndef LIBCOMBINE_NAMESPACE_H
#define LIBCOMBINE_NAMESPACE_H 1

#ifndef SWIG
#include <sbml/common/libsbml-namespace.h>

LIBSBML_CPP_NAMESPACE_USE

#endif
/*
 *
 * The idea of the following marcors are borrowed from 
 * Xerces-C++ XML Parser (http://xerces.apache.org/xerces-c/).
 *
 */

/* Define to enable libCombine C++ namespace */
#cmakedefine LIBCOMBINE_USE_CPP_NAMESPACE 1


#if defined(__cplusplus) && defined(LIBCOMBINE_USE_CPP_NAMESPACE) && !defined(SWIG)
  /* C++ namespace of libCombine */
  #define LIBCOMBINE_CPP_NAMESPACE            libcombine
  #define LIBCOMBINE_CPP_NAMESPACE_BEGIN      namespace LIBCOMBINE_CPP_NAMESPACE {
  #define LIBCOMBINE_CPP_NAMESPACE_END        }
  #define LIBCOMBINE_CPP_NAMESPACE_USE        using namespace LIBCOMBINE_CPP_NAMESPACE;
  #define LIBCOMBINE_CPP_NAMESPACE_QUALIFIER  LIBCOMBINE_CPP_NAMESPACE::

  namespace LIBCOMBINE_CPP_NAMESPACE {}
#else
  #define LIBCOMBINE_CPP_NAMESPACE 
  #define LIBCOMBINE_CPP_NAMESPACE_BEGIN
  #define LIBCOMBINE_CPP_NAMESPACE_END  
  #define LIBCOMBINE_CPP_NAMESPACE_USE 
  #define LIBCOMBINE_CPP_NAMESPACE_QUALIFIER 
#endif


#endif  /* LIBCOMBINE_NAMESPACE_H */

