## @file    CMakeLists.txt
## @brief   CMake build script for example programs
## @author  Frank T. Bergmann
##

# only compile examples if specified, but always copy samples
if(WITH_EXAMPLES)

add_subdirectory(c++)

if(WITH_CSHARP)
  add_subdirectory(csharp)
endif(WITH_CSHARP)

if(WITH_JAVA)
  add_subdirectory(java)
endif(WITH_JAVA)

endif(WITH_EXAMPLES)



# the remaining language bindings do not need to be compiled in order to run. 

# Now we just have to select files for installation# 
# install c++ examples
file(GLOB cpp_samples "${CMAKE_CURRENT_SOURCE_DIR}/c++/*.c"
                      "${CMAKE_CURRENT_SOURCE_DIR}/c++/*.cpp"
                      "${CMAKE_CURRENT_SOURCE_DIR}/c++/*.h"
                      "${CMAKE_CURRENT_SOURCE_DIR}/c++/README.md")
install(FILES ${cpp_samples} DESTINATION ${MISC_PREFIX}examples/c++)

if(WITH_CSHARP)
# install c# examples
file(GLOB cs_samples "${CMAKE_CURRENT_SOURCE_DIR}/csharp/*.cs"
                     "${CMAKE_CURRENT_SOURCE_DIR}/csharp/README.md")
install(FILES ${cs_samples} DESTINATION ${MISC_PREFIX}examples/csharp)
endif()

if(WITH_JAVA)
# install java examples
file(GLOB java_samples "${CMAKE_CURRENT_SOURCE_DIR}/java/*.java"
                       "${CMAKE_CURRENT_SOURCE_DIR}/java/README.md")
install(FILES ${java_samples} DESTINATION ${MISC_PREFIX}examples/java)
endif()

if(WITH_PERL)
# install perl examples
file(GLOB perl_samples "${CMAKE_CURRENT_SOURCE_DIR}/perl/*.pl"
                       "${CMAKE_CURRENT_SOURCE_DIR}/perl/README.md")
install(FILES ${perl_samples} DESTINATION ${MISC_PREFIX}examples/perl)
endif()

if (WITH_PYTHON)
# install python examples
file(GLOB python_samples "${CMAKE_CURRENT_SOURCE_DIR}/python/*.py"
                         "${CMAKE_CURRENT_SOURCE_DIR}/python/README.md")
install(FILES ${python_samples} DESTINATION ${MISC_PREFIX}examples/python)
endif()


if(WITH_RUBY)
# install ruby examples
file(GLOB perl_samples "${CMAKE_CURRENT_SOURCE_DIR}/ruby/*.rb"
                       "${CMAKE_CURRENT_SOURCE_DIR}/ruby/README.md")
install(FILES ${perl_samples} DESTINATION ${MISC_PREFIX}examples/ruby)
endif()

if (WITH_R)
# install r examples
file(GLOB r_samples "${CMAKE_CURRENT_SOURCE_DIR}/r/*.R"
                         "${CMAKE_CURRENT_SOURCE_DIR}/r/README.md")
install(FILES ${r_samples} DESTINATION ${MISC_PREFIX}examples/r)
endif()

