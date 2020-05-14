//
// Created by Ciaran on 5/8/2020.
//

#ifndef LIBSEMSIM_SEMSIMCAPI_H
#define LIBSEMSIM_SEMSIMCAPI_H

#include "semsim/RDF.h"
#include "semsim/Editor.h"
#include "semsim/XmlAssistant.h"

namespace semsim {

#ifdef __cplusplus
    extern "C" {
#endif

/***************************************************
 * RDF class methods
 */

    semsim::RDF *libsemsim_new_rdf();

    void RDF_free(semsim::RDF *rdf_ptr);

    char *RDF_getBaseUri(semsim::RDF *rdf_ptr);

    void RDF_setBaseUri(semsim::RDF *rdf_ptr, const char *uri);

    const char *RDF_toString(semsim::RDF *rdf_ptr, const char *format, const char *base_uri);

    void RDF_fromString(semsim::RDF *rdf_ptr, const char *str, const char *format);

    const char *RDF_queryResultsAsStr(semsim::RDF *rdf_ptr, const char *query_str, const char *results_format);

    int RDF_size(semsim::RDF *rdf_ptr);

    Editor *RDF_toEditor(semsim::RDF *rdf_ptr, const char *xml, semsim::XmlAssistantType type);

//RDF_toFile(semsim::RDF* rdf_ptr, );
//RDF_listOptions(semsim::RDF* rdf_ptr, );
//RDF_setNamespaces(semsim::RDF* rdf_ptr, );
//RDF_getNamespaces(semsim::RDF* rdf_ptr, );
//semsim::RDF* RDF_fromUrl(semsim::RDF* rdf_ptr, const char* url, const char* filename, const char* format);
//semsim::RDF* RDF_fromXML(semsim::RDF* rdf_ptr, const char* filename, const char* format);
//semsim::RDF* RDF_fromFile(semsim::RDF* rdf_ptr, const char* filename, const char* format);
//semsim::RDF* RDF_fromOmex(semsim::RDF* rdf_ptr, const char* filename_or_uri, const char* format);

/*********************************************
 *  Editor class
 */

    Editor *libsemsim_new_editor(semsim::RDF *rdf_ptr);

    void Editor_addNamespace(Editor *editor_ptr, const char *namespace_, const char *prefix);

    void Editor_addSingleAnnotation(Editor *editor_ptr, SingularAnnotation *singularAnnotation);

//void Editor_addPhysicalEntity(Editor* editor_ptr, )
//void Editor_addPhysicalProcess(Editor* editor_ptr, )
//void Editor_addPhysicalForce(Editor* editor_ptr, )
//void Editor_checkValidMetaid(Editor* editor_ptr, )

/*********************************************************************
 * Editor class methods
 */

/*********************************************************************
 * SingularAnnotation class methods
 */
    SingularAnnotation *new_singular_annotation(Editor *editor_ptr);

    SingularAnnotation *SingularAnnotation_setAbout(SingularAnnotation *singular_annotation, const char *about);

    SingularAnnotation *
    SingularAnnotation_setPredicate(SingularAnnotation *singular_annotation, const char *namespace_, const char *term);

    SingularAnnotation *
    SingularAnnotation_setPredicateNew(SingularAnnotation *singular_annotation, const char *namespace_,
                                       const char *term, const char *prefix);

    SingularAnnotation *
    SingularAnnotation_setResourceLiteral(SingularAnnotation *singular_annotation, const char *literal);

    SingularAnnotation *
    SingularAnnotation_setResourceUri(SingularAnnotation *singular_annotation, const char *identifiers_uri);

    SingularAnnotation *
    SingularAnnotation_setResourceBlank(SingularAnnotation *singular_annotation, const char *blank_id);

    const char *SingularAnnotation_getAbout(SingularAnnotation *singular_annotation);

    const char *
    SingularAnnotation_str(SingularAnnotation *singular_annotation, const char *format, const char *base_uri);

    const char *SingularAnnotation_getPredicate(SingularAnnotation *singular_annotation);

    const char *SingularAnnotation_getResource(SingularAnnotation *singular_annotation);

/*********************************************************************
 * PhysicalEntity class methods
 */

/*********************************************************************
 * PhysicalProcess class methods
 */

/*********************************************************************
 * PhysicalForce class methods
 */


#ifdef __cplusplus
    }
#endif
}

#endif //LIBSEMSIM_SEMSIMCAPI_H

























