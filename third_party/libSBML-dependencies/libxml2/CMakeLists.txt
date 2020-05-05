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

if (WITH_LIBXML)
project(libxml2)

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

set(LIBXML_SOURCE
	"c14n.c"
	"catalog.c"
	"chvalid.c"
	"debugXML.c"
	"dict.c"
	"DOCBparser.c"
	"encoding.c"
	"entities.c"
	"error.c"
	"globals.c"
	"hash.c"
	"HTMLparser.c"
	"HTMLtree.c"
	"legacy.c"
	"list.c"
	"nanoftp.c"
	"nanohttp.c"
	"parser.c"
	"parserInternals.c"
	"pattern.c"
	"relaxng.c"
	"SAX.c"
	"SAX2.c"
	"schematron.c"
	"threads.c"
	"tree.c"
	"uri.c"
	"valid.c"
	"xinclude.c"
	"xlink.c"
	"xmlIO.c"
	"xmlmemory.c"
	"xmlmodule.c"
	"xmlreader.c"
	"xmlregexp.c"
	"xmlsave.c"
	"xmlschemas.c"
	"xmlschemastypes.c"
	"xmlstring.c"
	"xmlunicode.c"
	"xmlwriter.c"
	"xpath.c"
	"xpointer.c"
)


include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/libxml"
					"${CMAKE_SOURCE_DIR}/libiconv/source/include"
					"${CMAKE_SOURCE_DIR}/zlib/source"
					"${CMAKE_CURRENT_SOURCE_DIR}/include"
					"${CMAKE_CURRENT_SOURCE_DIR}")


if (WIN32)
add_definitions(-DWIN32
				-DHAVE_ZLIB_H 
				-D_CRT_SECURE_NO_WARNINGS
				-D_CRT_SECURE_NO_DEPRECATE 
				-D_CRT_NONSTDC_NO_DEPRECATE 
				)
add_library (libxml2 ${LIBXML_SOURCE} )
target_link_libraries(libxml2 zdll libiconv wsock32.lib ws2_32.lib)
INSTALL(TARGETS libxml2
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

add_definitions(
				-DHAVE_ZLIB_H 
-DHAVE_STDLIB_H
-DHAVE_UNISTD_H
-DHAVE_SYS_SOCKET_H
-DHAVE_NETINET_IN_H
-DHAVE_ARPA_INET_H
-DHAVE_NETDB_H-DHAVE_FCNTL_H
-DHAVE_SYS_TIME_H
-DHAVE_SYS_SELECT_H
-DHAVE_SYS_SOCKET_H
-DHAVE_SYS_TYPES_H
-DHAVE_STRINGS_H
)

add_library (xml2 ${LIBXML_SOURCE} )
target_link_libraries(xml2 zlib libiconv )
INSTALL(TARGETS xml2
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
  )


endif()	
		

install(DIRECTORY 
	"include/libxml"
	DESTINATION include
	FILES_MATCHING PATTERN "*.h")

file(GLOB HEADERS include/libxml/*.h)
install(FILES  ${HEADERS}	
	DESTINATION include/libxml)
	
	
endif()
