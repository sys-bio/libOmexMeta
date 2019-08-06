add_executable(create_sbml_model create_sbml_model.cpp)
target_link_libraries(create_sbml_model ${SEMSIM_LIBRARY} ${libSBML_LIBRARIES})
install(TARGETS create_sbml_model DESTINATION bin/examples)

add_executable(import_combine_archive import_combine_archive.cpp)
target_link_libraries(import_combine_archive ${SEMSIM_LIBRARY} ${libSBML_LIBRARIES})
install(TARGETS import_combine_archive DESTINATION bin/examples)
