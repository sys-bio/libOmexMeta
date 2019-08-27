set (SEMSIM_SOURCES
  # annotation/Annotatable.cpp
  # annotation/Annotation.cpp
  # annotation/AnnotationCopier.cpp
  # annotation/Ontology.cpp
  # annotation/ReferenceOntologyAnnotation.cpp
  # annotation/ReferenceTerm.cpp
  # annotation/Relation.cpp
  # definitions/OtherKBconstants.cpp
  # definitions/PropertyType.cpp
  # definitions/RDFNamespace.cpp
  # definitions/SBMLconstants.cpp
  # definitions/SemSimRelations.cpp
  # definitions/SemSimTypes.cpp
  # model/physical/SemSimComponent.cpp
  # utilities/CaseInsensitiveComparator.cpp
  # utilities/DuplicateChecker.cpp
  # utilities/ErrorEntry.cpp
  # utilities/ErrorLog.cpp
  # utilities/SemSimComponentComparator.cpp
  # SemSimObject.cpp
  BiomodelsQualifiers.cpp
  Relation.cpp
  Resource.cpp
  SingularAnnotation.cpp
  SemSim.cpp
  omex/OmexOutput.cpp
  omex/SBMLOmex.cpp
  rdf/RDFReader.cpp
)

# Create main and link to cellml
if (ENABLE_SHARED_LIB)
  add_library(semsim SHARED ${SEMSIM_SOURCES})
  target_include_directories(semsim PUBLIC .)
  # set_target_properties(semgen PROPERTIES PUBLIC_HEADER "libsemgen.h")
endif ()
if (ENABLE_STATIC_LIB)
  add_library(semsim-static STATIC ${SEMSIM_SOURCES})
  target_include_directories(semsim-static PUBLIC .)
  # set_target_properties(semgen-static PROPERTIES PUBLIC_HEADER "libsemgen.h")
  set_target_properties(semsim-static PROPERTIES OUTPUT_NAME semsim)
endif ()

if (${ENABLE_SHARED_LIB})
  list(APPEND LIBRARIES semsim)
  if(NOT DEFINED SEMSIM_LIBRARY)
    set(SEMSIM_LIBRARY semsim PARENT_SCOPE)
  endif()
endif ()
if (${ENABLE_STATIC_LIB})
  list(APPEND LIBRARIES semsim-static)
  if(NOT DEFINED SEMSIM_LIBRARY)
    set(SEMSIM_LIBRARY semsim-static PARENT_SCOPE)
  endif()
endif ()
foreach(l ${LIBRARIES})
  target_link_libraries(${l} sbml)
  target_link_libraries(${l} LibXml2::LibXml2)
  target_link_libraries(${l} ZLIB::ZLIB)
  target_link_libraries(${l} ${Raptor2_LIBRARIES})
  target_link_libraries(${l} ${Rasqal_LIBRARIES})
  target_link_libraries(${l} ${LibRDF_LIBRARIES})
  target_link_libraries(${l} ${LIBCOMBINE_LIBS})
  if (${LIBCELLML_LIBS})
    target_link_libraries(${l} ${LIBCELLML_LIBS})
  endif()
  install(TARGETS ${l}
          RUNTIME DESTINATION bin
          LIBRARY DESTINATION lib
          ARCHIVE DESTINATION lib
          PUBLIC_HEADER DESTINATION include)
endforeach ()
