//
// Created by Ciaran on 5/8/2020.
//

#include "omexmeta/OmexMetaCApi.h"

#include <utility>


namespace omexmeta {

    std::string LAST_ERROR = "No errors";

    void setLastError(const char *err) {
        LAST_ERROR = err;
    }

    char *getLastError() {
        char *cstr = (char *) malloc((LAST_ERROR.size() + 1) * sizeof(char *));
        strcpy(cstr, LAST_ERROR.c_str());
        return cstr;
    }

    void clearLastError(const std::string &err) {
        LAST_ERROR = "";
    }

    int free_c_char_star(char *c) {
        try {
            if (c != nullptr)
                free(c);
            return 0;
        } catch (std::exception &error) {
            setLastError(error.what());
            return -1;
        }
    }

    /**
     * @brief when a function fails and it returns char*, do not return nullptr
     * as it will crash python. Instead copy the error string into dynamic memory
     * and return that.
     * @details the caller is responsible for freeing the memory associated with the
     * returned string.
     */
    char *funcThatReturnsCharStarFailed(const char *errorMsg) {
        setLastError(errorMsg);
        char *cstr = (char *) malloc((strlen(errorMsg) + 1) * sizeof(char *));
        strcpy(cstr, errorMsg);
        return cstr;
    }

    /*************************************************************
     *  RDF methods
     */

    int *functionThatReturnsNullptr(){
        return nullptr;
    };


    RDF *RDF_new(const char *storage_type, const char *storage_name,
                 const char *storage_options, const char *model_options) {
        try {
            RDF *rdf_ptr = new RDF(storage_type, storage_name, storage_options, model_options);
            return rdf_ptr;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    void RDF_delete(RDF *rdf_ptr) {
        delete rdf_ptr;
    }

    RDF *RDF_fromString(const char *str, const char *format, const char *storage_type,
                        const char *storage_name,
                        const char *storage_options, const char *model_options) {
        try {
            RDF *rdf = RDF_new();
            rdf->addFromString(str, format);
            return rdf;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    int RDF_addFromString(RDF *rdf_ptr, const char *str, const char *format) {
        try {
            rdf_ptr->addFromString(str, format);
            return 0;
        } catch (std::exception &error) {
            setLastError(error.what());
            return -1;
        }
    }

    RDF *RDF_fromUri(const char *uri_string, const char *format, const char *storage_type, const char *storage_name,
                     const char *storage_options, const char *model_options) {
        try {
            RDF *rdf = RDF_new();
            rdf->addFromUri(uri_string, format);
            return rdf;
        } catch (std::exception &error) {
            setLastError(error.what());
            RDF *rdf = RDF_new();
            return rdf;
        }
    }

    int RDF_addFromUri(RDF *rdf_ptr, const char *uri_string, const char *format) {
        try {
            rdf_ptr->addFromUri(uri_string, format);
            return 0;
        } catch (std::exception &error) {
            setLastError(error.what());
            return -1;
        }
    }

    RDF *RDF_fromFile(const char *filename, const char *format, const char *storage_type, const char *storage_name,
                      const char *storage_options, const char *model_options) {
        try {
            RDF *rdf = RDF_new();
            rdf->addFromFile(filename, format);
            return rdf;
        } catch (std::exception &error) {
            setLastError(error.what());
            RDF *rdf = RDF_new();
            return rdf;
        }
    }

    int RDF_addFromFile(RDF *rdf_ptr, const char *uri_string, const char *format) {
        try {
            rdf_ptr->addFromFile(uri_string, format);
            return 0;
        } catch (std::exception &error) {
            setLastError(error.what());
            return -1;
        }
    }

    char *RDF_toString(RDF *rdf_ptr, const char *format) {
        // do not return a temporary object:
        try {
            std::string s = rdf_ptr->toString(format);
            char *cstr = (char *) malloc((s.size() + 1) * sizeof(char *));
            strcpy(cstr, s.c_str());
            return cstr;
        } catch (std::exception &error) {
            return funcThatReturnsCharStarFailed(error.what());
        }
    }

    int RDF_toFile(RDF *rdf_ptr, const char *format, const char *filename) {
        try {
            rdf_ptr->toFile(filename, format);
            return 0;
        } catch (std::exception &error) {
            setLastError(error.what());
            return -1;
        }
    }

    char *RDF_queryResultsAsString(RDF *rdf_ptr, const char *query_str, const char *results_format) {
        try {
            std::string results = rdf_ptr->queryResultsAsString(query_str, results_format);
            char *s = (char *) malloc((results.size() + 1) * sizeof(char *));
            strcpy(s, results.c_str());
            return s;
        } catch (std::exception &error) {
            return funcThatReturnsCharStarFailed(error.what());
        }
    }

    /**
     * @brief run a sparql query on rdf_ptr. Return the results as a ResultsMap*.
     * @details Caller is responsible for freeing memory associated with returned map ptr
     */
    ResultsMap *RDF_queryResultsAsMap(RDF *rdf_ptr, const char *query_str) {
        try {
            ResultsMap resultsMap = rdf_ptr->queryResultsAsMap(query_str);
            auto *rOut = new ResultsMap{};
            rOut->insert(resultsMap.begin(), resultsMap.end());
            return rOut;
        } catch (std::exception &error) {
            setLastError(error.what());
            ResultsMap* r = new ResultsMap{};
            return r;
        }
    }

    /**
     * @brief RDF_queryResultsAsMap allocates a ResultsMap to the heap.
     * This method deletes that memory
     */
    void deleteResultsMap(ResultsMap *map) {
        delete map;
    }

    int RDF_size(RDF *rdf_ptr) {
        try {
            return rdf_ptr->size();
        } catch (std::exception &error) {
            setLastError(error.what());
            return -1;
        }
    }

    int RDF_setRepositoryUri(RDF *rdf_ptr, const char *repository_uri) {
        try {
            rdf_ptr->setRepositoryUri(repository_uri);
            return 0;
        } catch (std::exception &error) {
            setLastError(error.what());
            return -1;
        }
    }

    int RDF_setArchiveUri(RDF *rdf_ptr, const char *archive_uri) {
        try {
            rdf_ptr->setArchiveUri(archive_uri);
            return 0;
        } catch (std::exception &error) {
            setLastError(error.what());
            return -1;
        }
    }

    int RDF_setModelUri(RDF *rdf_ptr, const char *model_uri) {
        try {
            rdf_ptr->setModelUri(model_uri);
            return 0;
        } catch (std::exception &error) {
            setLastError(error.what());
            return -1;
        }
    }

    int RDF_setModelMetaid(RDF *rdf_ptr, const char *model_metaid) {
        try {
            rdf_ptr->setModelMetaid(model_metaid);
            return 0;
        } catch (std::exception &error) {
            setLastError(error.what());
            return -1;
        }
    }

    char *RDF_getModelMetaid(RDF *rdf_ptr) {
        try {
            const std::string &str = rdf_ptr->getModelMetaid();
            char *cstr = (char *) malloc((str.size() + 1) * sizeof(char *));
            strcpy(cstr, str.c_str());
            return cstr;
        } catch (std::exception &error) {
            return funcThatReturnsCharStarFailed(error.what());
        }
    }

    char *RDF_getRepositoryUri(RDF *rdf_ptr) {
        try {
            const std::string &str = rdf_ptr->getRepositoryUri();
            char *cstr = (char *) malloc((str.size() + 1) * sizeof(char *));
            strcpy(cstr, str.c_str());
            return cstr;
        } catch (std::exception &error) {
            return funcThatReturnsCharStarFailed(error.what());
        }
    }

    char *RDF_getModelLevelAnnotationUri(RDF *rdf_ptr) {
        try {
            const std::string &str = rdf_ptr->getModelLevelAnnotationUri();
            char *cstr = (char *) malloc((str.size() + 1) * sizeof(char *));
            strcpy(cstr, str.c_str());
            return cstr;
        } catch (std::exception &error) {
            return funcThatReturnsCharStarFailed(error.what());
        }
    }

    char *RDF_getArchiveUri(RDF *rdf_ptr) {
        try {
            const std::string &str = rdf_ptr->getArchiveUri();
            char *cstr = (char *) malloc((str.size() + 1) * sizeof(char *));
            strcpy(cstr, str.c_str());
            return cstr;
        } catch (std::exception &error) {
            return funcThatReturnsCharStarFailed(error.what());
        }
    }

    char *RDF_getModelUri(RDF *rdf_ptr) {
        try {
            const std::string &str = rdf_ptr->getModelUri();
            char *cstr = (char *) malloc((str.size() + 1) * sizeof(char *));
            strcpy(cstr, str.c_str());
            return cstr;
        } catch (std::exception &error) {
            return funcThatReturnsCharStarFailed(error.what());
        }
    }

    char *RDF_getLocalUri(RDF *rdf_ptr) {
        try {
            const std::string &str = rdf_ptr->getLocalUri();
            char *cstr = (char *) malloc((str.size() + 1) * sizeof(char *));
            strcpy(cstr, str.c_str());
            return cstr;
        } catch (std::exception &error) {
            return funcThatReturnsCharStarFailed(error.what());
        }
    }


    bool RDF_equals_rdf_vs_string(RDF *rdf_ptr, const char *serialized_rdf, const char *format, bool verbose) {
        try {
            return RDF::equals(rdf_ptr, serialized_rdf, format, verbose);
        } catch (std::exception &error) {
            setLastError(error.what());
            return false;
        }
    }

    bool RDF_equals_rdf_vs_rdf(RDF *rdf_ptr1, RDF *rdf_ptr2, const char *format, bool verbose) {
        try {
            return RDF::equals(rdf_ptr1, rdf_ptr2, format, verbose);
        } catch (std::exception &error) {
            setLastError(error.what());
            return false;
        }
    }

    bool RDF_equals_string_vs_string(const char *first_rdf_graph, const char *second_rdf_graph, const char *format, bool verbose) {
        try {
            return RDF::equals(first_rdf_graph, second_rdf_graph, format, format, verbose);
        } catch (std::exception &error) {
            setLastError(error.what());
            return false;
        }
    }

    Editor *RDF_toEditor(RDF *rdf_ptr, const char *xml, bool generate_new_metaids, bool sbml_semantic_extraction) {
        try {
            return rdf_ptr->toEditorPtr(xml, generate_new_metaids, sbml_semantic_extraction);
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    /*********************************************************************
     * Editor class methods
     */

    SingularAnnotation *Editor_newSingularAnnotation(Editor *editor_ptr) {
        try {
            auto *singularAnnotation = new SingularAnnotation(editor_ptr->getUriHandler());
            return singularAnnotation;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    PersonalInformation *Editor_newPersonalInformation(Editor *editor_ptr) {
        try {
            return new PersonalInformation(editor_ptr->getModel(), editor_ptr->getUriHandler());
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    PhysicalEntity *Editor_newPhysicalEntity(Editor *editor_ptr) {
        try {
            return new PhysicalEntity(editor_ptr->getModel(), editor_ptr->getUriHandler());
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    EnergyDiff *Editor_newEnergyDiff(Editor *editor_ptr) {
        try {
            return new EnergyDiff(editor_ptr->getModel(), editor_ptr->getUriHandler());
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }
    PhysicalProcess *Editor_newPhysicalProcess(Editor *editor_ptr) {
        try {
            return new PhysicalProcess(editor_ptr->getModel(), editor_ptr->getUriHandler());
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    PhysicalProperty *Editor_newPhysicalProperty(Editor *editor_ptr) {
        try {
            auto *property = new PhysicalProperty(editor_ptr->getModel(), editor_ptr->getUriHandler());
            return property;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }


    int Editor_addNamespace(Editor *editor_ptr, const char *namespace_, const char *prefix) {
        try {
            editor_ptr->addNamespace(namespace_, prefix);
            return 0;
        } catch (std::exception &error) {
            setLastError(error.what());
            return -1;
        }
    }

    int Editor_addSingleAnnotation(Editor *editor_ptr, SingularAnnotation *singularAnnotation) {
        try {
            editor_ptr->addSingleAnnotation(*singularAnnotation);
            return 0;
        } catch (std::exception &error) {
            setLastError(error.what());
            return -1;
        }
    }

    int Editor_addPhysicalEntity(Editor *editor_ptr, PhysicalEntity *physicalEntity) {
        try {
            editor_ptr->addPhysicalEntity(*physicalEntity);
            return 0;
        } catch (std::exception &error) {
            setLastError(error.what());
            return -1;
        }
    }

    int Editor_addPhysicalProcess(Editor *editor_ptr, PhysicalProcess *physicalProcess) {
        try {
            editor_ptr->addPhysicalProcess(*physicalProcess);
            return 0;
        } catch (std::exception &error) {
            setLastError(error.what());
            return -1;
        }
    }

    int Editor_addPhysicalProperty(Editor *editor_ptr, PhysicalProperty *physicalProperty) {
        try {
            editor_ptr->addPhysicalProperty(*physicalProperty);
            return 0;
        } catch (std::exception &error) {
            setLastError(error.what());
            return -1;
        }
    }

    int Editor_addEnergyDiff(Editor *editor_ptr, EnergyDiff *physicalForce) {
        try {
            editor_ptr->addEnergyDiff(*physicalForce);
            return 0;

        } catch (std::exception &error) {
            setLastError(error.what());
            return -1;
        }
    }

    int Editor_addPersonalInformation(Editor *editor_ptr, PersonalInformation *personalInformation) {
        try {
            editor_ptr->addPersonalInformation(personalInformation);
            return 0;
        } catch (std::exception &error) {
            setLastError(error.what());
            return -1;
        }
    }

    int Editor_removeSingleAnnotation(Editor *editor_ptr, SingularAnnotation *singularAnnotation) {
        try {
            editor_ptr->removeSingleAnnotation(*singularAnnotation);
            return 0;
        } catch (std::exception &error) {
            setLastError(error.what());
            return -1;
        }
    }

    int Editor_removePhysicalEntity(Editor *editor_ptr, PhysicalEntity *physicalEntity) {
        try {
            editor_ptr->removePhysicalEntity(*physicalEntity);
            return 0;
        } catch (std::exception &error) {
            setLastError(error.what());
            return -1;
        }
    }

    int Editor_removePhysicalProcess(Editor *editor_ptr, PhysicalProcess *physicalProcess) {
        try {
            editor_ptr->removePhysicalProcess(*physicalProcess);
            return 0;
        } catch (std::exception &error) {
            setLastError(error.what());
            return -1;
        }
    }

    int Editor_removeEnergyDiff(Editor *editor_ptr, EnergyDiff *physicalForce) {
        try {
            editor_ptr->removeEnergyDiff(*physicalForce);
            return 0;
        } catch (std::exception &error) {
            setLastError(error.what());
            return -1;
        }
    }

    int Editor_removePersonalInformation(Editor *editor_ptr, PersonalInformation *information) {
        try {
            editor_ptr->removePersonalInformation(information);
            return 0;
        } catch (std::exception &error) {
            setLastError(error.what());
            return -1;
        }
    }

    int Editor_checkValidMetaid(Editor *editor_ptr, const char *id) {
        try {
            editor_ptr->checkValidMetaid(id);
            return 0;
        } catch (std::exception &error) {
            setLastError(error.what());
            return -1;
        }
    }

    char *Editor_getMetaId(Editor *editor_ptr, int index) {
        try {
            std::string str = editor_ptr->getMetaids()[index];
            auto cstr = (char *) malloc((str.size() + 1) * sizeof(char *));
            strcpy(cstr, str.c_str());
            return cstr;
        } catch (std::exception &error) {
            return funcThatReturnsCharStarFailed(error.what());
        }
    }

    int Editor_getNumMetaIds(Editor *editor_ptr) {
        try {
            return editor_ptr->getMetaids().size();
        } catch (std::exception &error) {
            setLastError(error.what());
            return -1;
        }
    }

    /**
         * @brief get the xml from the editor
     *
     * The returned string is owned by the caller.
     */
    char *Editor_getXml(Editor *editor_ptr) {
        try {
            const std::string &str = editor_ptr->getXml();
            char *cstr = (char *) malloc((str.size() + 1) * sizeof(char *));
            strcpy(cstr, str.c_str());
            return cstr;
        } catch (std::exception &error) {
            return funcThatReturnsCharStarFailed(error.what());
        }
    }

    int Editor_delete(Editor *editor_ptr) {
        try {
            if (!editor_ptr)
                exit(1);
            delete editor_ptr;
            return 0;
        } catch (std::exception &error) {
            setLastError(error.what());
            return -1;
        }
    }

    char *Editor_getArchiveUri(Editor *editor_ptr) {
        try {
            std::string str = editor_ptr->getArchiveUri();
            char *cstr = (char *) malloc((str.size() + 1) * sizeof(char *));
            strcpy(cstr, str.c_str());
            return cstr;
        } catch (std::exception &error) {
            return funcThatReturnsCharStarFailed(error.what());
        }
    }

    char *Editor_getLocalUri(Editor *editor_ptr) {
        try {
            std::string str = editor_ptr->getLocalUri();
            char *cstr = (char *) malloc((str.size() + 1) * sizeof(char *));
            strcpy(cstr, str.c_str());
            return cstr;
        } catch (std::exception &error) {
            return funcThatReturnsCharStarFailed(error.what());
        }
    }

    char *Editor_getModelUri(Editor *editor_ptr) {
        try {
            std::string str = editor_ptr->getModelUri();
            char *cstr = (char *) malloc((str.size() + 1) * sizeof(char *));
            strcpy(cstr, str.c_str());
            return cstr;
        } catch (std::exception &error) {
            return funcThatReturnsCharStarFailed(error.what());
        }
    }

    char *Editor_getRepositoryUri(Editor *editor_ptr) {
        try {
            std::string str = editor_ptr->getRepositoryUri();
            char *cstr = (char *) malloc((str.size() + 1) * sizeof(char *));
            strcpy(cstr, str.c_str());
            return cstr;
        } catch (std::exception &error) {
            return funcThatReturnsCharStarFailed(error.what());
        }
    }

    char *Editor_stripAnnotations(Editor *editor_ptr, const char *annotationElementName) {
        try {
            std::string str = editor_ptr->stripAnnotations(annotationElementName);
            char *cstr = (char *) malloc((str.size() + 1) * sizeof(char *));
            strcpy(cstr, str.c_str());
            return cstr;
        } catch (std::exception &error) {
            return funcThatReturnsCharStarFailed(error.what());
        }
    }

    Editor *Editor_addCreator(Editor *editor_ptr, const char *orcid_id) {
        try {
            editor_ptr->addCreator(orcid_id);
            return editor_ptr;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    Editor *Editor_addContributor(Editor *editor_ptr, const char *orcid_id) {
        try {
            editor_ptr->addContributor(orcid_id);
            return editor_ptr;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    Editor *Editor_addTaxon(Editor *editor_ptr, const char *taxon_id) {
        try {
            editor_ptr->addTaxon(taxon_id);
            return editor_ptr;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    Editor *Editor_addPubmed(Editor *editor_ptr, const char *pubmedid) {
        try {
            editor_ptr->addPubmed(pubmedid);
            return editor_ptr;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    Editor *Editor_addDescription(Editor *editor_ptr, const char *date) {
        try {
            editor_ptr->addDescription(date);
            return editor_ptr;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    Editor *Editor_addDateCreated(Editor *editor_ptr, const char *date) {
        try {
            editor_ptr->addDateCreated(date);
            return editor_ptr;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    Editor *Editor_addParentModel(Editor *editor_ptr, const char *biomod_id) {
        try {
            editor_ptr->addParentModel(biomod_id);
            return editor_ptr;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    int SingularAnnotation_delete(SingularAnnotation *singularAnnotation) {
        try {
            delete singularAnnotation;
            return 0;
        } catch (std::exception &error) {
            setLastError(error.what());
            return -1;
        }
    }

    SingularAnnotation *
    SingularAnnotation_about(SingularAnnotation *singular_annotation, const char *about) {
        try {
            singular_annotation->about(about);
            return singular_annotation;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    };

    SingularAnnotation *SingularAnnotation_setPredicate(
            SingularAnnotation *singular_annotation, const char *namespace_, const char *term) {
        try {
            singular_annotation->setPredicate(namespace_, term);
            return singular_annotation;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    SingularAnnotation *SingularAnnotation_predicate(
            SingularAnnotation *singular_annotation, const char *namespace_, const char *term) {
        return SingularAnnotation_setPredicate(singular_annotation, namespace_, term);
    }

    SingularAnnotation *SingularAnnotation_setPredicateFromUri(
            SingularAnnotation *singular_annotation, const char *uri) {
        try {
            singular_annotation->predicate(uri);
            return singular_annotation;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    SingularAnnotation *SingularAnnotation_predicateFromUri(
            SingularAnnotation *singular_annotation, const char *uri) {
        return SingularAnnotation_setPredicateFromUri(singular_annotation, uri);
    }

    SingularAnnotation *
    SingularAnnotation_setResourceLiteral(SingularAnnotation *singular_annotation, const char *literal) {
        try {
            singular_annotation->setResourceLiteral(literal);
            return singular_annotation;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    SingularAnnotation *
    SingularAnnotation_resourceLiteral(SingularAnnotation *singular_annotation, const char *literal) {
        return SingularAnnotation_setResourceLiteral(singular_annotation, literal);
    }

    SingularAnnotation *
    SingularAnnotation_setResourceUri(SingularAnnotation *singular_annotation, const char *identifiers_uri) {
        try {
            singular_annotation->setResourceUri(identifiers_uri);
            return singular_annotation;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    SingularAnnotation *
    SingularAnnotation_resourceUri(SingularAnnotation *singular_annotation, const char *identifiers_uri) {
        return SingularAnnotation_setResourceUri(singular_annotation, identifiers_uri);
    }

    SingularAnnotation *
    SingularAnnotation_setResourceBlank(SingularAnnotation *singular_annotation, const char *blank_id) {
        try {
            singular_annotation->setResourceBlank(blank_id);
            return singular_annotation;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }
    SingularAnnotation *
    SingularAnnotation_resourceBlank(SingularAnnotation *singular_annotation, const char *blank_id) {
        return SingularAnnotation_setResourceBlank(singular_annotation, blank_id);
    }

    char *SingularAnnotation_getAbout(SingularAnnotation *singular_annotation) {
        try {
            std::string about = singular_annotation->getAbout();
            char *cstr = (char *) malloc((about.size() + 1) * sizeof(char));
            strcpy(cstr, about.c_str());
            return cstr;
        } catch (std::exception &error) {
            return funcThatReturnsCharStarFailed(error.what());
        }
    }

    char *SingularAnnotation_getPredicate(SingularAnnotation *singular_annotation) {
        try {
            LibrdfNode predicateNode = singular_annotation->getPredicateNode();
            std::string predicate_str = predicateNode.str();
            char *cstr = (char *) malloc((predicate_str.size() + 1) * sizeof(char));
            strcpy(cstr, predicate_str.c_str());
            return cstr;
        } catch (std::exception &error) {
            return funcThatReturnsCharStarFailed(error.what());
        }
    }

    char *SingularAnnotation_getResource(SingularAnnotation *singular_annotation) {
        try {
            std::string resource = singular_annotation->getResourceNode().str();
            char *cstr = (char *) malloc((resource.size() + 1) * sizeof(char));
            strcpy(cstr, resource.c_str());
            return cstr;
        } catch (std::exception &error) {
            return funcThatReturnsCharStarFailed(error.what());
        }
    }

    //    char *SingularAnnotation_str(SingularAnnotation *singular_annotation, const char *format) {
    //        try {
    //            std::string str = singular_annotation->str(format);
    //            char *cstr = (char *) malloc((str.size() + 1) * sizeof(char));
    //            strcpy(cstr, str.c_str());
    //            return cstr;
    //        } catch (std::exception &error) {
    //            setLastError(error.what());
    //            return nullptr;
    //        }
    //    }

    /*********************************************************************
 * PhysicalProperty class methods
 */
    char *PhysicalProperty_getAbout(PhysicalProperty *property) {
        try {
            const std::string &str = property->getAbout();
            char *cstr = (char *) malloc((str.size() + 1) * sizeof(char));
            strcpy(cstr, str.c_str());
            return cstr;
        } catch (std::exception &error) {
            return funcThatReturnsCharStarFailed(error.what());
        }
    }

    PhysicalProperty *PhysicalProperty_about(PhysicalProperty *property, const char *about, eUriType type) {
        try {
            property->about(about, type);
            return property;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    char *PhysicalProperty_getIsVersionOfValue(PhysicalProperty *property) {
        try {
            const std::string &str = property->getIsVersionOfValue();
            char *cstr = (char *) malloc((str.size() + 1) * sizeof(char));
            strcpy(cstr, str.c_str());
            return cstr;
        } catch (std::exception &error) {
            return funcThatReturnsCharStarFailed(error.what());
        }
    }

    PhysicalProperty *PhysicalProperty_isPropertyOf(PhysicalProperty *property, const char *is_property_of, eUriType type) {
        try {
            property->isPropertyOf(is_property_of, type);
            return property;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    PhysicalProperty *PhysicalProperty_isVersionOf(PhysicalProperty *property, const char *is_version_of) {
        try {
            property->isVersionOf(is_version_of);
            return property;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }


    char *PhysicalProperty_getIsPropertyOfValue(PhysicalProperty *property) {
        try {
            const std::string &str = property->getIsPropertyOfValue();
            char *cstr = (char *) malloc((str.size() + 1) * sizeof(char));
            strcpy(cstr, str.c_str());
            return cstr;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    int PhysicalProperty_delete(PhysicalProperty *property) {
        try {
            delete property;
            return 0;
        } catch (std::exception &error) {
            setLastError(error.what());
            return -1;
        }
    }


    /*********************************************************************
 * PhysicalEntity class methods
 */


    int PhysicalEntity_delete(PhysicalEntity *physical_entity_ptr) {
        try {
            delete physical_entity_ptr;
            return 0;
        } catch (std::exception &error) {
            setLastError(error.what());
            return -1;
        }
    }

    PhysicalEntity *PhysicalEntity_setPhysicalProperty(
            PhysicalEntity *physical_entity_ptr, const char *subject_metaid, const char *physical_property) {
        try {
            physical_entity_ptr->setPhysicalProperty(subject_metaid, physical_property);
            return physical_entity_ptr;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    PhysicalEntity *PhysicalEntity_identity(PhysicalEntity *physical_entity_ptr, const char *identity_resource) {
        try {
            physical_entity_ptr->identity(identity_resource);
            return physical_entity_ptr;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }


    char *PhysicalEntity_getAbout(PhysicalEntity *physical_entity_ptr) {
        try {
            const std::string &about = physical_entity_ptr->getAbout();
            char *cstr = (char *) malloc((about.size() + 1) * sizeof(char));
            strcpy(cstr, about.c_str());
            return cstr;
        } catch (std::exception &error) {
            return funcThatReturnsCharStarFailed(error.what());
        }
    }

    char *PhysicalEntity_getIdentity(PhysicalEntity *physical_entity_ptr) {
        try {
            std::string identity = physical_entity_ptr->getIdentityResource();
            char *cstr = (char *) malloc((identity.size() + 1) * sizeof(char));
            strcpy(cstr, identity.c_str());
            return cstr;
        } catch (std::exception &error) {
            return funcThatReturnsCharStarFailed(error.what());
        }
    }

    int PhysicalEntity_getNumLocations(PhysicalEntity *physicalEntity) {
        try {
            return physicalEntity->getNumLocations();
        } catch (std::exception &error) {
            setLastError(error.what());
            return -1;
        }
    }

    char *PhysicalEntity_getLocation(PhysicalEntity *physical_entity_ptr, int index) {
        try {
            std::string location = physical_entity_ptr->getLocationResources()[index];
            char *cstr = (char *) malloc((location.size() + 1) * sizeof(char *));
            strcpy(cstr, location.c_str());
            return cstr;
        } catch (std::exception &error) {
            return funcThatReturnsCharStarFailed(error.what());
        }
    }

    PhysicalEntity *PhysicalEntity_hasProperty(PhysicalEntity *physical_entity_ptr, PhysicalProperty *property) {
        try {

            physical_entity_ptr->hasProperty(*property);
            return physical_entity_ptr;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    PhysicalEntity *PhysicalEntity_hasPropertyisVersionOf(PhysicalEntity *physical_entity_ptr, const char *isVersionOf) {
        try {

            physical_entity_ptr->hasProperty(isVersionOf);
            return physical_entity_ptr;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    PhysicalEntity *PhysicalEntity_hasPropertyFull(PhysicalEntity *physical_entity_ptr, const char *property_about, eUriType about_uri_type, const char *is_version_of) {
        try {

            physical_entity_ptr->hasProperty(property_about, about_uri_type, is_version_of);
            return physical_entity_ptr;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    PhysicalEntity *PhysicalEntity_isPartOf(PhysicalEntity *physical_entity_ptr, const char *is_part_of, eUriType type) {
        try {
            physical_entity_ptr->isPartOf(is_part_of, type);
            return physical_entity_ptr;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    PhysicalEntity *PhysicalEntity_hasPart(PhysicalEntity *physical_entity_ptr, const char *part) {
        try {
            physical_entity_ptr->hasPart(part);
            return physical_entity_ptr;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    PhysicalEntity *PhysicalEntity_about(PhysicalEntity *physical_entity_ptr, const char *about, eUriType type) {
        try {
            physical_entity_ptr->about(about, type);
            return physical_entity_ptr;
            return physical_entity_ptr;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }


    int PhysicalProcess_delete(PhysicalProcess *physicalProcess) {
        try {
            delete physicalProcess;
            return 0;
        } catch (std::exception &error) {
            setLastError(error.what());
            return -1;
        }
    }

    PhysicalProcess *
    PhysicalProcess_addSource(PhysicalProcess *physical_process,
                              const char *physical_entity_reference, eUriType type, double multiplier) {
        try {
            physical_process->addSource(physical_entity_reference, type, multiplier);
            return physical_process;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    PhysicalProcess *
    PhysicalProcess_addSink(PhysicalProcess *physical_process,
                            const char *physical_entity_reference, eUriType type, double multiplier) {
        try {
            physical_process->addSink(physical_entity_reference, type, multiplier);
            return physical_process;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    PhysicalProcess *
    PhysicalProcess_addMediator(PhysicalProcess *physical_process,
                                const char *physical_entity_reference, eUriType type) {
        try {
            physical_process->addMediator(physical_entity_reference, type);
            return physical_process;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    PhysicalProcess *PhysicalProcess_hasProperty(PhysicalProcess *physical_process_ptr, PhysicalProperty *property) {
        try {

            physical_process_ptr->hasProperty(*property);
            return physical_process_ptr;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    PhysicalProcess *PhysicalProcess_hasPropertyisVersionOf(PhysicalProcess *physical_process_ptr, const char *isVersionOf) {
        try {

            physical_process_ptr->hasProperty(isVersionOf);
            return physical_process_ptr;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    PhysicalProcess *PhysicalProcess_hasPropertyFull(PhysicalProcess *physical_process_ptr, const char *property_about, eUriType about_uri_type, const char *is_version_of) {
        try {

            physical_process_ptr->hasProperty(property_about, about_uri_type, is_version_of);
            return physical_process_ptr;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    char *PhysicalProcess_getAbout(PhysicalProcess *physical_process_ptr) {
        try {
            const std::string &about = physical_process_ptr->getAbout();
            char *cstr = (char *) malloc((about.size() + 1) * sizeof(char));
            strcpy(cstr, about.c_str());
            return cstr;
        } catch (std::exception &error) {
            return funcThatReturnsCharStarFailed(error.what());
        }
    }

    int PhysicalProcess_getNumSources(PhysicalProcess *physicalProcess) {
        try {
            return physicalProcess->getNumSources();
        } catch (std::exception &error) {
            setLastError(error.what());
            return -1;
        }
    }

    int PhysicalProcess_getNumSinks(PhysicalProcess *physicalProcess) {
        try {
            return physicalProcess->getNumSinks();
        } catch (std::exception &error) {
            setLastError(error.what());
            return -1;
        }
    }

    int PhysicalProcess_getNumMediators(PhysicalProcess *physicalProcess) {
        try {
            return physicalProcess->getNumMediators();
        } catch (std::exception &error) {
            setLastError(error.what());
            return -1;
        }
    }

    PhysicalProcess *PhysicalProcess_about(PhysicalProcess *physical_process_ptr, const char *about, eUriType type) {
        try {
            physical_process_ptr->about(about, type);
            return physical_process_ptr;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    PhysicalProcess *PhysicalProcess_isVersionOf(PhysicalProcess *physical_process_ptr, const char *version, eUriType type) {
        try {
            physical_process_ptr->isVersionOf(version, type);
            return physical_process_ptr;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    int EnergyDiff_delete(EnergyDiff *physicalForce) {
        try {
            delete physicalForce;
            return 0;
        } catch (std::exception &error) {
            setLastError(error.what());
            return -1;
        }
    }

    EnergyDiff *EnergyDiff_addSource(EnergyDiff *energy_diff_ptr,
                                     const char *physical_entity_reference, eUriType type) {
        try {
            energy_diff_ptr->addSource(physical_entity_reference, type);
            return energy_diff_ptr;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    EnergyDiff *EnergyDiff_addSink(EnergyDiff *energy_diff_ptr,
                                   const char *physical_entity_reference, eUriType type) {
        try {
            energy_diff_ptr->addSink(physical_entity_reference, type);
            return energy_diff_ptr;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    EnergyDiff *EnergyDiff_setPhysicalProperty(EnergyDiff *energy_diff_ptr, const char *subject_metaid,
                                               const char *physical_property) {
        try {
            energy_diff_ptr->setPhysicalProperty(subject_metaid, physical_property);
            return energy_diff_ptr;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    int EnergyDiff_getNumSources(EnergyDiff *physicalForce) {
        try {
            return physicalForce->getNumSources();
        } catch (std::exception &error) {
            setLastError(error.what());
            return -1;
        }
    }

    int EnergyDiff_getNumSinks(EnergyDiff *physicalForce) {
        try {
            return physicalForce->getNumSinks();
        } catch (std::exception &error) {
            setLastError(error.what());
            return -1;
        }
    }

    EnergyDiff *EnergyDiff_hasProperty(EnergyDiff *energy_diff_ptr, PhysicalProperty *property) {
        try {

            energy_diff_ptr->hasProperty(*property);
            return energy_diff_ptr;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    EnergyDiff *EnergyDiff_hasPropertyisVersionOf(EnergyDiff *energy_diff_ptr, const char *isVersionOf) {
        try {

            energy_diff_ptr->hasProperty(isVersionOf);
            return energy_diff_ptr;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    EnergyDiff *EnergyDiff_hasPropertyFull(EnergyDiff *energy_diff_ptr, const char *property_about, eUriType about_uri_type, const char *is_version_of) {
        try {

            energy_diff_ptr->hasProperty(property_about, about_uri_type, is_version_of);
            return energy_diff_ptr;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }


    char *EnergyDiff_getAbout(EnergyDiff *energy_diff_ptr) {
        try {
            const std::string &about = energy_diff_ptr->getAbout();
            char *cstr = (char *) malloc((about.size() + 1) * sizeof(char));
            strcpy(cstr, about.c_str());
            return cstr;
        } catch (std::exception &error) {
            return funcThatReturnsCharStarFailed(error.what());
        }
    }

    EnergyDiff *EnergyDiff_about(EnergyDiff *energy_diff_ptr, const char *about, eUriType type) {
        try {
            energy_diff_ptr->about(about, type);
            return energy_diff_ptr;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    int PersonalInformation_delete(PersonalInformation *information) {
        try {
            delete information;
            return 0;
        } catch (std::exception &error) {
            setLastError(error.what());
            return -1;
        }
    }

    char *PersonalInformation_getLocalUri(PersonalInformation *information) {
        try {
            const std::string &about = information->getLocalUri();
            char *cstr = (char *) malloc((about.size() + 1) * sizeof(char));
            strcpy(cstr, about.c_str());
            return cstr;
        } catch (std::exception &error) {
            return funcThatReturnsCharStarFailed(error.what());
        }
    }

    PersonalInformation *PersonalInformation_addCreator(PersonalInformation *information, const char *value) {
        try {
            information->addCreator(value);
            return information;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    PersonalInformation *PersonalInformation_addName(PersonalInformation *information, const char *value) {
        try {
            information->addName(value);
            return information;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    PersonalInformation *PersonalInformation_addMbox(PersonalInformation *information, const char *value) {
        try {
            information->addMbox(value);
            return information;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    PersonalInformation *PersonalInformation_addAccountName(PersonalInformation *information, const char *value) {
        try {
            information->addAccountName(value);
            return information;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    PersonalInformation *
    PersonalInformation_addAccountServiceHomepage(PersonalInformation *information, const char *value) {
        try {
            information->addAccountServiceHomepage(value);
            return information;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    PersonalInformation *
    PersonalInformation_addFoafBlank(PersonalInformation *information, const char *predicate, const char *blank_value) {
        try {
            information->addFoafBlank(predicate, blank_value);
            return information;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    PersonalInformation *
    PersonalInformation_addFoafUri(PersonalInformation *information, const char *predicate, const char *uri_value) {
        try {
            information->addFoafUri(predicate, uri_value);
            return information;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    PersonalInformation *
    PersonalInformation_addFoafLiteral(PersonalInformation *information, const char *predicate,
                                       const char *literal_value) {
        try {
            information->addFoafLiteral(predicate, literal_value);
            return information;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    PersonalInformation *
    PersonalInformation_addFoaf(PersonalInformation *information, const char *predicate, const LibrdfNode &value_node) {
        try {
            information->addFoaf(predicate, value_node);
            return information;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    char *PersonalInformation_getMetaid(PersonalInformation *information) {
        try {
            std::string about = information->getMetaid();
            char *cstr = (char *) malloc((about.size() + 1) * sizeof(char));
            strcpy(cstr, about.c_str());
            return cstr;
        } catch (std::exception &error) {
            return funcThatReturnsCharStarFailed(error.what());
        }
    }

    int PersonalInformation_setMetaid(PersonalInformation *information, const char *metaid) {
        try {
            information->setMetaid(metaid);
            return 0;
        } catch (std::exception &error) {
            setLastError(error.what());
            return -1;
        }
    }


    // auxillary types

    int StringVector_getSize(std::vector<std::string> *vec) {
        try {
            return (int) vec->size();
        } catch (std::exception &e) {
            setLastError(e.what());
            return -1;
        }
    }

    char *StringVector_getElementAtIdx(std::vector<std::string> *vec, int idx) {
        try {
            std::string s = vec->operator[](idx);
            char *cstr = (char *) malloc((s.size() + 1) * sizeof(char));
            std::strcpy(cstr, s.c_str());
            return cstr;
        } catch (std::exception &e) {
            setLastError(e.what());
            return nullptr;
        }
    }

    void StringVector_delete(std::vector<std::string> *strVec) {
        try {
            if (strVec) {
                delete strVec;
                strVec = nullptr;
            }
        } catch (std::exception &e) {
            setLastError(e.what());
        }
    }

    int ResultsMap_getSize(ResultsMap *resultsMap) {
        try {
            return resultsMap->size();
        } catch (std::exception &e) {
            setLastError(e.what());
            return -1;
        }
    }

    std::vector<std::string> *ResultsMap_getStringVectorAt(ResultsMap *resultsMap, const char *key) {
        try {
            std::vector<std::string> strVec = (*resultsMap).at(key);
            auto out = new std::vector<std::string>(strVec.begin(), strVec.end());
            return out;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    std::vector<std::string> *ResultsMap_getKeys(ResultsMap *resultsMap) {
        try {
            auto out = new std::vector<std::string>(resultsMap->size());
            int i = 0;
            for (auto [k, v] : *resultsMap) {
                (*out)[i] = k;
                i++;
            }
            return out;
        } catch (std::exception &error) {
            setLastError(error.what());
            return nullptr;
        }
    }

    void ResultsMap_delete(ResultsMap *resultsMap) {
        try {
            if (resultsMap) {
                delete resultsMap;
                resultsMap = nullptr;
            }
        } catch (std::exception &e) {
            setLastError(e.what());
        }
    }

    /**
     * Logger
     */

    Logger *Logger_getLogger() {
        try {
            return Logger::getLogger();
        } catch (std::exception &e) {
            setLastError(e.what());
            return nullptr;
        }
    }

    void Logger_setFormatter(const char *format) {
        try {
            Logger::getLogger()->setFormatter(format);
        } catch (std::exception &e) {
            setLastError(e.what());
        }
    }

    void Logger_setLevel(Logger::LogLevel level) {
        try {
            Logger::getLogger()->setLevel(level);
        } catch (std::exception &e) {
            setLastError(e.what());
        }
    }

    int Logger_getLevel() {
        try {
            return (int) Logger::getLogger()->getLevel();
        } catch (std::exception &e) {
            setLastError(e.what());
            return -1;
        }
    }

    void Logger_enableBacktrace(int num) {
        try {
            Logger::getLogger()->enableBacktrace(num);
        } catch (std::exception &e) {
            setLastError(e.what());
        }
    }

    void Logger_disableBacktrace() {
        try {
            Logger::getLogger()->disableBacktrace();
        } catch (std::exception &e) {
            setLastError(e.what());
        }
    }

    void Logger_dumpBacktrace() {
        try {
            Logger::getLogger()->dumpBacktrace();
        } catch (std::exception &e) {
            setLastError(e.what());
        }
    }

    void Logger_consoleLogger() {
        try {
            Logger::getLogger()->consoleLogger();
        } catch (std::exception &e) {
            setLastError(e.what());
        }
    }

    void Logger_fileLogger(const char *filename) {
        try {
            Logger::getLogger()->fileLogger(filename);
        } catch (std::exception &e) {
            setLastError(e.what());
        }
    }

    void Logger_info(const char *message) {
        try {
            Logger::getLogger()->info(message);
        } catch (std::exception &e) {
            setLastError(e.what());
        }
    }

    void Logger_trace(const char *message) {
        try {
            Logger::getLogger()->trace(message);
        } catch (std::exception &e) {
            setLastError(e.what());
        }
    }

    void Logger_debug(const char *message) {
        try {
            Logger::getLogger()->debug(message);
        } catch (std::exception &e) {
            setLastError(e.what());
        }
    }

    void Logger_warn(const char *message) {
        try {
            Logger::getLogger()->warn(message);
        } catch (std::exception &e) {
            setLastError(e.what());
        }
    }

    void Logger_error(const char *message) {
        try {
            Logger::getLogger()->error(message);
        } catch (std::exception &e) {
            setLastError(e.what());
        }
    }

    void Logger_critical(const char *message) {
        try {
            Logger::getLogger()->critical(message);
        } catch (std::exception &e) {
            setLastError(e.what());
        }
    }

}// namespace omexmeta
