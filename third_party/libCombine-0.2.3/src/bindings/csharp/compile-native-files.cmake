#################################################
 # @file compile-native-files.cmake
 # @brief Base file
 # @author DEVISER
 #
 # <!--------------------------------------------------------------------------
 # This file is part of libSBML. Please visit http://sbml.org for more
 # information about SBML, and the latest version of libSBML.
 #
 # Copyright (C) 2013-2016 jointly by the following organizations:
 # 1. California Institute of Technology, Pasadena, CA, USA
 # 2. EMBL European Bioinformatics Institute (EMBL-EBI), Hinxton, UK
 # 3. University of Heidelberg, Heidelberg, Germany
 #
 # Copyright (C) 2009-2013 jointly by the following organizations:
 # 1. California Institute of Technology, Pasadena, CA, USA
 # 2. EMBL European Bioinformatics Institute (EMBL-EBI), Hinxton, UK
 #
 # Copyright (C) 2006-2008 by the California Institute of Technology,
 # Pasadena, CA, USA
 #
 # Copyright (C) 2002-2005 jointly by the following organizations:
 # 1. California Institute of Technology, Pasadena, CA, USA
 # 2. Japan Science and Technology Agency, Japan
 #
 # This library is free software; you can redistribute it and/or modify it
 # under the terms of the GNU Lesser General Public License as published by the
 # Free Software Foundation. A copy of the license agreement is provided in the
 # file named "LICENSE.txt" included with this software distribution and also
 # available online as http://sbml.org/software/libsbml/license.html
 # ------------------------------------------------------------------------ -->
 #


message("Creating: libcombinecsP.dll")

# find all sources
file(GLOB_RECURSE SOURCE_FILES RELATIVE ${BIN_DIRECTORY} ${BIN_DIRECTORY}/csharp-files/*.cs)
set(SOURCE_FILES ${SOURCE_FILES} ${BIN_DIRECTORY}/AssemblyInfo.cs)


SET(PATCH_SWIG_FILES ON)

# convert paths
set(NATIVE_FILES)
foreach(csFile ${SOURCE_FILES})
  
  file(TO_NATIVE_PATH ${csFile} temp)
  set(NATIVE_FILES ${NATIVE_FILES} ${temp})

  
  if (PATCH_SWIG_FILES)
  
    # read file, prepend using statement, write again ... 
    file(READ ${csFile} content)
    file(WRITE ${csFile} "using System;\nusing System.Runtime.InteropServices;\n\n${content}")

  endif(PATCH_SWIG_FILES)

endforeach()

# delete file if it exists
if (EXISTS ${BIN_DIRECTORY}/libcombinecsP.dll)
    file(REMOVE ${BIN_DIRECTORY}/libcombinecsP.dll)	
endif()

# the compile run disables the following warnings
# -  105: warning CS0105: The using directive for `x' appeared previously 
#         in this namespace (needed because of swig 3.0.2)
# -  108: 'method name' hides inherited member 'base member name'. Use the 
#         new keyword if hiding was intended.
# -  114: 'method name' hides inherited member 'base member name'. To make 
#         the current member override that implementation, add the override 
#         keyword. Otherwise add the new keyword.
# - 1570: XML comment on 'class name' has badly formed XML.
# - 1572: XML comment on 'method name' has a param tag for 'parameter name'
#         but there is no parameter by that name.
# - 1573: Parameter 'parameter name' has no matching param tag in the XML 
#         comment for 'method name' (but other parameters do).
# - 1574: XML comment on 'method name' has cref attribute 'method name' 
#         that could not be resolved.
# - 1591: Missing XML comment for publicly visible type or member 'method
#         name'

# compile files
execute_process(
    COMMAND "${CSHARP_COMPILER}"
         -target:library
         -nowarn:105,108,109,114,1570,1572,1573,1574,1591
         -out:libcombinecsP.dll
         -doc:libcombinecsP.xml
         ${CSHARP_EXTRA_ARGS}
         ${NATIVE_FILES}
    ERROR_VARIABLE COMPILE_ERROR
    OUTPUT_VARIABLE COMPILE_OUT
    WORKING_DIRECTORY "${BIN_DIRECTORY}"
)

if (NOT EXISTS ${BIN_DIRECTORY}/libcombinecsP.dll)
  message(FATAL_ERROR "Compiling the library failed with ${COMPILE_OUT} ${COMPILE_ERROR}")
endif()

# # print variables for debug purposes
# message("BIN_DIRECTORY     : ${BIN_DIRECTORY}")
# message("SRC_DIRECTORY     : ${SRC_DIRECTORY}")
# message("CSHARP_COMPILER   : ${CSHARP_COMPILER}")
# message("CSHARP_EXTRA_ARGS : ${CSHARP_EXTRA_ARGS}")
# 
