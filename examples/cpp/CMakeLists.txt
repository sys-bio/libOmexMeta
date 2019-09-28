add_executable(create_sbml_model create_sbml_model.cpp)
target_link_libraries(create_sbml_model ${SEMSIM_LIBRARY})
install(TARGETS create_sbml_model DESTINATION bin/examples)

add_executable(import_combine_archive import_combine_archive.cpp)
target_link_libraries(import_combine_archive ${SEMSIM_LIBRARY})
install(TARGETS import_combine_archive DESTINATION bin/examples)

add_executable(import_sbml import_sbml.cpp)
target_link_libraries(import_sbml ${SEMSIM_LIBRARY})
install(TARGETS import_sbml DESTINATION bin/examples)

add_executable(query_sbml query_sbml.cpp)
target_link_libraries(query_sbml ${SEMSIM_LIBRARY})
install(TARGETS query_sbml DESTINATION bin/examples)

add_executable(query_sbml_tiered query_sbml_tiered.cpp)
target_link_libraries(query_sbml_tiered ${SEMSIM_LIBRARY})
install(TARGETS query_sbml_tiered DESTINATION bin/examples)

add_executable(list_omex list_omex.cpp)
target_link_libraries(list_omex ${SEMSIM_LIBRARY})
install(TARGETS list_omex DESTINATION bin/examples)

add_executable(sbml_to_omex sbml_to_omex.cpp)
target_link_libraries(sbml_to_omex ${SEMSIM_LIBRARY})
install(TARGETS sbml_to_omex DESTINATION bin/examples)

add_executable(query_rdf query_rdf.cpp)
target_link_libraries(query_rdf ${SEMSIM_LIBRARY})
install(TARGETS query_rdf DESTINATION bin/examples)
