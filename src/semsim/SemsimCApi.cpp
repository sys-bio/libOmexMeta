//
// Created by Ciaran on 5/8/2020.
//

#include "semsim/SemsimCApi.h"
#include <cstring>
#include "semsim/SemsimUtils.h"

namespace semsim {
    semsim::RDF *libsemsim_new_rdf() {
        return new semsim::RDF();
    }

    void RDF_free(semsim::RDF *rdf_ptr) {
        free(rdf_ptr);
    }

    void RDF_fromString(semsim::RDF *rdf_ptr, const char *str, const char *format) {
        semsim::RDF rdf = semsim::RDF::fromString(str, format);
        *rdf_ptr = rdf;
    }

    const char *RDF_toString(semsim::RDF *rdf_ptr, const char *format, const char *base_uri) {
        // do not return a temporary object:
        static std::string s = rdf_ptr->toString(format, base_uri);
        const char *output_str = (const char *) s.c_str();
        return output_str;
    }

    char *RDF_getBaseUri(semsim::RDF *rdf_ptr) {
        std::string str = rdf_ptr->getBaseUriAsString();
        char *cstr = (char *) malloc(str.size());
        strcpy(cstr, str.c_str());
        return cstr;
    }

    void RDF_setBaseUri(semsim::RDF *rdf_ptr, const char *uri) {
        rdf_ptr->setBaseUri(uri);
    }

    const char *RDF_queryResultsAsStr(semsim::RDF *rdf_ptr, const char *query_str, const char *results_format) {
        static std::string query_results = rdf_ptr->queryResultsAsStr(query_str, results_format);
        return query_results.c_str();
    }

    int RDF_size(semsim::RDF *rdf_ptr) {
        return rdf_ptr->size();
    }

    Editor *RDF_toEditor(semsim::RDF *rdf_ptr, const char *xml, semsim::XmlAssistantType type) {
        return rdf_ptr->toEditorPtr(xml, type);
    }

/*********************************************************************
 * Editor class methods
 */

    void Editor_addNamespace(Editor *editor_ptr, const char *namespace_, const char *prefix) {
        editor_ptr->addNamespace(namespace_, prefix);
    }

    void Editor_addSingleAnnotation(Editor *editor_ptr, SingularAnnotation *singularAnnotation) {
        editor_ptr->addSingleAnnotation(*singularAnnotation);
    }


/*********************************************************************
 * SingularAnnotation class methods
 */
    SingularAnnotation *new_singular_annotation(Editor *editor_ptr) {
        return new SingularAnnotation(editor_ptr->getWorld());
    }

    void free_singular_annotation(SingularAnnotation *singularAnnotationPtr) {
        free(singularAnnotationPtr);
    }

    SingularAnnotation *SingularAnnotation_setAbout(SingularAnnotation *singular_annotation, const char *about) {
        singular_annotation->setAbout(about);
        return singular_annotation;
    };


    SingularAnnotation *SingularAnnotation_setPredicate(
            SingularAnnotation *singular_annotation, const char *namespace_, const char *term) {
        singular_annotation->setPredicate(namespace_, term);
        return singular_annotation;
    }

    SingularAnnotation *SingularAnnotation_setPredicateNew(
            SingularAnnotation *singular_annotation, const char *namespace_,
            const char *term, const char *prefix) {
        singular_annotation->setPredicateNew(namespace_, term, prefix);
        return singular_annotation;
    }

    SingularAnnotation *
    SingularAnnotation_setResourceLiteral(SingularAnnotation *singular_annotation, const char *literal) {
        singular_annotation->setResourceLiteral(literal);
        return singular_annotation;
    }

    SingularAnnotation *
    SingularAnnotation_setResourceUri(SingularAnnotation *singular_annotation, const char *identifiers_uri) {
        singular_annotation->setResourceUri(identifiers_uri);
        return singular_annotation;
    }

    SingularAnnotation *
    SingularAnnotation_setResourceBlank(SingularAnnotation *singular_annotation, const char *blank_id) {
        singular_annotation->setResourceBlank(blank_id);
        return singular_annotation;
    }

    const char *SingularAnnotation_getAbout(SingularAnnotation *singular_annotation) {
        std::string about = singular_annotation->getAbout();
        char *cstr = (char *) malloc(about.size());
        strcpy(cstr, about.c_str());
        return cstr;
    }

    const char *SingularAnnotation_getPredicate(SingularAnnotation *singular_annotation) {
        std::string predicate_str = singular_annotation->getPredicatePtr()->str();
        char *cstr = (char*) malloc(predicate_str.size());
        strcpy(cstr, predicate_str.c_str());
        return cstr;
    }

    const char *SingularAnnotation_getResource(SingularAnnotation *singular_annotation) {
        std::string resource = singular_annotation->getResource().str();
        char* cstr = (char*) malloc(resource.size());
        strcpy(cstr, resource.c_str());
        return cstr;
    }

    const char *SingularAnnotation_str(
            SingularAnnotation *singular_annotation, const char *format, const char *base_uri) {
        std::string str = singular_annotation->str(format, base_uri);
        char* cstr = (char*) malloc(str.size());
        strcpy(cstr, str.c_str());
        return cstr;
    }
/*********************************************************************
 * PhysicalEntity class methods
 */

/*********************************************************************
 * PhysicalProcess class methods
 */

/*********************************************************************
 * PhysicalForce class methods
 */


}































