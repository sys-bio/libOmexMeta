//
// Created by Ciaran on 5/8/2020.
//

#ifndef LIBSEMSIM_SEMSIMCAPI_H
#define LIBSEMSIM_SEMSIMCAPI_H

#include "semsim/RDF.h"
#include "semsim/Editor.h"
#include "semsim/SemsimXmlAssistant.h"
#include "semsim/PhysicalEntity.h"
#include "semsim/PhysicalProcess.h"
#include "semsim/PhysicalForce.h"
#include <cstring>
#include "semsim/SemsimUtils.h"
#include "semsim/Preproc.h"

namespace semsim {

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

    SEMSIM_API void free_world(librdf_world *world);

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

    SEMSIM_API void Editor_checkValidMetaid(Editor *editor_ptr, const char *id);

    SEMSIM_API char *Editor_getMetaId(Editor *editor_ptr, int index);

    SEMSIM_API char *Editor_getXml(Editor *editor_ptr);

    SEMSIM_API int Editor_getNumMetaIds(Editor *editor_ptr);

    SEMSIM_API void Editor_delete(Editor *editor_ptr);


/*********************************************************************
 * SingularAnnotation class methods
 */
    SEMSIM_API SingularAnnotation *SingularAnnotation_new(Editor *editor_ptr);

    SEMSIM_API void SingularAnnotation_delete(SingularAnnotation *singularAnnotation);

    SEMSIM_API SingularAnnotation *SingularAnnotation_setAbout(SingularAnnotation *singular_annotation, const char *about);

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

    SEMSIM_API char *SingularAnnotation_str(SingularAnnotation *singular_annotation, const char *format, const char *base_uri);

    SEMSIM_API char *SingularAnnotation_getPredicate(SingularAnnotation *singular_annotation);

    SEMSIM_API char *SingularAnnotation_getResource(SingularAnnotation *singular_annotation);

/*********************************************************************
 * PhysicalEntity class methods
 */
    SEMSIM_API PhysicalEntity *PhysicalEntity_new(Editor *editor_ptr);

    SEMSIM_API void PhysicalEntity_delete(PhysicalEntity *physical_entity_ptr);

    SEMSIM_API void PhysicalEntity_freeAll(PhysicalEntity *physical_entity_ptr);

    SEMSIM_API PhysicalEntity *PhysicalEntity_setAbout(PhysicalEntity *physical_entity_ptr, const char *about);

    SEMSIM_API PhysicalEntity *PhysicalEntity_setPhysicalProperty(
            PhysicalEntity *physical_entity_ptr, const char *subject_metaid, const char *physical_property);

    SEMSIM_API PhysicalEntity *PhysicalEntity_setIdentity(
            PhysicalEntity *physical_entity_ptr, const char *identity_resource);

    SEMSIM_API PhysicalEntity *PhysicalEntity_addLocation(
            PhysicalEntity *physical_entity_ptr, const char *location_resource);


    SEMSIM_API char *PhysicalEntity_getAbout(PhysicalEntity *physical_entity_ptr);

//    char *PhysicalEntity_getPhysicalProperty(PhysicalEntity *physical_entity_ptr);

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

    SEMSIM_API PhysicalProcess *PhysicalProcess_setAbout(
            PhysicalProcess *physical_process, const char *about);

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

    SEMSIM_API char *PhysicalProcess_str(PhysicalProcess *physical_process_ptr, const char *format, const char *base_uri);

    SEMSIM_API char *PhysicalProcess_getAbout(PhysicalProcess *physical_process_ptr);

//    char *PhysicalProcess_getPhysicalProperty(PhysicalProcess *physical_process_ptr);

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

    SEMSIM_API PhysicalForce *PhysicalForce_setAbout(
            PhysicalForce *physical_force_ptr, const char *about);

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

//    char *PhysicalForce_getPhysicalProperty(PhysicalForce *physical_force_ptr);


#ifdef __cplusplus
    }
#endif
}

#endif //LIBSEMSIM_SEMSIMCAPI_H

























