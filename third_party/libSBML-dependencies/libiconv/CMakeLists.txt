###############################################################################
#
# $URL$
# $Id$
#
# Description       : CMake build script for libSBML dependencies (iconv)
# Original author(s): Frank Bergmann <fbergman@caltech.edu>
# Organization      : California Institute of Technology
#
# This file is part of libSBML.  Please visit http://sbml.org for more
# information about SBML, and the latest version of libSBML.
#
# Copyright 2005-2011 California Institute of Technology.
# Copyright 2002-2005 California Institute of Technology and
#                     Japan Science and Technology Corporation.
# 
# This library is free software; you can redistribute it and/or modify it
# under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation.  A copy of the license agreement is provided
# in the file named "LICENSE.txt" included with this software distribution
# and also available online as http://sbml.org/software/libsbml/license.html
#
###############################################################################

if (WITH_ICONV)
project(iconv)

if (WITH_STATIC_RUNTIME)
	foreach(flag_var
		CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
		CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO
		CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
		CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO)

		if(${flag_var} MATCHES "/MD")
			string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
		endif(${flag_var} MATCHES "/MD")
		
		
	endforeach(flag_var)
	add_definitions( -D_MT)
endif(WITH_STATIC_RUNTIME)

set(ICONV_SOURCE
	"source/lib/iconv.c"
	"source/libcharset/lib/localcharset.c"
	"source/lib/relocatable.c"
)

include_directories(
	"source/"
	"source/lib"
	"source/libcharset/lib"
	"source/include"
)

add_definitions(
		-DHAVE_CONFIG_H=1
		-DENABLE_RELOCATABLE=1
		-DIN_LIBRARY
		-DNO_XMALLOC
		-Dset_relocation_prefix=libiconv_set_relocation_prefix
		-Drelocate=libiconv_relocate
                -DINSTALLPREFIX="/usr/lib"
		-DINSTALLDIR="/usr/local/lib"
		-DLIBDIR="/usr/lib"
		
		-DPIC
		)

if(WIN32)
add_definitions(
		-DWIN32 
		-D_CRT_SECURE_NO_WARNINGS 
		-D_CRT_SECURE_NO_DEPRECATE 
		-D_CRT_NONSTDC_NO_DEPRECATE 
		-DINSTALLPREFIX="c:/program files/iconv"
		-DINSTALLDIR="c:/program files/iconv"
		-DLIBDIR="c:/program files/iconv"
		-DBUILDING_LIBICONV
		-DBUILDING_DLL=1		
		)

add_library (libiconv ${ICONV_SOURCE} )

INSTALL(TARGETS libiconv
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
  )

else()

if (NOT CYGWIN)
	# on cygwin all code is position independent so -fPIC is not needed
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-strict-aliasing -fPIC")
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-strict-aliasing -fPIC")
endif()


add_library (iconv ${ICONV_SOURCE} )

INSTALL(TARGETS iconv
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
  )

endif()



install(FILES 
	"source/include/iconv.h"
	DESTINATION include)

	install(FILES 
	"source/include/iconv.h"
	DESTINATION include/iconv)


endif()
