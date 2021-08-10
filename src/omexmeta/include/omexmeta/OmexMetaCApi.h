//
// Created by Ciaran on 5/8/2020.
//

#ifndef LIBOMEXMETA_OMEXMETACAPI_H
#define LIBOMEXMETA_OMEXMETACAPI_H

#include "include/redland/Logger.h"
#include "omexmeta/Editor.h"
#include "omexmeta/EnergyDiff.h"
#include "omexmeta/OmexMetaUtils.h"
#include "omexmeta/OmexMetaXml.h"
#include "omexmeta/PhysicalEntity.h"
#include "omexmeta/PhysicalProcess.h"
#include "omexmeta/RDF.h"
#include "omexmeta_capi_export.h"
#include <cstring>

namespace omexmeta {


#ifdef __cplusplus
    extern "C" {
#endif

    OMEXMETA_CAPI_EXPORT int free_c_char_star(char *c);

    OMEXMETA_CAPI_EXPORT void setLastError(const char *msg);

    OMEXMETA_CAPI_EXPORT char *getLastError();

    OMEXMETA_CAPI_EXPORT void clearLastError(const std::string &err);

    /***************************************************
 * RDF class methods
 */

    OMEXMETA_CAPI_EXPORT RDF *RDF_new(const char *storage_type = "memory", const char *storage_name = "semsim_store",
                                      const char *storage_options = nullptr, const char *model_options = nullptr);

    OMEXMETA_CAPI_EXPORT void RDF_delete(RDF *rdf_ptr);

    OMEXMETA_CAPI_EXPORT char *RDF_getBaseUri(RDF *rdf_ptr);

    OMEXMETA_CAPI_EXPORT int RDF_setBaseUri(RDF *rdf_ptr, const char *uri);

    OMEXMETA_CAPI_EXPORT char *RDF_toString(RDF *rdf_ptr, const char *format);

    OMEXMETA_CAPI_EXPORT int RDF_toFile(RDF *rdf_ptr, const char *format, const char *filename);

    /**
     * @brief read RDF formatted annotations a string.
     * @param pdf_ptr a pointer to an RDF object.
     * @param str the string to read annotations from
     * @param format the format that the string annotations are in (get it
     * wrong to be provided a list of supported syntaxes)
     * @param baseuri the uri used for the base. All relative uri's
     * in the RDF graph are relative to the base uri
     *
     * @example
     * RDF* rdf_ptr = RDF_fromString(string_annotations, "rdfxml", "string_annotations_base_uri");
     */
    OMEXMETA_CAPI_EXPORT RDF *RDF_fromString(const char *str, const char *format,
                                             const char *storage_type = "memory", const char *storage_name = "semsim_store",
                                             const char *storage_options = nullptr, const char *model_options = nullptr);

    OMEXMETA_CAPI_EXPORT int RDF_addFromString(RDF *rdf_ptr, const char *str, const char *format);

    OMEXMETA_CAPI_EXPORT RDF *RDF_fromUri(const char *uri_string, const char *format,
                                          const char *storage_type = "memory", const char *storage_name = "semsim_store",
                                          const char *storage_options = nullptr, const char *model_options = nullptr);

    OMEXMETA_CAPI_EXPORT int RDF_addFromUri(RDF *rdf_ptr, const char *uri_string, const char *format);

    OMEXMETA_CAPI_EXPORT RDF *RDF_fromFile(const char *filename, const char *format, const char *storage_type = "memory",
                                           const char *storage_name = "semsim_store",
                                           const char *storage_options = nullptr, const char *model_options = nullptr);

    OMEXMETA_CAPI_EXPORT int RDF_addFromFile(RDF *rdf_ptr, const char *uri_string, const char *format);

    OMEXMETA_CAPI_EXPORT char *RDF_queryResultsAsString(RDF *rdf_ptr, const char *query_str, const char *results_format);

    OMEXMETA_CAPI_EXPORT ResultsMap *RDF_queryResultsAsMap(RDF *rdf_ptr, const char *query_str);

    OMEXMETA_CAPI_EXPORT void deleteResultsMap(ResultsMap *map);

    OMEXMETA_CAPI_EXPORT int RDF_size(RDF *rdf_ptr);

    OMEXMETA_CAPI_EXPORT int RDF_setRepositoryUri(RDF *rdf_ptr, const char *repository_uri);

    OMEXMETA_CAPI_EXPORT int RDF_setArchiveUri(RDF *rdf_ptr, const char *archive_uri);

    OMEXMETA_CAPI_EXPORT int RDF_setModelUri(RDF *rdf_ptr, const char *model_uri);

    OMEXMETA_CAPI_EXPORT char *RDF_getRepositoryUri(RDF *rdf_ptr);

    OMEXMETA_CAPI_EXPORT char *RDF_getArchiveUri(RDF *rdf_ptr);

    OMEXMETA_CAPI_EXPORT char *RDF_getModelUri(RDF *rdf_ptr);

    OMEXMETA_CAPI_EXPORT char *RDF_getLocalUri(RDF *rdf_ptr);

    OMEXMETA_CAPI_EXPORT int RDF_setModelMetaid(RDF *rdf_ptr, const char *model_metaid);

    OMEXMETA_CAPI_EXPORT char *RDF_getModelMetaid(RDF *rdf_ptr);

    OMEXMETA_CAPI_EXPORT char *RDF_getModelLevelAnnotationUri(RDF *rdf_ptr);

    OMEXMETA_CAPI_EXPORT bool RDF_equals_rdf_vs_string(RDF *rdf_ptr, const char *serialized_rdf, const char *format = "turtle", bool verbose = false);

    OMEXMETA_CAPI_EXPORT bool RDF_equals_rdf_vs_rdf(RDF *rdf_ptr1, RDF *rdf_ptr2, const char *format = "turtle", bool verbose = false);

    OMEXMETA_CAPI_EXPORT bool RDF_equals_string_vs_string(const char *first_rdf_graph, const char *second_rdf_graph, const char *format = "turtle", bool verbose = false);

    OMEXMETA_CAPI_EXPORT Editor *
    RDF_toEditor(RDF *rdf_ptr, const char *xml, bool generate_new_metaids, bool sbml_semantic_extraction);

    /*********************************************
 *  Editor class methods
 */

    OMEXMETA_CAPI_EXPORT PhysicalEntity *Editor_newPhysicalEntity(Editor *editor_ptr);

    OMEXMETA_CAPI_EXPORT PersonalInformation *Editor_newPersonalInformation(Editor *editor_ptr);

    OMEXMETA_CAPI_EXPORT EnergyDiff *Editor_newEnergyDiff(Editor *editor_ptr);

    OMEXMETA_CAPI_EXPORT SingularAnnotation *Editor_newSingularAnnotation(Editor *editor_ptr);

    OMEXMETA_CAPI_EXPORT PhysicalProperty *Editor_newPhysicalProperty(Editor *editor_ptr);

    OMEXMETA_CAPI_EXPORT PhysicalProcess *Editor_newPhysicalProcess(Editor *editor_ptr);


    OMEXMETA_CAPI_EXPORT int Editor_addNamespace(Editor *editor_ptr, const char *namespace_, const char *prefix);

    OMEXMETA_CAPI_EXPORT int Editor_addSingleAnnotation(Editor *editor_ptr, SingularAnnotation *singularAnnotation);

    OMEXMETA_CAPI_EXPORT int Editor_addPhysicalEntity(Editor *editor_ptr, PhysicalEntity *physicalEntity);

    OMEXMETA_CAPI_EXPORT int Editor_addPhysicalProcess(Editor *editor_ptr, PhysicalProcess *physicalProcess);

    OMEXMETA_CAPI_EXPORT int Editor_addPhysicalProperty(Editor *editor_ptr, PhysicalProperty *physicalProperty);

    OMEXMETA_CAPI_EXPORT int Editor_addEnergyDiff(Editor *editor_ptr, EnergyDiff *physicalForce);

    OMEXMETA_CAPI_EXPORT int Editor_addPersonalInformation(Editor *editor_ptr, PersonalInformation *personalInformation);

    OMEXMETA_CAPI_EXPORT int Editor_removeSingleAnnotation(Editor *editor_ptr, SingularAnnotation *singularAnnotation);

    OMEXMETA_CAPI_EXPORT int Editor_removePhysicalEntity(Editor *editor_ptr, PhysicalEntity *physicalEntity);

    OMEXMETA_CAPI_EXPORT int Editor_removePhysicalProcess(Editor *editor_ptr, PhysicalProcess *physicalProcess);

    OMEXMETA_CAPI_EXPORT int Editor_removeEnergyDiff(Editor *editor_ptr, EnergyDiff *physicalForce);

    OMEXMETA_CAPI_EXPORT int Editor_removePersonalInformation(Editor *editor_ptr, PersonalInformation *information);

    OMEXMETA_CAPI_EXPORT int Editor_checkValidMetaid(Editor *editor_ptr, const char *id);

    OMEXMETA_CAPI_EXPORT char *Editor_getMetaId(Editor *editor_ptr, int index);

    OMEXMETA_CAPI_EXPORT char *Editor_getXml(Editor *editor_ptr);

    OMEXMETA_CAPI_EXPORT int Editor_getNumMetaIds(Editor *editor_ptr);

    OMEXMETA_CAPI_EXPORT int Editor_delete(Editor *editor_ptr);

    OMEXMETA_CAPI_EXPORT char *Editor_getArchiveUri(Editor *editor_ptr);

    OMEXMETA_CAPI_EXPORT char *Editor_getLocalUri(Editor *editor_ptr);

    OMEXMETA_CAPI_EXPORT char *Editor_getModelUri(Editor *editor_ptr);

    OMEXMETA_CAPI_EXPORT char *Editor_getRepositoryUri(Editor *editor_ptr);

    OMEXMETA_CAPI_EXPORT char *Editor_stripAnnotations(Editor *editor_ptr, const char *annotationElementName = "annotation");

    OMEXMETA_CAPI_EXPORT Editor *Editor_addCreator(Editor *editor_ptr, const char *orcid_id);

    OMEXMETA_CAPI_EXPORT Editor *Editor_addContributor(Editor *editor_ptr, const char *orcid_id);

    OMEXMETA_CAPI_EXPORT Editor *Editor_addTaxon(Editor *editor_ptr, const char *taxon_id);

    OMEXMETA_CAPI_EXPORT Editor *Editor_addPubmed(Editor *editor_ptr, const char *pubmedid);

    OMEXMETA_CAPI_EXPORT Editor *Editor_addDescription(Editor *editor_ptr, const char *date);

    OMEXMETA_CAPI_EXPORT Editor *Editor_addDateCreated(Editor *editor_ptr, const char *date);

    OMEXMETA_CAPI_EXPORT Editor *Editor_addParentModel(Editor *editor_ptr, const char *biomod_id);

    /*********************************************************************
 * SingularAnnotation class methods
 */

    OMEXMETA_CAPI_EXPORT int SingularAnnotation_delete(SingularAnnotation *singularAnnotation);

    OMEXMETA_CAPI_EXPORT SingularAnnotation *
    SingularAnnotation_about(SingularAnnotation *singular_annotation, const char *about);

    OMEXMETA_CAPI_EXPORT SingularAnnotation *
    SingularAnnotation_setPredicate(SingularAnnotation *singular_annotation, const char *namespace_, const char *term);

    OMEXMETA_CAPI_EXPORT SingularAnnotation *
    SingularAnnotation_predicate(SingularAnnotation *singular_annotation, const char *namespace_, const char *term);

    OMEXMETA_CAPI_EXPORT SingularAnnotation *SingularAnnotation_setPredicateFromUri(
            SingularAnnotation *singular_annotation, const char *uri);

    OMEXMETA_CAPI_EXPORT SingularAnnotation *SingularAnnotation_predicateFromUri(
            SingularAnnotation *singular_annotation, const char *uri);

    OMEXMETA_CAPI_EXPORT SingularAnnotation *SingularAnnotation_setResourceLiteral(
            SingularAnnotation *singular_annotation, const char *literal);

    OMEXMETA_CAPI_EXPORT SingularAnnotation *SingularAnnotation_resourceLiteral(
            SingularAnnotation *singular_annotation, const char *literal);

    OMEXMETA_CAPI_EXPORT SingularAnnotation *
    SingularAnnotation_setResourceUri(SingularAnnotation *singular_annotation, const char *identifiers_uri);

    OMEXMETA_CAPI_EXPORT SingularAnnotation *
    SingularAnnotation_resourceUri(SingularAnnotation *singular_annotation, const char *identifiers_uri);

    OMEXMETA_CAPI_EXPORT SingularAnnotation *
    SingularAnnotation_setResourceBlank(SingularAnnotation *singular_annotation, const char *blank_id);

    OMEXMETA_CAPI_EXPORT SingularAnnotation *
    SingularAnnotation_resourceBlank(SingularAnnotation *singular_annotation, const char *blank_id);

    OMEXMETA_CAPI_EXPORT char *SingularAnnotation_getAbout(SingularAnnotation *singular_annotation);

    OMEXMETA_CAPI_EXPORT char *
    SingularAnnotation_str(SingularAnnotation *singular_annotation, const char *format);

    OMEXMETA_CAPI_EXPORT char *SingularAnnotation_getPredicate(SingularAnnotation *singular_annotation);

    OMEXMETA_CAPI_EXPORT char *SingularAnnotation_getResource(SingularAnnotation *singular_annotation);

    /*********************************************************************
 * PhysicalProperty class methods
 */

    OMEXMETA_CAPI_EXPORT char *PhysicalProperty_getAbout(PhysicalProperty *property);

    OMEXMETA_CAPI_EXPORT PhysicalProperty *PhysicalProperty_about(PhysicalProperty *property, const char *about, eUriType type = eUriType::NONE);

    OMEXMETA_CAPI_EXPORT char *PhysicalProperty_getIsVersionOfValue(PhysicalProperty *property);

    OMEXMETA_CAPI_EXPORT PhysicalProperty *PhysicalProperty_isPropertyOf(PhysicalProperty *property, const char *is_property_of, eUriType type);

    OMEXMETA_CAPI_EXPORT PhysicalProperty *PhysicalProperty_isVersionOf(PhysicalProperty *property, const char *is_version_of);

    OMEXMETA_CAPI_EXPORT char *PhysicalProperty_getIsPropertyOfValue(PhysicalProperty *property);

    OMEXMETA_CAPI_EXPORT char *PhysicalProperty_getPropertyMetaidBase(PhysicalProperty *property);

    OMEXMETA_CAPI_EXPORT int PhysicalProperty_delete(PhysicalProperty *property);

    /*********************************************************************
 * PhysicalEntity class methods
 */

    OMEXMETA_CAPI_EXPORT int PhysicalEntity_delete(PhysicalEntity *physical_entity_ptr);

    OMEXMETA_CAPI_EXPORT int PhysicalEntity_freeAll(PhysicalEntity *physical_entity_ptr);

    OMEXMETA_CAPI_EXPORT PhysicalEntity *PhysicalEntity_identity(
            PhysicalEntity *physical_entity_ptr, const char *identity_resource);

    OMEXMETA_CAPI_EXPORT char *PhysicalEntity_getAbout(PhysicalEntity *physical_entity_ptr);

    OMEXMETA_CAPI_EXPORT char *PhysicalEntity_getIdentity(PhysicalEntity *physical_entity_ptr);

    OMEXMETA_CAPI_EXPORT int PhysicalEntity_getNumLocations(PhysicalEntity *physicalEntity);

    OMEXMETA_CAPI_EXPORT char *PhysicalEntity_getLocation(PhysicalEntity *physical_entity_ptr, int index);

    OMEXMETA_CAPI_EXPORT char *PhysicalEntity_str(PhysicalEntity *physical_entity_ptr, const char *format, const char *base_uri);

    OMEXMETA_CAPI_EXPORT PhysicalEntity *PhysicalEntity_hasProperty(PhysicalEntity *physical_entity_ptr, PhysicalProperty *property);

    OMEXMETA_CAPI_EXPORT PhysicalEntity *PhysicalEntity_hasPropertyisVersionOf(PhysicalEntity *physical_entity_ptr, const char *isVersionOf);

    OMEXMETA_CAPI_EXPORT PhysicalEntity *PhysicalEntity_hasPropertyFull(PhysicalEntity *physical_entity_ptr, const char *property_about, eUriType about_uri_type, const char *is_version_of);

    OMEXMETA_CAPI_EXPORT PhysicalEntity *PhysicalEntity_isPartOf(PhysicalEntity *physical_entity_ptr, const char *is_part_of, eUriType type);

    OMEXMETA_CAPI_EXPORT PhysicalEntity *PhysicalEntity_hasPart(PhysicalEntity *physical_entity_ptr, const char *part);

    OMEXMETA_CAPI_EXPORT PhysicalEntity *PhysicalEntity_about(PhysicalEntity *physical_entity_ptr, const char *about, eUriType type = eUriType::NONE);

    /*********************************************************************
 * PhysicalProcess class methods
 */

    OMEXMETA_CAPI_EXPORT int PhysicalProcess_delete(PhysicalProcess *physicalProcess);

    OMEXMETA_CAPI_EXPORT int PhysicalProcess_freeAll(PhysicalProcess *physicalProcess);

    OMEXMETA_CAPI_EXPORT PhysicalProcess *PhysicalProcess_setPhysicalProperty(
            PhysicalProcess *physical_process, const char *subject_metaid, const char *physical_property);

    OMEXMETA_CAPI_EXPORT PhysicalProcess *PhysicalProcess_addSource(
            PhysicalProcess *physical_process,
            const char *physical_entity_reference, eUriType type, double multiplier);

    OMEXMETA_CAPI_EXPORT PhysicalProcess *PhysicalProcess_addSink(
            PhysicalProcess *physical_process,
            const char *physical_entity_reference, eUriType type, double multiplier);

    OMEXMETA_CAPI_EXPORT PhysicalProcess *PhysicalProcess_addMediator(
            PhysicalProcess *physical_process, const char *physical_entity_reference, eUriType type);

    OMEXMETA_CAPI_EXPORT char *
    PhysicalProcess_str(PhysicalProcess *physical_process_ptr, const char *format, const char *base_uri);

    OMEXMETA_CAPI_EXPORT PhysicalProcess *PhysicalProcess_about(PhysicalProcess *physical_process_ptr, const char *about, eUriType type = eUriType::NONE);

    OMEXMETA_CAPI_EXPORT PhysicalProcess *PhysicalProcess_isVersionOf(PhysicalProcess *physical_process_ptr, const char *version, eUriType type);

    OMEXMETA_CAPI_EXPORT PhysicalProcess *PhysicalProcess_hasProperty(PhysicalProcess *physical_process_ptr, PhysicalProperty *property);

    OMEXMETA_CAPI_EXPORT PhysicalProcess *PhysicalProcess_hasPropertyisVersionOf(PhysicalProcess *physical_process_ptr, const char *isVersionOf);

    OMEXMETA_CAPI_EXPORT PhysicalProcess *PhysicalProcess_hasPropertyFull(PhysicalProcess *physical_process_ptr, const char *property_about, eUriType about_uri_type, const char *is_version_of);


    /*********************************************************************
 * EnergyDiff class methods
 */


    /**
         * @brief deletes energy differential excluding all
     * nodes associated with it.
     */
    OMEXMETA_CAPI_EXPORT int EnergyDiff_delete(EnergyDiff *physicalForce);

    /**
         * @brief deletes energy differential including all
     * nodes associated with it.
     */
    OMEXMETA_CAPI_EXPORT int EnergyDiff_freeAll(EnergyDiff *energy_diff_ptr);

    OMEXMETA_CAPI_EXPORT EnergyDiff *EnergyDiff_addSource(
            EnergyDiff *energy_diff_ptr,
            const char *physical_entity_reference, eUriType type);

    OMEXMETA_CAPI_EXPORT EnergyDiff *EnergyDiff_addSink(
            EnergyDiff *energy_diff_ptr,
            const char *physical_entity_reference, eUriType type);

    OMEXMETA_DEPRECATED OMEXMETA_CAPI_EXPORT EnergyDiff *EnergyDiff_setPhysicalProperty(
            EnergyDiff *energy_diff_ptr, const char *subject_metaid, const char *physical_property);

    OMEXMETA_CAPI_EXPORT int EnergyDiff_getNumSources(EnergyDiff *physicalForce);

    OMEXMETA_CAPI_EXPORT int EnergyDiff_getNumSinks(EnergyDiff *physicalForce);

    OMEXMETA_CAPI_EXPORT char *EnergyDiff_str(EnergyDiff *energy_diff_ptr, const char *format, const char *base_uri);

    OMEXMETA_CAPI_EXPORT char *EnergyDiff_getAbout(EnergyDiff *energy_diff_ptr);

    OMEXMETA_CAPI_EXPORT EnergyDiff *EnergyDiff_about(EnergyDiff *energy_diff_ptr, const char *about, eUriType type = eUriType::NONE);

    OMEXMETA_CAPI_EXPORT EnergyDiff *EnergyDiff_hasProperty(EnergyDiff *energy_diff_ptr, PhysicalProperty *property);

    OMEXMETA_CAPI_EXPORT EnergyDiff *EnergyDiff_hasPropertyisVersionOf(EnergyDiff *energy_diff_ptr, const char *isVersionOf);

    OMEXMETA_CAPI_EXPORT EnergyDiff *EnergyDiff_hasPropertyFull(EnergyDiff *energy_diff_ptr, const char *property_about, eUriType about_uri_type, const char *is_version_of);


    /*********************************************************************
 * PersonalInformation class methods
 */


    OMEXMETA_CAPI_EXPORT int PersonalInformation_delete(PersonalInformation *information);

    OMEXMETA_CAPI_EXPORT char *PersonalInformation_getLocalUri(PersonalInformation *information);

    OMEXMETA_CAPI_EXPORT int PersonalInformation_setLocalUri(PersonalInformation *information, const char *localUri);

    OMEXMETA_CAPI_EXPORT PersonalInformation *PersonalInformation_addCreator(PersonalInformation *information, const char *value);

    OMEXMETA_CAPI_EXPORT PersonalInformation *PersonalInformation_addName(PersonalInformation *information, const char *value);

    OMEXMETA_CAPI_EXPORT PersonalInformation *PersonalInformation_addMbox(PersonalInformation *information, const char *value);

    OMEXMETA_CAPI_EXPORT PersonalInformation *
    PersonalInformation_addAccountName(PersonalInformation *information, const char *value);

    OMEXMETA_CAPI_EXPORT PersonalInformation *
    PersonalInformation_addAccountServiceHomepage(PersonalInformation *information, const char *value);

    OMEXMETA_CAPI_EXPORT PersonalInformation *
    PersonalInformation_addFoafBlank(PersonalInformation *information, const char *predicate, const char *blank_value);

    OMEXMETA_CAPI_EXPORT PersonalInformation *
    PersonalInformation_addFoafUri(PersonalInformation *information, const char *predicate, const char *uri_value);

    OMEXMETA_CAPI_EXPORT PersonalInformation *
    PersonalInformation_addFoafLiteral(PersonalInformation *information, const char *predicate,
                                       const char *literal_value);

    OMEXMETA_CAPI_EXPORT PersonalInformation *
    PersonalInformation_addFoaf(PersonalInformation *information, const char *predicate, const LibrdfNode &value_node);

    OMEXMETA_CAPI_EXPORT char *PersonalInformation_getMetaid(PersonalInformation *information);

    OMEXMETA_CAPI_EXPORT int PersonalInformation_setMetaid(PersonalInformation *information, const char *metaid);

    OMEXMETA_CAPI_EXPORT int StringVector_getSize(std::vector<std::string>* vec);

    OMEXMETA_CAPI_EXPORT char* StringVector_getElementAtIdx(std::vector<std::string>* vec, int idx);

    OMEXMETA_CAPI_EXPORT void StringVector_delete(std::vector<std::string> *strVec);

    OMEXMETA_CAPI_EXPORT int ResultsMap_getSize(ResultsMap* resultsMap);

    OMEXMETA_CAPI_EXPORT std::vector<std::string>* ResultsMap_getStringVectorAt(ResultsMap* resultsMap, const char* key);

    OMEXMETA_CAPI_EXPORT std::vector<std::string>* ResultsMap_getKeys(ResultsMap* resultsMap);

    OMEXMETA_CAPI_EXPORT void ResultsMap_delete(ResultsMap * resultsMap);

    OMEXMETA_CAPI_EXPORT Logger *Logger_getLogger();

    OMEXMETA_CAPI_EXPORT void Logger_setFormatter(const char* format);

    OMEXMETA_CAPI_EXPORT void Logger_setLevel(Logger::LogLevel level);

    OMEXMETA_CAPI_EXPORT Logger::LogLevel Logger_getLevel();

    OMEXMETA_CAPI_EXPORT void Logger_enableBacktrace(int num);

    OMEXMETA_CAPI_EXPORT void Logger_disableBacktrace();

    OMEXMETA_CAPI_EXPORT void Logger_dumpBacktrace();

    OMEXMETA_CAPI_EXPORT void Logger_consoleLogger();

    OMEXMETA_CAPI_EXPORT void Logger_fileLogger(const char*filename);

    OMEXMETA_CAPI_EXPORT void Logger_info(const char* message);

    OMEXMETA_CAPI_EXPORT void Logger_trace(const char* message);

    OMEXMETA_CAPI_EXPORT void Logger_debug(const char* message);

    OMEXMETA_CAPI_EXPORT void Logger_warn(const char* message);

    OMEXMETA_CAPI_EXPORT void Logger_error(const char* message);

    OMEXMETA_CAPI_EXPORT void Logger_critical(const char* message);


#ifdef __cplusplus
    }
#endif
}// namespace omexmeta

#endif//LIBOMEXMETA_OMEXMETACAPI_H
