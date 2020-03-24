/**
 * @file    libcombine-version.h
 * @brief   Define libCombine version numbers for access from client software.
 *
 */


#ifndef LIBCOMBINE_VERSION_H
#define LIBCOMBINE_VERSION_H 

#include <omex/common/extern.h>


/**
 * LIBCOMBINE_DOTTED_VERSION:
 *
 * A version string of the form "1.2.3".
 */
#define LIBCOMBINE_DOTTED_VERSION	"@LIBCOMBINE_VERSION@"


/**
 * LIBCOMBINE_VERSION:
 *
 * The version as an integer: version 1.2.3 becomes 10203.  Since the major
 * number comes first, the overall number will always increase when a new
 * libCombine is released, making it easy to use less-than and greater-than
 * comparisons when testing versions numbers.
 */
#define LIBCOMBINE_VERSION		@LIBCOMBINE_VERSION_NUMERIC@


/**
 * LIBCOMBINE_VERSION_STRING:
 *
 * The numeric version as a string: version 1.2.3 becomes "10203".
 */
#define LIBCOMBINE_VERSION_STRING	"@LIBCOMBINE_VERSION_NUMERIC@"


LIBCOMBINE_CPP_NAMESPACE_BEGIN
BEGIN_C_DECLS

/**
 * Returns the version number of this copy of libCombine as an integer.
 *
 * @return the libCombine version as an integer; version 1.2.3 becomes 10203.
 */
LIBCOMBINE_EXTERN
int 
getLibCombineVersion();


/**
 * Returns the version number of this copy of libCombine as a string.
 *
 * @return the libCombine version as a string; version 1.2.3 becomes
 * "1.2.3".
 *
 * @see getLibCombineVersionString()
 */
LIBCOMBINE_EXTERN
const char* 
getLibCombineDottedVersion();


/**
 * Returns the version number of this copy of libCombine as a string without
 * periods.
 *
 * @return the libCombine version as a string: version 1.2.3 becomes "10203".
 *
 * @see getLibCombineDottedVersion()
 */
LIBCOMBINE_EXTERN
const char* 
getLibCombineVersionString();


END_C_DECLS
LIBCOMBINE_CPP_NAMESPACE_END

#endif  /* LIBCOMBINE_VERSION_H */
