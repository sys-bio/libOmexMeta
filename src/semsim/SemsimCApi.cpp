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
        char *cstr = (char *) malloc(predicate_str.size());
        strcpy(cstr, predicate_str.c_str());
        return cstr;
    }

    const char *SingularAnnotation_getResource(SingularAnnotation *singular_annotation) {
        std::string resource = singular_annotation->getResource().str();
        char *cstr = (char *) malloc(resource.size());
        strcpy(cstr, resource.c_str());
        return cstr;
    }

    const char *SingularAnnotation_str(
            SingularAnnotation *singular_annotation, const char *format, const char *base_uri) {
        std::string str = singular_annotation->str(format, base_uri);
        char *cstr = (char *) malloc(str.size());
        strcpy(cstr, str.c_str());
        return cstr;
    }

/*********************************************************************
 * PhysicalEntity class methods
 */
    PhysicalEntity *new_physical_entity(Editor *editor_ptr) {
        return new PhysicalEntity(editor_ptr->getWorld(), editor_ptr->getModel());
    }

    void free_physical_entity(PhysicalEntity *physical_entity_ptr) {
        free(physical_entity_ptr);
    }

    PhysicalEntity *PhysicalEntity_setAbout(PhysicalEntity *physical_entity_ptr, const char *about) {
        physical_entity_ptr->setAbout(about);
        return physical_entity_ptr;
    }

    PhysicalEntity *PhysicalEntity_setPhysicalProperty(
            PhysicalEntity *physical_entity_ptr, const char *physical_property) {
        physical_entity_ptr->setPhysicalProperty(physical_property);
        return physical_entity_ptr;
    }

    PhysicalEntity *PhysicalEntity_setIdentity(PhysicalEntity *physical_entity_ptr, const char *identity_resource) {
        physical_entity_ptr->setIdentity(identity_resource);
        return physical_entity_ptr;
    }

    PhysicalEntity *PhysicalEntity_addLocation(PhysicalEntity *physical_entity_ptr, const char *location_resource) {
        physical_entity_ptr->addLocation(location_resource);
        return physical_entity_ptr;
    }

    const char *PhysicalEntity_getAbout(PhysicalEntity *physical_entity_ptr) {
        std::string about = physical_entity_ptr->getAbout().str();
        char *cstr = (char *) malloc(about.size());
        strcpy(cstr, about.c_str());
        return cstr;
    }

    const char *PhysicalEntity_getPhysicalProperty(PhysicalEntity *physical_entity_ptr) {
        std::string physical_property = physical_entity_ptr->getPhysicalProperty().str();
        char *cstr = (char *) malloc(physical_property.size());
        strcpy(cstr, physical_property.c_str());
        return cstr;
    }

    const char *PhysicalEntity_getIdentity(PhysicalEntity *physical_entity_ptr) {
        std::string identity = physical_entity_ptr->getIdentityResource().str();
        char *cstr = (char *) malloc(identity.size());
        strcpy(cstr, identity.c_str());
        return cstr;

    }

    int PhysicalEntity_getNumLocations(PhysicalEntity *physicalEntity) {
        return physicalEntity->getNumLocations();
    }

    char **PhysicalEntity_getLocations(PhysicalEntity *physical_entity_ptr) {
        Resources locations = physical_entity_ptr->getLocationResources();
        char **arr = (char **) malloc(locations.size() * sizeof(char *));

        for (int i = 0; i < locations.size(); i++) {
            arr[i] = (char *) malloc(strlen(locations[i].str().c_str()) + 1);
            strcpy(arr[i], locations[i].str().c_str());
        }

        return arr;
    }

    const char *PhysicalEntity_str(PhysicalEntity *physical_entity_ptr, const char *format, const char *base_uri) {
        std::string str = physical_entity_ptr->toTriples().str(format, base_uri);
        char *cstr = (char *) malloc(str.size());
        strcpy(cstr, str.c_str());
        return cstr;
    }


/*********************************************************************
 * PhysicalProcess class methods
 */
    PhysicalProcess *new_physical_process(Editor *editor_ptr) {
        return new PhysicalProcess(editor_ptr->getWorld(), editor_ptr->getModel());
    }

    void free_physical_process(PhysicalProcess *physical_process_ptr) {
        free(physical_process_ptr);
    }

    PhysicalProcess *PhysicalProcess_setAbout(PhysicalProcess *physical_process, const char *about) {
        physical_process->setAbout(about);
        return physical_process;
    }

    PhysicalProcess *
    PhysicalProcess_setPhysicalProperty(PhysicalProcess *physical_process, const char *physical_property) {
        physical_process->setPhysicalProperty(physical_property);
        return physical_process;

    }

    PhysicalProcess *
    PhysicalProcess_addSource(PhysicalProcess *physical_process, const char *source_metaid, double multiplier,
                              const char *physical_entity_reference) {
        physical_process->addSource(source_metaid, multiplier, physical_entity_reference);
        return physical_process;

    }

    PhysicalProcess *
    PhysicalProcess_addSink(PhysicalProcess *physical_process, const char *sink_metaid, double multiplier,
                            const char *physical_entity_reference) {
        physical_process->addSink(sink_metaid, multiplier, physical_entity_reference);
        return physical_process;

    }

    PhysicalProcess *
    PhysicalProcess_addMediator(PhysicalProcess *physical_process, const char *mediator_metaid, double multiplier,
                                const char *physical_entity_reference) {
        physical_process->addMediator(mediator_metaid, multiplier, physical_entity_reference);
        return physical_process;

    }

    const char *PhysicalProcess_str(PhysicalProcess *physical_process_ptr, const char *format, const char *base_uri) {
        std::string str = physical_process_ptr->toTriples().str(format, base_uri);
        char *cstr = (char *) malloc(str.size());
        strcpy(cstr, str.c_str());
        return cstr;
    }

    const char *PhysicalProcess_getAbout(PhysicalProcess *physical_process_ptr) {
        std::string about = physical_process_ptr->getAbout().str();
        char *cstr = (char *) malloc(about.size());
        strcpy(cstr, about.c_str());
        return cstr;
    }

    const char *PhysicalProcess_getPhysicalProperty(PhysicalProcess *physical_process_ptr) {
        std::string pp = physical_process_ptr->getPhysicalProperty().str();
        char *cstr = (char *) malloc(pp.size());
        strcpy(cstr, pp.c_str());
        return cstr;
    }

    int PhysicalProcess_getNumSources(PhysicalProcess *physicalProcess) {
        return physicalProcess->getNumSources();
    }

    int PhysicalProcess_getNumSinks(PhysicalProcess *physicalProcess) {
        return physicalProcess->getNumSinks();
    }

    int PhysicalProcess_getNumMediators(PhysicalProcess *physicalProcess) {
        return physicalProcess->getNumMediators();
    }

//    const char** PhysicalProcess_getSinks(PhysicalProcess* physical_process_ptr);
//    const char** PhysicalProcess_getMediators(PhysicalProcess* physical_process_ptr);

/*********************************************************************
 * PhysicalForce class methods
 */
    PhysicalForce *new_physical_force(Editor *editor_ptr) {
        return new PhysicalForce(editor_ptr->getWorld(), editor_ptr->getModel());
    }

    PhysicalForce *PhysicalForce_setAbout(PhysicalForce *physical_force_ptr, const char *about) {
        physical_force_ptr->setAbout(about);
        return physical_force_ptr;
    }

    PhysicalForce *PhysicalForce_addSource(
            PhysicalForce *physical_force_ptr, const char *source_metaid,
            double multiplier,
            const char *physical_entity_reference) {
        physical_force_ptr->addSource(source_metaid, multiplier, physical_entity_reference);
        return physical_force_ptr;

    }

    PhysicalForce *PhysicalForce_addSink(PhysicalForce *physical_force_ptr, const char *sink_metaid,
                                         double multiplier,
                                         const char *physical_entity_reference) {
        physical_force_ptr->addSink(sink_metaid, multiplier, physical_entity_reference);
        return physical_force_ptr;

    }

    PhysicalForce *PhysicalForce_setPhysicalProperty(PhysicalForce *physical_force_ptr, const char *physical_property) {
        physical_force_ptr->setPhysicalProperty(physical_property);
        return physical_force_ptr;

    }

    int PhysicalForce_getNumSources(PhysicalForce *physicalForce) {
        return physicalForce->getNumSources();
    }

    int PhysicalForce_getNumSinks(PhysicalForce *physicalForce) {
        return physicalForce->getNumSinks();
    }

    const char *PhysicalForce_str(PhysicalForce *physical_force_ptr, const char *format, const char *base_uri) {
        std::string str = physical_force_ptr->toTriples().str(format, base_uri);
        char *cstr = (char *) malloc(str.size());
        strcpy(cstr, str.c_str());
        return cstr;
    }


}




























