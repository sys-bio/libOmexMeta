add_executable(create_sbml_model create_sbml_model.cpp)
target_link_libraries(create_sbml_model ${SEMSIM_LIBRARY} ${libSBML_LIBRARIES})
install(TARGETS create_sbml_model DESTINATION bin/examples)
