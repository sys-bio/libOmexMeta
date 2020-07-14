//
// Created by Ciaran on 5/8/2020.
//

#ifndef LIBOMEXMETA_OMEXMETACAPI_H
#define LIBOMEXMETA_OMEXMETACAPI_H

#include "omexmeta/RDF.h"
#include "omexmeta/Editor.h"
#include "omexmeta/SemsimXmlAssistant.h"
#include "omexmeta/PhysicalEntity.h"
#include "omexmeta/PhysicalProcess.h"
#include "omexmeta/PhysicalForce.h"
#include <cstring>
#include "omexmeta/OmexMetaUtils.h"
#include "omexmeta/Preproc.h"

namespace omexmeta {

#ifdef __cplusplus
    extern "C" {
#endif

    SEMSIM_API void free_c_char_star(char *c);

    SEMSIM_API void free_c_char_star_star(char **c, int size);

    SEMSIM_API char *_func_that_returns_dynamic_alloc_str();

    SEMSIM_API char **_func_that_returns_dynamic_alloc_char_star_star();

/***************************************************
 * librdf_world methods
 *
 * note: Really I do not want users to have to deal with this
 * todo take steps to ensure users do not need to interact with the librdf_world*
 *
 */

    SEMSIM_API [[maybe_unused]] [[maybe_unused]] void free_world(librdf_world *world);

/***************************************************
 * RDF class methods
 */

    SEMSIM_API RDF *RDF_new(const char *storage_type = "memory", const char *storage_name = "semsim_store",
                            const char *storage_options = nullptr, const char *model_options = nullptr);

    SEMSIM_API void RDF_delete(RDF *rdf_ptr);

    SEMSIM_API char *RDF_getBaseUri(RDF *rdf_ptr);

    SEMSIM_API void RDF_setBaseUri(RDF *rdf_ptr, const char *uri);

    SEMSIM_API char *RDF_toString(RDF *rdf_ptr, const char *format, const char *base_uri);

    /*
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
    SEMSIM_API RDF *RDF_fromString(const char *str, const char *format, const char *baseuri = "./Annotations.rdf",
                                   const char *storage_type = "memory", const char *storage_name = "semsim_store",
                                   const char *storage_options = nullptr, const char *model_options = nullptr);

    SEMSIM_API void RDF_addFromString(RDF *rdf_ptr, const char *str, const char *format, const char *base_uri);

    SEMSIM_API RDF *RDF_fromUri(const char *uri_string, const char *format,
                                const char *storage_type = "memory", const char *storage_name = "semsim_store",
                                const char *storage_options = nullptr, const char *model_options = nullptr);

    SEMSIM_API void RDF_addFromUri(RDF *rdf_ptr, const char *uri_string, const char *format);

    SEMSIM_API RDF *RDF_fromFile(const char *filename, const char *format, const char *storage_type = "memory",
                                 const char *storage_name = "semsim_store",
                                 const char *storage_options = nullptr, const char *model_options = nullptr);

    SEMSIM_API void RDF_addFromFile(RDF *rdf_ptr, const char *uri_string, const char *format);

    SEMSIM_API char *RDF_queryResultsAsStr(RDF *rdf_ptr, const char *query_str, const char *results_format);

    SEMSIM_API int RDF_size(RDF *rdf_ptr);

    SEMSIM_API void RDF_setRepositoryUri(RDF *rdf_ptr, std::string repository_uri);

    SEMSIM_API void RDF_setArchiveUri(RDF *rdf_ptr, std::string archive_uri);

    SEMSIM_API void RDF_setModelUri(RDF *rdf_ptr, std::string model_uri);
    
    SEMSIM_API char* RDF_getRepositoryUri(RDF *rdf_ptr);

    SEMSIM_API char* RDF_getArchiveUri(RDF *rdf_ptr);

    SEMSIM_API char* RDF_getModelUri(RDF *rdf_ptr);

    SEMSIM_API char* RDF_getLocalUri(RDF *rdf_ptr);

    SEMSIM_API Editor *RDF_toEditor(RDF *rdf_ptr, const char *xml, SemsimXmlType type);

//RDF* RDF_fromOmex(RDF* rdf_ptr, const char* filename_or_uri, const char* format);

/*********************************************
 *  Editor class methods
 */

    SEMSIM_API void Editor_addNamespace(Editor *editor_ptr, const char *namespace_, const char *prefix);

    SEMSIM_API void Editor_addSingleAnnotation(Editor *editor_ptr, SingularAnnotation *singularAnnotation);

    SEMSIM_API void Editor_addPhysicalEntity(Editor *editor_ptr, PhysicalEntity *physicalEntity);

    SEMSIM_API void Editor_addPhysicalProcess(Editor *editor_ptr, PhysicalProcess *physicalProcess);

    SEMSIM_API void Editor_addPhysicalForce(Editor *editor_ptr, PhysicalForce *physicalForce);

    SEMSIM_API void Editor_addPersonalInformation(Editor *editor_ptr, PersonalInformation *personalInformation);

    SEMSIM_API void Editor_removeSingleAnnotation(Editor *editor_ptr, SingularAnnotation *singularAnnotation);

    SEMSIM_API void Editor_removePhysicalEntity(Editor *editor_ptr, PhysicalEntity *physicalEntity);

    SEMSIM_API void Editor_removePhysicalProcess(Editor *editor_ptr, PhysicalProcess *physicalProcess);

    SEMSIM_API void Editor_removePhysicalForce(Editor *editor_ptr, PhysicalForce *physicalForce);

    SEMSIM_API void Editor_removePersonalInformation(Editor *editor_ptr, PersonalInformation *information);

    SEMSIM_API void Editor_checkValidMetaid(Editor *editor_ptr, const char *id);

    SEMSIM_API char *Editor_getMetaId(Editor *editor_ptr, int index);

    SEMSIM_API char *Editor_getXml(Editor *editor_ptr);

    SEMSIM_API int Editor_getNumMetaIds(Editor *editor_ptr);

    SEMSIM_API void Editor_delete(Editor *editor_ptr);

    SEMSIM_API char*Editor_getArchiveUri(Editor *editor_ptr);
    SEMSIM_API char*Editor_getLocalUri(Editor *editor_ptr);
    SEMSIM_API char*Editor_getModelUri(Editor *editor_ptr);
    SEMSIM_API char*Editor_getRepositoryUri(Editor *editor_ptr);
    SEMSIM_API void Editor_addCreator(Editor *editor_ptr, const char* orcid_id);
    SEMSIM_API void Editor_addCurator(Editor *editor_ptr, const char* orcid_id);
    SEMSIM_API void Editor_addTaxon(Editor *editor_ptr, const char *taxon_id);
    SEMSIM_API void Editor_addPubmed(Editor *editor_ptr, const char *pubmedid);
    SEMSIM_API void Editor_addDescription(Editor *editor_ptr, const char *date);
    SEMSIM_API void Editor_addDateCreated(Editor *editor_ptr, const char *date);
    SEMSIM_API void Editor_addParentModel(Editor *editor_ptr, const char *biomod_id);

/*********************************************************************
 * SingularAnnotation class methods
 */
    SEMSIM_API SingularAnnotation *SingularAnnotation_new(Editor *editor_ptr);

    SEMSIM_API void SingularAnnotation_delete(SingularAnnotation *singularAnnotation);

    SEMSIM_API SingularAnnotation *
    SingularAnnotation_setAbout(SingularAnnotation *singular_annotation, const char *about);

    SEMSIM_API SingularAnnotation *
    SingularAnnotation_setPredicate(SingularAnnotation *singular_annotation, const char *namespace_, const char *term);

    SEMSIM_API SingularAnnotation *SingularAnnotation_setPredicateFromUri(
            SingularAnnotation *singular_annotation, const char *uri);

    SEMSIM_API SingularAnnotation *SingularAnnotation_setResourceLiteral(
            SingularAnnotation *singular_annotation, const char *literal);

    SEMSIM_API SingularAnnotation *
    SingularAnnotation_setResourceUri(SingularAnnotation *singular_annotation, const char *identifiers_uri);

    SEMSIM_API SingularAnnotation *
    SingularAnnotation_setResourceBlank(SingularAnnotation *singular_annotation, const char *blank_id);

    SEMSIM_API char *SingularAnnotation_getAbout(SingularAnnotation *singular_annotation);

    SEMSIM_API char *
    SingularAnnotation_str(SingularAnnotation *singular_annotation, const char *format, const char *base_uri);

    SEMSIM_API char *SingularAnnotation_getPredicate(SingularAnnotation *singular_annotation);

    SEMSIM_API char *SingularAnnotation_getResource(SingularAnnotation *singular_annotation);

/*********************************************************************
 * PhysicalEntity class methods
 */
    SEMSIM_API PhysicalEntity *PhysicalEntity_new(Editor *editor_ptr);

    SEMSIM_API void PhysicalEntity_delete(PhysicalEntity *physical_entity_ptr);

    SEMSIM_API void PhysicalEntity_freeAll(PhysicalEntity *physical_entity_ptr);

    SEMSIM_API PhysicalEntity *PhysicalEntity_setPhysicalProperty(
            PhysicalEntity *physical_entity_ptr, const char *subject_metaid, const char *physical_property);

    SEMSIM_API PhysicalEntity *PhysicalEntity_setIdentity(
            PhysicalEntity *physical_entity_ptr, const char *identity_resource);

    SEMSIM_API PhysicalEntity *PhysicalEntity_addLocation(
            PhysicalEntity *physical_entity_ptr, const char *location_resource);


    SEMSIM_API char *PhysicalEntity_getAbout(PhysicalEntity *physical_entity_ptr);

    SEMSIM_API char *PhysicalEntity_getIdentity(PhysicalEntity *physical_entity_ptr);

    SEMSIM_API int PhysicalEntity_getNumLocations(PhysicalEntity *physicalEntity);

    SEMSIM_API char *PhysicalEntity_getLocation(PhysicalEntity *physical_entity_ptr, int index);

    SEMSIM_API char *PhysicalEntity_str(PhysicalEntity *physical_entity_ptr, const char *format, const char *base_uri);

/*********************************************************************
 * PhysicalProcess class methods
 */
    SEMSIM_API PhysicalProcess *PhysicalProcess_new(Editor *editor_ptr);

    SEMSIM_API void PhysicalProcess_delete(PhysicalProcess *physicalProcess);

    SEMSIM_API void PhysicalProcess_freeAll(PhysicalProcess *physicalProcess);

    SEMSIM_API PhysicalProcess *PhysicalProcess_setPhysicalProperty(
            PhysicalProcess *physical_process, const char *subject_metaid, const char *physical_property);

    SEMSIM_API PhysicalProcess *PhysicalProcess_addSource(
            PhysicalProcess *physical_process, double multiplier,
            const char *physical_entity_reference);

    SEMSIM_API PhysicalProcess *PhysicalProcess_addSink(
            PhysicalProcess *physical_process, double multiplier,
            const char *physical_entity_reference);

    SEMSIM_API PhysicalProcess *PhysicalProcess_addMediator(
            PhysicalProcess *physical_process, double multiplier,
            const char *physical_entity_reference);

    SEMSIM_API char *
    PhysicalProcess_str(PhysicalProcess *physical_process_ptr, const char *format, const char *base_uri);


/*********************************************************************
 * PhysicalForce class methods
 */
    SEMSIM_API PhysicalForce *PhysicalForce_new(Editor *editor_ptr);


    /*
     * @brief deletes physical force excluding all
     * nodes associated with it.
     */
    SEMSIM_API void PhysicalForce_delete(PhysicalForce *physicalForce);

    /*
     * @brief deletes physical force including all
     * nodes associated with it.
     */
    SEMSIM_API void PhysicalForce_freeAll(PhysicalForce *physical_force_ptr);

    SEMSIM_API PhysicalForce *PhysicalForce_addSource(
            PhysicalForce *physical_force_ptr, double multiplier,
            const char *physical_entity_reference);

    SEMSIM_API PhysicalForce *PhysicalForce_addSink(
            PhysicalForce *physical_force_ptr, double multiplier,
            const char *physical_entity_reference);

    SEMSIM_API PhysicalForce *PhysicalForce_setPhysicalProperty(
            PhysicalForce *physical_force_ptr, const char *subject_metaid, const char *physical_property);

    SEMSIM_API int PhysicalForce_getNumSources(PhysicalForce *physicalForce);

    SEMSIM_API int PhysicalForce_getNumSinks(PhysicalForce *physicalForce);

    SEMSIM_API char *PhysicalForce_str(PhysicalForce *physical_force_ptr, const char *format, const char *base_uri);

    SEMSIM_API char *PhysicalForce_getAbout(PhysicalForce *physical_force_ptr);

/*********************************************************************
 * PersonalInformation class methods
 */

    SEMSIM_API PersonalInformation *PersonalInformation_new(Editor *editor_ptr);

    SEMSIM_API void PersonalInformation_delete(PersonalInformation* information);

    SEMSIM_API char *PersonalInformation_getLocalUri(PersonalInformation *information);

    SEMSIM_API void PersonalInformation_setLocalUri(PersonalInformation *information, const char *localUri);

    SEMSIM_API PersonalInformation *PersonalInformation_addCreator(PersonalInformation *information, const char *value);

//    SEMSIM_API PersonalInformation *PersonalInformation_addCurator(PersonalInformation *information, const char*value);

    SEMSIM_API PersonalInformation *PersonalInformation_addName(PersonalInformation *information, const char *value);

    SEMSIM_API PersonalInformation *PersonalInformation_addMbox(PersonalInformation *information, const char *value);

    SEMSIM_API PersonalInformation *
    PersonalInformation_addAccountName(PersonalInformation *information, const char *value);

    SEMSIM_API PersonalInformation *
    PersonalInformation_addAccountServiceHomepage(PersonalInformation *information, const char *value);

    SEMSIM_API PersonalInformation *
    PersonalInformation_addFoafBlank(PersonalInformation *information, const char *predicate, const char *blank_value);

    SEMSIM_API PersonalInformation *
    PersonalInformation_addFoafUri(PersonalInformation *information, const char *predicate, const char *uri_value);

    SEMSIM_API PersonalInformation *
    PersonalInformation_addFoafLiteral(PersonalInformation *information, const char *predicate,
                                       const char *literal_value);

    SEMSIM_API PersonalInformation *
    PersonalInformation_addFoaf(PersonalInformation *information, const char *predicate, const LibrdfNode &value_node);

    SEMSIM_API char *PersonalInformation_getMetaid(PersonalInformation *information);

    SEMSIM_API void PersonalInformation_setMetaid(PersonalInformation *information, const char *metaid);

    SEMSIM_API char *PersonalInformation_getModelUri(PersonalInformation *information);

    SEMSIM_API void PersonalInformation_setModelUri(PersonalInformation *information, const char *modelUri);


#ifdef __cplusplus
    }
#endif
}

#endif //LIBOMEXMETA_OMEXMETACAPI_H

























