//
// Created by Ciaran on 5/8/2020.
//

#include "omexmeta/OmexMetaCApi.h"

#include <utility>


namespace omexmeta {
    void free_c_char_star(char *c) {
        if (c != nullptr)
            free(c);
    }

    /*
     * For testing.
     */
    char *_func_that_returns_dynamic_alloc_str() {
        std::string str = "ADynamicallyAllocatedStringForTesting";
        char *cstr = (char *) malloc((str.size() + 1) * sizeof(char *));
        strcpy(cstr, str.c_str());
        return cstr;
    }

    /*
     * for testing
     */
    char **_func_that_returns_dynamic_alloc_char_star_star() {
        std::vector<std::string> vec = {"A", "Dynamically", "Allocated", "List", "of", "Strings"};
        char **arr = (char **) malloc((vec.size() + 1) * sizeof(char *));

        for (int i = 0; i < vec.size(); i++) {
            arr[i] = (char *) malloc(strlen(vec[i].c_str()) + sizeof(char));
            strcpy(arr[i], vec[i].c_str());
        }
        return arr;
    }

/*************************************************************
 *  librdf_world methods
 */

    /*
     * world is statically allocated. When we
     * free a world instance, its best to replace it
     * immediately
     */
    [[maybe_unused]] void free_world(librdf_world *world) {
        if (world != nullptr) {
            World::free(world);
            world = World::getWorld();
        }
    }

/*************************************************************
 *  RDF methods
 */

    RDF *RDF_new(const char *storage_type, const char *storage_name,
                 const char *storage_options, const char *model_options) {
        RDF *rdf_ptr = new RDF(storage_type, storage_name, storage_options, model_options);
        if (!rdf_ptr) {
            throw NullPointerException("NullPointerException: RDF_fromString(): \"rdf_ptr\" is nullptr");
        }
        return rdf_ptr;
    }

    void RDF_delete(RDF *rdf_ptr) {
        delete rdf_ptr;
    }

    RDF *RDF_fromString(const char *str, const char *format, const char *storage_type,
                        const char *storage_name,
                        const char *storage_options, const char *model_options) {
        RDF *rdf = RDF_new();
        rdf->addFromString(str, format);
        return rdf;
    }

    void RDF_addFromString(RDF *rdf_ptr, const char *str, const char *format) {
        rdf_ptr->addFromString(str, format);
    }

    RDF *RDF_fromUri(const char *uri_string, const char *format, const char *storage_type, const char *storage_name,
                     const char *storage_options, const char *model_options) {
        RDF *rdf = RDF_new();
        rdf->addFromUri(uri_string, format);
        return rdf;
    }

    void RDF_addFromUri(RDF *rdf_ptr, const char *uri_string, const char *format) {
        rdf_ptr->addFromUri(uri_string, format);
    }

    RDF *RDF_fromFile(const char *filename, const char *format, const char *storage_type, const char *storage_name,
                      const char *storage_options, const char *model_options) {
        RDF *rdf = RDF_new();
        rdf->addFromFile(filename, format);
        return rdf;
    }

    void RDF_addFromFile(RDF *rdf_ptr, const char *uri_string, const char *format) {
        rdf_ptr->addFromFile(uri_string, format);
    }

    char *RDF_toString(RDF *rdf_ptr, const char *format, const char *base_uri) {
        // do not return a temporary object:
        std::string s = rdf_ptr->toString(format, base_uri);
        char *cstr = (char *) malloc((s.size() + 1) * sizeof(char *));
        strcpy(cstr, s.c_str());
        return cstr;
    }

    void RDF_toFile(RDF *rdf_ptr, const char* format, const char *filename) {
        rdf_ptr->toFile(filename, format);
    }

    char *RDF_query(RDF *rdf_ptr, const char *query_str, const char *results_format) {
        std::string results = rdf_ptr->query(query_str, results_format);
        char *s = (char *) malloc((results.size() + 1) * sizeof(char *));
        strcpy(s, results.c_str());
        return s;
    }

    int RDF_size(RDF *rdf_ptr) {
        return rdf_ptr->size();
    }

    void RDF_setRepositoryUri(RDF *rdf_ptr, const char* repository_uri) {
        rdf_ptr->setRepositoryUri(std::move(repository_uri));
    }

    void RDF_setArchiveUri(RDF *rdf_ptr, const char* archive_uri) {
        rdf_ptr->setArchiveUri(std::move(archive_uri));
    }

    void RDF_setModelUri(RDF *rdf_ptr, const char* model_uri) {
        rdf_ptr->setModelUri(std::move(model_uri));
    }

    char *RDF_getRepositoryUri(RDF *rdf_ptr) {
        const std::string &str = rdf_ptr->getRepositoryUri();
        char *cstr = (char *) malloc((str.size() + 1) * sizeof(char *));
        strcpy(cstr, str.c_str());
        return cstr;
    }

    char *RDF_getArchiveUri(RDF *rdf_ptr) {
        const std::string &str = rdf_ptr->getArchiveUri();
        char *cstr = (char *) malloc((str.size() + 1) * sizeof(char *));
        strcpy(cstr, str.c_str());
        return cstr;
    }

    char *RDF_getModelUri(RDF *rdf_ptr) {
        const std::string &str = rdf_ptr->getModelUri();
        char *cstr = (char *) malloc((str.size() + 1) * sizeof(char *));
        strcpy(cstr, str.c_str());
        return cstr;
    }

    char *RDF_getLocalUri(RDF *rdf_ptr) {
        const std::string &str = rdf_ptr->getLocalUri();
        char *cstr = (char *) malloc((str.size() + 1) * sizeof(char *));
        strcpy(cstr, str.c_str());
        return cstr;
    }

    Editor *RDF_toEditor(RDF *rdf_ptr, const char *xml, bool generate_new_metaids) {
        return rdf_ptr->toEditorPtr(xml, generate_new_metaids);
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

    void Editor_addPhysicalEntity(Editor *editor_ptr, PhysicalEntity *physicalEntity) {
        editor_ptr->addPhysicalEntity(*physicalEntity);
    }

    void Editor_addPhysicalProcess(Editor *editor_ptr, PhysicalProcess *physicalProcess) {
        editor_ptr->addPhysicalProcess(*physicalProcess);
    }

    void Editor_addPhysicalForce(Editor *editor_ptr, PhysicalForce *physicalForce) {
        editor_ptr->addPhysicalForce(*physicalForce);
    }

    void Editor_addPersonalInformation(Editor *editor_ptr, PersonalInformation *personalInformation) {
        editor_ptr->addPersonalInformation(personalInformation);
    }

    void Editor_removeSingleAnnotation(Editor *editor_ptr, SingularAnnotation *singularAnnotation) {
        editor_ptr->removeSingleAnnotation(*singularAnnotation);
    }

    void Editor_removePhysicalEntity(Editor *editor_ptr, PhysicalEntity *physicalEntity) {
        editor_ptr->removePhysicalEntity(*physicalEntity);
    }

    void Editor_removePhysicalProcess(Editor *editor_ptr, PhysicalProcess *physicalProcess) {
        editor_ptr->removePhysicalProcess(*physicalProcess);
    }

    void Editor_removePhysicalForce(Editor *editor_ptr, PhysicalForce *physicalForce) {
        editor_ptr->removePhysicalForce(*physicalForce);
    }

    void Editor_removePersonalInformation(Editor *editor_ptr, PersonalInformation *information) {
        editor_ptr->removePersonalInformation(information);
    }

    void Editor_checkValidMetaid(Editor *editor_ptr, const char *id) {
        editor_ptr->checkValidMetaid(id);
    }

    char *Editor_getMetaId(Editor *editor_ptr, int index) {
        std::string str = editor_ptr->getMetaids()[index];
        auto cstr = (char *) malloc((str.size() + 1) * sizeof(char *));
        strcpy(cstr, str.c_str());
        return cstr;
    }

    int Editor_getNumMetaIds(Editor *editor_ptr) {
        return editor_ptr->getMetaids().size();
    }

    /*
     * @brief get the xml from the editor
     *
     * The returned string is owned by the caller.
     */
    char *Editor_getXml(Editor *editor_ptr) {
        const std::string &str = editor_ptr->getXml();
        char *cstr = (char *) malloc((str.size() + 1) * sizeof(char *));
        strcpy(cstr, str.c_str());
        return cstr;
    }

    void Editor_delete(Editor *editor_ptr) {
        if (!editor_ptr)
            return;
        delete editor_ptr;
    }

    char *Editor_getArchiveUri(Editor *editor_ptr) {
        std::string str = editor_ptr->getArchiveUri();
        char *cstr = (char *) malloc((str.size() + 1) * sizeof(char *));
        strcpy(cstr, str.c_str());
        return cstr;
    }

    char *Editor_getLocalUri(Editor *editor_ptr) {
        std::string str = editor_ptr->getLocalUri();
        char *cstr = (char *) malloc((str.size() + 1) * sizeof(char *));
        strcpy(cstr, str.c_str());
        return cstr;
    }

    char *Editor_getModelUri(Editor *editor_ptr) {
        std::string str = editor_ptr->getModelUri();
        char *cstr = (char *) malloc((str.size() + 1) * sizeof(char *));
        strcpy(cstr, str.c_str());
        return cstr;
    }

    char *Editor_getRepositoryUri(Editor *editor_ptr) {
        std::string str = editor_ptr->getRepositoryUri();
        char *cstr = (char *) malloc((str.size() + 1) * sizeof(char *));
        strcpy(cstr, str.c_str());
        return cstr;
    }

    void Editor_addCreator(Editor *editor_ptr, const char* orcid_id) {
        editor_ptr->addCreator(orcid_id);
    }

    void Editor_addCurator(Editor *editor_ptr, const char* orcid_id) {
        editor_ptr->addCurator(std::move(orcid_id));
    }

    void Editor_addTaxon(Editor *editor_ptr, const char *taxon_id) {
        editor_ptr->addTaxon(taxon_id);
    }

    void Editor_addPubmed(Editor *editor_ptr, const char *pubmedid) {
        editor_ptr->addPubmed(pubmedid);
    }

    void Editor_addDescription(Editor *editor_ptr, const char *date) {
        editor_ptr->addDescription(date);
    }

    void Editor_addDateCreated(Editor *editor_ptr, const char *date) {
        editor_ptr->addDateCreated(date);
    }

    void Editor_addParentModel(Editor *editor_ptr, const char *biomod_id) {
        editor_ptr->addParentModel(biomod_id);
    }


/*********************************************************************
 * SingularAnnotation class methods
 */
    SingularAnnotation *SingularAnnotation_new(Editor *editor_ptr) {
        auto *singularAnnotation = new SingularAnnotation();
        singularAnnotation->setLocalUri(editor_ptr->getLocalUri());
        return singularAnnotation;
    }

    void SingularAnnotation_delete(SingularAnnotation *singularAnnotation) {
        if (singularAnnotation != nullptr) {
            singularAnnotation->freeStatement();
            delete singularAnnotation;
        }
    }

    void SingularAnnotation_freeAll(SingularAnnotation *singularAnnotation) {
        // note: we do not need a freeAll type function
        //  for singular annotation as it is a typedef Triple,
        //  which owns the nodes.

        if (!singularAnnotation)
            return;
        delete singularAnnotation;
    }

    void free_singular_annotation(SingularAnnotation *singularAnnotationPtr) {
        free(singularAnnotationPtr);
    }

    SingularAnnotation *
    SingularAnnotation_setAbout(SingularAnnotation *singular_annotation, const char *about) {
        singular_annotation->setAbout(about);
        return singular_annotation;
    };

    SingularAnnotation *SingularAnnotation_setPredicate(
            SingularAnnotation *singular_annotation, const char *namespace_, const char *term) {
        singular_annotation->setPredicate(namespace_, term);
        return singular_annotation;
    }

    SingularAnnotation *SingularAnnotation_setPredicateFromUri(
            SingularAnnotation *singular_annotation, const char *uri) {
        singular_annotation->setPredicate(uri);
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

    char *SingularAnnotation_getAbout(SingularAnnotation *singular_annotation) {
        std::string about = singular_annotation->getAbout();
        char *cstr = (char *) malloc((about.size() + 1) * sizeof(char));
        strcpy(cstr, about.c_str());
        return cstr;
    }

    char *SingularAnnotation_getPredicate(SingularAnnotation *singular_annotation) {
        std::string predicate_str = singular_annotation->getPredicateStr();
        char *cstr = (char *) malloc((predicate_str.size() + 1) * sizeof(char));
        strcpy(cstr, predicate_str.c_str());
        return cstr;
    }

    char *SingularAnnotation_getResource(SingularAnnotation *singular_annotation) {
        std::string resource = singular_annotation->getResourceStr();
        char *cstr = (char *) malloc((resource.size() + 1) * sizeof(char));
        strcpy(cstr, resource.c_str());
        return cstr;
    }

    char *SingularAnnotation_str(
            SingularAnnotation *singular_annotation,
            const char *format, const char *base_uri) {
        std::string str = singular_annotation->str(format, base_uri);
        char *cstr = (char *) malloc((str.size() + 1) * sizeof(char));
        strcpy(cstr, str.c_str());
        return cstr;
    }

/*********************************************************************
 * PhysicalEntity class methods
 */
    PhysicalEntity *PhysicalEntity_new(Editor *editor_ptr) {
        return new PhysicalEntity(editor_ptr->getModel(), editor_ptr->getModelUri(), editor_ptr->getLocalUri());
    }

    void PhysicalEntity_delete(PhysicalEntity *physical_entity_ptr) {
        if (physical_entity_ptr) {
//            physical_entity_ptr->free(); // free the containing node
            delete physical_entity_ptr;
        }
    }

    void PhysicalEntity_freeAll(PhysicalEntity *physical_entity_ptr) {
        physical_entity_ptr->free();
        delete physical_entity_ptr;
    }

    PhysicalEntity *PhysicalEntity_setPhysicalProperty(
            PhysicalEntity *physical_entity_ptr, const char *subject_metaid, const char *physical_property) {
        physical_entity_ptr->setPhysicalProperty(subject_metaid, physical_property);
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

    char *PhysicalEntity_getAbout(PhysicalEntity *physical_entity_ptr) {
        std::string about = physical_entity_ptr->getAbout();
        char *cstr = (char *) malloc((about.size() + 1) * sizeof(char));
        strcpy(cstr, about.c_str());
        return cstr;
    }

    char *PhysicalEntity_getIdentity(PhysicalEntity *physical_entity_ptr) {
        std::string identity = physical_entity_ptr->getIdentityResource().str();
        char *cstr = (char *) malloc((identity.size() + 1) * sizeof(char));
        strcpy(cstr, identity.c_str());
        return cstr;
    }

    int PhysicalEntity_getNumLocations(PhysicalEntity *physicalEntity) {
        return physicalEntity->getNumLocations();
    }

    char *PhysicalEntity_getLocation(PhysicalEntity *physical_entity_ptr, int index) {
        std::string location = physical_entity_ptr->getLocationResources()[index].str();
        char *cstr = (char *) malloc((location.size() + 1) * sizeof(char *));
        strcpy(cstr, location.c_str());
        return cstr;
    }

    char *PhysicalEntity_str(PhysicalEntity *physical_entity_ptr, const char *format, const char *base_uri) {
        Triples triples = physical_entity_ptr->toTriples();
        std::string str = triples.str(format, base_uri);
        triples.freeTriples();
        char *cstr = (char *) malloc((str.size() + 1) * sizeof(char));
        strcpy(cstr, str.c_str());
        return cstr;
    }


/*********************************************************************
 * PhysicalProcess class methods
 */
    PhysicalProcess *PhysicalProcess_new(Editor *editor_ptr) {
        return new PhysicalProcess(editor_ptr->getModel(), editor_ptr->getModelUri(), editor_ptr->getLocalUri());
    }

    void PhysicalProcess_delete(PhysicalProcess *physicalProcess) {
        delete physicalProcess;
    }

    void PhysicalProcess_freeAll(PhysicalProcess *physicalProcess) {
        physicalProcess->free();
        delete physicalProcess;
    }

    PhysicalProcess *
    PhysicalProcess_setPhysicalProperty(PhysicalProcess *physical_process, const char *subject_metaid,
                                        const char *physical_property) {
        physical_process->setPhysicalProperty(subject_metaid, physical_property);
        return physical_process;

    }

    PhysicalProcess *
    PhysicalProcess_addSource(PhysicalProcess *physical_process, double multiplier,
                              const char *physical_entity_reference) {
        physical_process->addSource(multiplier, physical_entity_reference);
        return physical_process;

    }

    PhysicalProcess *
    PhysicalProcess_addSink(PhysicalProcess *physical_process, double multiplier,
                            const char *physical_entity_reference) {
        physical_process->addSink(multiplier, physical_entity_reference);
        return physical_process;

    }

    PhysicalProcess *
    PhysicalProcess_addMediator(PhysicalProcess *physical_process,
                                const char *physical_entity_reference) {
        physical_process->addMediator(physical_entity_reference);
        return physical_process;

    }

    char *PhysicalProcess_str(PhysicalProcess *physical_process_ptr, const char *format, const char *base_uri) {
        Triples triples = physical_process_ptr->toTriples();
        std::string str = triples.str(format, base_uri);
        triples.freeTriples();
        char *cstr = (char *) malloc((str.size() + 1) * sizeof(char));
        strcpy(cstr, str.c_str());
        return cstr;
    }

    char *PhysicalProcess_getAbout(PhysicalProcess *physical_process_ptr) {
        const std::string &about = physical_process_ptr->getAbout();
        char *cstr = (char *) malloc((about.size() + 1) * sizeof(char));
        strcpy(cstr, about.c_str());
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


/*********************************************************************
 * PhysicalForce class methods
 */
    PhysicalForce *PhysicalForce_new(Editor *editor_ptr) {
        return new PhysicalForce(editor_ptr->getModel(), editor_ptr->getModelUri(), editor_ptr->getLocalUri());
    }

    void PhysicalForce_delete(PhysicalForce *physicalForce) {
        delete physicalForce;

    }

    void PhysicalForce_freeAll(PhysicalForce *physical_force_ptr) {
        physical_force_ptr->free();
        delete physical_force_ptr;
    }


    PhysicalForce *PhysicalForce_addSource(PhysicalForce *physical_force_ptr, double multiplier,
                                           const char *physical_entity_reference) {
        physical_force_ptr->addSource(multiplier, physical_entity_reference);
        return physical_force_ptr;

    }

    PhysicalForce *PhysicalForce_addSink(PhysicalForce *physical_force_ptr, double multiplier,
                                         const char *physical_entity_reference) {
        physical_force_ptr->addSink(multiplier, physical_entity_reference);
        return physical_force_ptr;
    }

    PhysicalForce *PhysicalForce_setPhysicalProperty(PhysicalForce *physical_force_ptr, const char *subject_metaid,
                                                     const char *physical_property) {
        physical_force_ptr->setPhysicalProperty(subject_metaid, physical_property);
        return physical_force_ptr;
    }

    int PhysicalForce_getNumSources(PhysicalForce *physicalForce) {
        return physicalForce->getNumSources();
    }

    int PhysicalForce_getNumSinks(PhysicalForce *physicalForce) {
        return physicalForce->getNumSinks();
    }

    char *PhysicalForce_str(PhysicalForce *physical_force_ptr, const char *format, const char *base_uri) {
        Triples triples = physical_force_ptr->toTriples();
        std::string str = triples.str(format, base_uri);
        triples.freeTriples();
        char *cstr = (char *) malloc((str.size() + 1) * sizeof(char));
        strcpy(cstr, str.c_str());
        return cstr;
    }


    char *PhysicalForce_getAbout(PhysicalForce *physical_force_ptr) {
        std::string about = physical_force_ptr->getAbout();
        char *cstr = (char *) malloc((about.size() + 1) * sizeof(char));
        strcpy(cstr, about.c_str());
        return cstr;
    }


/*********************************************************************
 * PersonalInformation class methods
 */
    PersonalInformation *PersonalInformation_new(Editor *editor_ptr) {
        return new PersonalInformation(editor_ptr->getModel(), editor_ptr->getModelUri(), editor_ptr->getLocalUri());
    }

    void PersonalInformation_delete(PersonalInformation* information) {
        delete information;
    }

    char *PersonalInformation_getLocalUri(PersonalInformation *information) {
        const std::string& about = information->getLocalUri();
        char *cstr = (char *) malloc((about.size() + 1) * sizeof(char));
        strcpy(cstr, about.c_str());
        return cstr;
    }

    void PersonalInformation_setLocalUri(PersonalInformation *information, const char *localUri) {
        information->setLocalUri(localUri);
    }

    PersonalInformation *PersonalInformation_addCreator(PersonalInformation *information, const char *value) {
        information->addCreator(value);
        return information;
    }

    PersonalInformation *PersonalInformation_addName(PersonalInformation *information, const char *value) {
        information->addName(value);
        return information;
    }

    PersonalInformation *PersonalInformation_addMbox(PersonalInformation *information, const char *value) {
        information->addMbox(value);
        return information;
    }

    PersonalInformation *PersonalInformation_addAccountName(PersonalInformation *information, const char *value) {
        information->addAccountName(value);
        return information;
    }

    PersonalInformation *
    PersonalInformation_addAccountServiceHomepage(PersonalInformation *information, const char *value) {
        information->addAccountServiceHomepage(value);
        return information;
    }

    PersonalInformation *
    PersonalInformation_addFoafBlank(PersonalInformation *information, const char *predicate, const char *blank_value) {
        information->addFoafBlank(predicate, blank_value);
        return information;
    }

    PersonalInformation *
    PersonalInformation_addFoafUri(PersonalInformation *information, const char *predicate, const char *uri_value) {
        information->addFoafUri(predicate, uri_value);
        return information;
    }

    PersonalInformation *
    PersonalInformation_addFoafLiteral(PersonalInformation *information, const char *predicate,
                                       const char *literal_value) {
        information->addFoafLiteral(predicate, literal_value);
        return information;
    }

    PersonalInformation *
    PersonalInformation_addFoaf(PersonalInformation *information, const char *predicate, const LibrdfNode &value_node) {
        information->addFoaf(predicate, value_node);
        return information;
    }

    char *PersonalInformation_getMetaid(PersonalInformation *information) {
        std::string about = information->getMetaid();
        char *cstr = (char *) malloc((about.size() + 1) * sizeof(char));
        strcpy(cstr, about.c_str());
        return cstr;
    }

    void PersonalInformation_setMetaid(PersonalInformation *information, const char *metaid) {
        information->setMetaid(metaid);
    }

    char *PersonalInformation_getModelUri(PersonalInformation *information) {
        std::string about = information->getModelUri();
        char *cstr = (char *) malloc((about.size() + 1) * sizeof(char));
        strcpy(cstr, about.c_str());
        return cstr;
    }

    void PersonalInformation_setModelUri(PersonalInformation *information, const char *modelUri) {
        information->setModelUri(modelUri);
    }


}




























