//
// Created by Ciaran on 5/8/2020.
//

#include "omexmeta/OmexMetaCApi.h"

#include <utility>


namespace omexmeta {
    int free_c_char_star(char *c) {
        try {
            if (c != nullptr)
                free(c);
            return 0;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            return -1;
        }
    }

    /**
     * For testing.
     */
    char *_func_that_returns_dynamic_alloc_str() {
        std::string str = "ADynamicallyAllocatedStringForTesting";
        char *cstr = (char *) malloc((str.size() + 1) * sizeof(char *));
        strcpy(cstr, str.c_str());
        return cstr;
    }


    /*************************************************************
 *  RDF methods
 */

    RDF *RDF_new(const char *storage_type, const char *storage_name,
                 const char *storage_options, const char *model_options) {
        try {
            RDF *rdf_ptr = new RDF(storage_type, storage_name, storage_options, model_options);
            return rdf_ptr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
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
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    int RDF_addFromString(RDF *rdf_ptr, const char *str, const char *format) {
        try {
            rdf_ptr->addFromString(str, format);
            return 0;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
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
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    int RDF_addFromUri(RDF *rdf_ptr, const char *uri_string, const char *format) {
        try {
            rdf_ptr->addFromUri(uri_string, format);
            return 0;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
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
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    int RDF_addFromFile(RDF *rdf_ptr, const char *uri_string, const char *format) {
        try {
            rdf_ptr->addFromFile(uri_string, format);
            return 0;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
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
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    int RDF_toFile(RDF *rdf_ptr, const char *format, const char *filename) {
        try {
            rdf_ptr->toFile(filename, format);
            return 0;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            return -1;
        }
    }

    char *RDF_query(RDF *rdf_ptr, const char *query_str, const char *results_format) {
        try {
            std::string results = rdf_ptr->query(query_str, results_format);
            char *s = (char *) malloc((results.size() + 1) * sizeof(char *));
            strcpy(s, results.c_str());
            return s;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    int RDF_size(RDF *rdf_ptr) {
        try {
            return rdf_ptr->size();
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            return -1;
        }
    }

    int RDF_setRepositoryUri(RDF *rdf_ptr, const char *repository_uri) {
        try {
            rdf_ptr->setRepositoryUri(std::move(repository_uri));
            return 0;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            return -1;
        }
    }

    int RDF_setArchiveUri(RDF *rdf_ptr, const char *archive_uri) {
        try {
            rdf_ptr->setArchiveUri(std::move(archive_uri));
            return 0;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            return -1;
        }
    }

    int RDF_setModelUri(RDF *rdf_ptr, const char *model_uri) {
        try {
            rdf_ptr->setModelUri(std::move(model_uri));
            return 0;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            return -1;
        }
    }

    char *RDF_getRepositoryUri(RDF *rdf_ptr) {
        try {
            const std::string &str = rdf_ptr->getRepositoryUri();
            char *cstr = (char *) malloc((str.size() + 1) * sizeof(char *));
            strcpy(cstr, str.c_str());
            return cstr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    char *RDF_getArchiveUri(RDF *rdf_ptr) {
        try {
            const std::string &str = rdf_ptr->getArchiveUri();
            char *cstr = (char *) malloc((str.size() + 1) * sizeof(char *));
            strcpy(cstr, str.c_str());
            return cstr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    char *RDF_getModelUri(RDF *rdf_ptr) {
        try {
            const std::string &str = rdf_ptr->getModelUri();
            char *cstr = (char *) malloc((str.size() + 1) * sizeof(char *));
            strcpy(cstr, str.c_str());
            return cstr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    char *RDF_getLocalUri(RDF *rdf_ptr) {
        try {
            const std::string &str = rdf_ptr->getLocalUri();
            char *cstr = (char *) malloc((str.size() + 1) * sizeof(char *));
            strcpy(cstr, str.c_str());
            return cstr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }


    bool RDF_equals_rdf_vs_string(RDF *rdf_ptr, const char *serialized_rdf, const char *format) {
        try {
            return RDF::equals(rdf_ptr, serialized_rdf, format);
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    bool RDF_equals_rdf_vs_rdf(RDF *rdf_ptr1, RDF *rdf_ptr2, const char *format) {
        try {
            return RDF::equals(rdf_ptr1, rdf_ptr2, format);
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    bool RDF_equals_string_vs_string(const char *first_rdf_graph, const char *second_rdf_graph, const char *format) {
        try {
            return RDF::equals(first_rdf_graph, second_rdf_graph, format);
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    Editor *RDF_toEditor(RDF *rdf_ptr, const char *xml, bool generate_new_metaids, bool sbml_semantic_extraction) {
        try {
            return rdf_ptr->toEditorPtr(xml, generate_new_metaids, sbml_semantic_extraction);
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }


    /*********************************************************************
 * Editor class methods
 */

    SingularAnnotation *Editor_newSingularAnnotation(Editor *editor_ptr) {
        try {
            auto *singularAnnotation = new SingularAnnotation();
            singularAnnotation->setLocalUri(editor_ptr->getLocalUri());
            singularAnnotation->setModelUri(editor_ptr->getModelUri());
            return singularAnnotation;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }
    PersonalInformation *Editor_newPersonalInformation(Editor *editor_ptr) {
        try {
            return new PersonalInformation(editor_ptr->getModel(), editor_ptr->getModelUri(),
                                           editor_ptr->getLocalUri());
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    PhysicalEntity *Editor_newPhysicalEntity(Editor *editor_ptr) {
        try {
            return new PhysicalEntity(editor_ptr->getModel(), editor_ptr->getModelUri(), editor_ptr->getLocalUri());
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    PhysicalForce *Editor_newPhysicalForce(Editor *editor_ptr) {
        try {
            return new PhysicalForce(editor_ptr->getModel(), editor_ptr->getModelUri(), editor_ptr->getLocalUri());
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }
    PhysicalProcess *Editor_newPhysicalProcess(Editor *editor_ptr) {
        try {
            return new PhysicalProcess(editor_ptr->getModel(), editor_ptr->getModelUri(), editor_ptr->getLocalUri());
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    PhysicalProperty *Editor_newPhysicalProperty(Editor *editor_ptr) {
        try {
            auto* property = new PhysicalProperty(editor_ptr->getModel(), editor_ptr->getModelUri(), editor_ptr->getLocalUri());
            return property;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }


    int Editor_addNamespace(Editor *editor_ptr, const char *namespace_, const char *prefix) {
        try {
            editor_ptr->addNamespace(namespace_, prefix);
            return 0;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            return -1;
        }
    }

    int Editor_addSingleAnnotation(Editor *editor_ptr, SingularAnnotation *singularAnnotation) {
        try {
            editor_ptr->addSingleAnnotation(*singularAnnotation);
            return 0;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            return -1;
        }
    }

    int Editor_addPhysicalEntity(Editor *editor_ptr, PhysicalEntity *physicalEntity) {
        try {
            editor_ptr->addPhysicalEntity(*physicalEntity);
            return 0;

        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            return -1;
        }
    }

    int Editor_addPhysicalProcess(Editor *editor_ptr, PhysicalProcess *physicalProcess) {
        try {
            editor_ptr->addPhysicalProcess(*physicalProcess);
            return 0;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            return -1;
        }
    }

    int Editor_addPhysicalProperty(Editor *editor_ptr, PhysicalProperty *physicalProperty) {
        try {
            editor_ptr->addPhysicalProperty(*physicalProperty);
            return 0;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            return -1;
        }
    }

    int Editor_addPhysicalForce(Editor *editor_ptr, PhysicalForce *physicalForce) {
        try {
            editor_ptr->addPhysicalForce(*physicalForce);
            return 0;

        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            return -1;
        }
    }

    int Editor_addPersonalInformation(Editor *editor_ptr, PersonalInformation *personalInformation) {
        try {
            editor_ptr->addPersonalInformation(personalInformation);
            return 0;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            return -1;
        }
    }

    int Editor_removeSingleAnnotation(Editor *editor_ptr, SingularAnnotation *singularAnnotation) {
        try {
            editor_ptr->removeSingleAnnotation(*singularAnnotation);
            return 0;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            return -1;
        }
    }

    int Editor_removePhysicalEntity(Editor *editor_ptr, PhysicalEntity *physicalEntity) {
        try {
            editor_ptr->removePhysicalEntity(*physicalEntity);
            return 0;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            return -1;
        }
    }

    int Editor_removePhysicalProcess(Editor *editor_ptr, PhysicalProcess *physicalProcess) {
        try {
            editor_ptr->removePhysicalProcess(*physicalProcess);
            return 0;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            return -1;
        }
    }

    int Editor_removePhysicalForce(Editor *editor_ptr, PhysicalForce *physicalForce) {
        try {
            editor_ptr->removePhysicalForce(*physicalForce);
            return 0;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            return -1;
        }
    }

    int Editor_removePersonalInformation(Editor *editor_ptr, PersonalInformation *information) {
        try {
            editor_ptr->removePersonalInformation(information);
            return 0;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            return -1;
        }
    }

    int Editor_checkValidMetaid(Editor *editor_ptr, const char *id) {
        try {
            editor_ptr->checkValidMetaid(id);
            return 0;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
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
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    int Editor_getNumMetaIds(Editor *editor_ptr) {
        try {
            return editor_ptr->getMetaids().size();
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
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
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    int Editor_delete(Editor *editor_ptr) {
        try {
            if (!editor_ptr)
                return -1;
            delete editor_ptr;
            return 0;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
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
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    char *Editor_getLocalUri(Editor *editor_ptr) {
        try {
            std::string str = editor_ptr->getLocalUri();
            char *cstr = (char *) malloc((str.size() + 1) * sizeof(char *));
            strcpy(cstr, str.c_str());
            return cstr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    char *Editor_getModelUri(Editor *editor_ptr) {
        try {
            std::string str = editor_ptr->getModelUri();
            char *cstr = (char *) malloc((str.size() + 1) * sizeof(char *));
            strcpy(cstr, str.c_str());
            return cstr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    char *Editor_getRepositoryUri(Editor *editor_ptr) {
        try {
            std::string str = editor_ptr->getRepositoryUri();
            char *cstr = (char *) malloc((str.size() + 1) * sizeof(char *));
            strcpy(cstr, str.c_str());
            return cstr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    Editor *Editor_addCreator(Editor *editor_ptr, const char *orcid_id) {
        try {
            editor_ptr->addCreator(orcid_id);
            return editor_ptr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    Editor *Editor_addCurator(Editor *editor_ptr, const char *orcid_id) {
        try {
            editor_ptr->addCurator(orcid_id);
            return editor_ptr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    Editor *Editor_addTaxon(Editor *editor_ptr, const char *taxon_id) {
        try {
            editor_ptr->addTaxon(taxon_id);
            return editor_ptr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    Editor *Editor_addPubmed(Editor *editor_ptr, const char *pubmedid) {
        try {
            editor_ptr->addPubmed(pubmedid);
            return editor_ptr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    Editor *Editor_addDescription(Editor *editor_ptr, const char *date) {
        try {
            editor_ptr->addDescription(date);
            return editor_ptr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    Editor *Editor_addDateCreated(Editor *editor_ptr, const char *date) {
        try {
            editor_ptr->addDateCreated(date);
            return editor_ptr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    Editor *Editor_addParentModel(Editor *editor_ptr, const char *biomod_id) {
        try {
            editor_ptr->addParentModel(biomod_id);
            return editor_ptr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }


    int SingularAnnotation_delete(SingularAnnotation *singularAnnotation) {
        try {
            if (singularAnnotation != nullptr) {
                singularAnnotation->freeStatement();
                delete singularAnnotation;
            }
            return 0;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            return -1;
        }
    }


    int free_singular_annotation(SingularAnnotation *singularAnnotationPtr) {
        try {
            free(singularAnnotationPtr);
            return 0;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            return -1;
        }
    }

    SingularAnnotation *
    SingularAnnotation_about(SingularAnnotation *singular_annotation, const char *about) {
        try {
            singular_annotation->about(about);
            return singular_annotation;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    };

    SingularAnnotation *SingularAnnotation_setPredicate(
            SingularAnnotation *singular_annotation, const char *namespace_, const char *term) {
        try {
            singular_annotation->setPredicate(namespace_, term);
            return singular_annotation;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    SingularAnnotation *SingularAnnotation_predicate(
            SingularAnnotation *singular_annotation, const char *namespace_, const char *term) {
        return SingularAnnotation_setPredicate(singular_annotation, namespace_, term);
    }

    SingularAnnotation *SingularAnnotation_setPredicateFromUri(
            SingularAnnotation *singular_annotation, const char *uri) {
        try {
            singular_annotation->setPredicate(uri);
            return singular_annotation;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
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
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
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
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
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
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
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
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    char *SingularAnnotation_getPredicate(SingularAnnotation *singular_annotation) {
        try {
            std::string predicate_str = singular_annotation->getPredicateStr();
            char *cstr = (char *) malloc((predicate_str.size() + 1) * sizeof(char));
            strcpy(cstr, predicate_str.c_str());
            return cstr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    char *SingularAnnotation_getResource(SingularAnnotation *singular_annotation) {
        try {
            std::string resource = singular_annotation->getResourceStr();
            char *cstr = (char *) malloc((resource.size() + 1) * sizeof(char));
            strcpy(cstr, resource.c_str());
            return cstr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    char *SingularAnnotation_str(SingularAnnotation *singular_annotation, const char *format) {
        try {
            std::string str = singular_annotation->str(format);
            char *cstr = (char *) malloc((str.size() + 1) * sizeof(char));
            strcpy(cstr, str.c_str());
            return cstr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

/*********************************************************************
 * PhysicalProperty class methods
 */
    char *PhysicalProperty_getAbout(PhysicalProperty *property){
        try {
            const std::string& str = property->getAbout();
            char *cstr = (char *) malloc((str.size() + 1) * sizeof(char));
            strcpy(cstr, str.c_str());
            return cstr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    PhysicalProperty *PhysicalProperty_about(PhysicalProperty *property, const char *about, eUriType type){
        try {
            property->about(about, type);
            return property;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    char *PhysicalProperty_getIsVersionOfValue(PhysicalProperty *property){
        try {
            const std::string& str = property->getIsVersionOfValue();
            char *cstr = (char *) malloc((str.size() + 1) * sizeof(char));
            strcpy(cstr, str.c_str());
            return cstr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    PhysicalProperty *PhysicalProperty_isPropertyOf(PhysicalProperty *property, const char *is_property_of, eUriType type) {
        try {
            property->isPropertyOf(is_property_of, type);
            return property;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    PhysicalProperty *PhysicalProperty_isVersionOf(PhysicalProperty *property, const char *is_version_of){
        try {
            property->isVersionOf(is_version_of);
            return property;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }


    char *PhysicalProperty_getIsPropertyOfValue(PhysicalProperty *property){
        try {
            const std::string& str = property->getIsPropertyOfValue();
            char *cstr = (char *) malloc((str.size() + 1) * sizeof(char));
            strcpy(cstr, str.c_str());
            return cstr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    int PhysicalProperty_delete(PhysicalProperty* property){
        try {
            delete property;
            return 0;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
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
            fprintf(stderr, "OmexMetaException: %s", error.what());
            return -1;
        }
    }

    int PhysicalEntity_freeAll(PhysicalEntity *physical_entity_ptr) {
        try {
            physical_entity_ptr->free();
            delete physical_entity_ptr;
            return 0;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            return -1;
        }
    }

    PhysicalEntity *PhysicalEntity_setPhysicalProperty(
            PhysicalEntity *physical_entity_ptr, const char *subject_metaid, const char *physical_property) {
        try {
            physical_entity_ptr->setPhysicalProperty(subject_metaid, physical_property);
            return physical_entity_ptr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    PhysicalEntity *PhysicalEntity_setIdentity(PhysicalEntity *physical_entity_ptr, const char *identity_resource) {
        try {
            physical_entity_ptr->setIdentity(identity_resource);
            return physical_entity_ptr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    PhysicalEntity *PhysicalEntity_identity(PhysicalEntity *physical_entity_ptr, const char *identity_resource) {
        try {
            return PhysicalEntity_setIdentity(physical_entity_ptr, identity_resource);
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    PhysicalEntity *PhysicalEntity_addLocation(PhysicalEntity *physical_entity_ptr, const char *location_resource) {
        try {
            physical_entity_ptr->addLocation(location_resource);
            return physical_entity_ptr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    char *PhysicalEntity_getAbout(PhysicalEntity *physical_entity_ptr) {
        try {
            std::string about = physical_entity_ptr->getAbout();
            char *cstr = (char *) malloc((about.size() + 1) * sizeof(char));
            strcpy(cstr, about.c_str());
            return cstr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    char *PhysicalEntity_getIdentity(PhysicalEntity *physical_entity_ptr) {
        try {
            std::string identity = physical_entity_ptr->getIdentityResource().str();
            char *cstr = (char *) malloc((identity.size() + 1) * sizeof(char));
            strcpy(cstr, identity.c_str());
            return cstr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    int PhysicalEntity_getNumLocations(PhysicalEntity *physicalEntity) {
        try {
            return physicalEntity->getNumLocations();
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            return -1;
        }
    }

    char *PhysicalEntity_getLocation(PhysicalEntity *physical_entity_ptr, int index) {
        try {
            std::string location = physical_entity_ptr->getLocationResources()[index].str();
            char *cstr = (char *) malloc((location.size() + 1) * sizeof(char *));
            strcpy(cstr, location.c_str());
            return cstr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    char *PhysicalEntity_str(PhysicalEntity *physical_entity_ptr, const char *format, const char *base_uri) {
        try {
            Triples triples = physical_entity_ptr->toTriples();
            std::string str = triples.str(format, base_uri);
            triples.freeTriples();
            char *cstr = (char *) malloc((str.size() + 1) * sizeof(char));
            strcpy(cstr, str.c_str());
            return cstr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    PhysicalEntity *PhysicalEntity_hasProperty(PhysicalEntity *physical_entity_ptr, PhysicalProperty* property) {
        try {

            physical_entity_ptr->hasProperty(*property);
            return physical_entity_ptr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    PhysicalEntity *PhysicalEntity_hasPropertyisVersionOf(PhysicalEntity *physical_entity_ptr, const char* isVersionOf) {
        try {

            physical_entity_ptr->hasProperty(isVersionOf);
            return physical_entity_ptr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    PhysicalEntity *PhysicalEntity_hasPropertyFull(PhysicalEntity *physical_entity_ptr, const char* property_about, eUriType about_uri_type, const char* is_version_of, const char* is_property_of, eUriType is_property_of_uri_type) {
        try {

            physical_entity_ptr->hasProperty(property_about, about_uri_type, is_version_of, is_property_of, is_property_of_uri_type);
            return physical_entity_ptr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    PhysicalEntity *PhysicalEntity_hasPropertyAutoGeneratePropertyId(PhysicalEntity *physical_entity_ptr, const char* property_about, eUriType about_uri_type, const char* is_version_of) {
        try {

            physical_entity_ptr->hasProperty(property_about, about_uri_type, is_version_of);
            return physical_entity_ptr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    PhysicalEntity *PhysicalEntity_isPartOf(PhysicalEntity *physical_entity_ptr, const char *is_part_of) {
        try {
            physical_entity_ptr->isPartOf(is_part_of);
            return physical_entity_ptr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    PhysicalEntity *PhysicalEntity_hasPart(PhysicalEntity *physical_entity_ptr, const char *part) {
        try {
            physical_entity_ptr->hasPart(part);
            return physical_entity_ptr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    PhysicalEntity *PhysicalEntity_about(PhysicalEntity *physical_entity_ptr, const char *about) {
        try {
            physical_entity_ptr->about(about);
            return physical_entity_ptr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    PhysicalEntity *PhysicalEntity_aboutWithUriType(PhysicalEntity *physical_entity_ptr, const char *about, eUriType type) {
        try {
            physical_entity_ptr->about(about, type);
            return physical_entity_ptr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }


    int PhysicalProcess_delete(PhysicalProcess *physicalProcess) {
        try {
            delete physicalProcess;
            return 0;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            return -1;
        }
    }

    int PhysicalProcess_freeAll(PhysicalProcess *physicalProcess) {
        try {
            physicalProcess->free();
            delete physicalProcess;
            return 0;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            return -1;
        }
    }

    PhysicalProcess *
    PhysicalProcess_setPhysicalProperty(PhysicalProcess *physical_process, const char *subject_metaid,
                                        const char *physical_property) {
        try {
            physical_process->setPhysicalProperty(subject_metaid, physical_property);
            return physical_process;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    PhysicalProcess *
    PhysicalProcess_addSource(PhysicalProcess *physical_process,
                              const char *physical_entity_reference, eUriType type,int multiplier) {
        try {
            physical_process->addSource(physical_entity_reference, type, multiplier);
            return physical_process;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    PhysicalProcess *
    PhysicalProcess_addSink(PhysicalProcess *physical_process,
                            const char *physical_entity_reference, eUriType type, int multiplier) {
        try {
            physical_process->addSink(physical_entity_reference, type, multiplier);
            return physical_process;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    PhysicalProcess *
    PhysicalProcess_addMediator(PhysicalProcess *physical_process,
                                const char *physical_entity_reference, eUriType type) {
        try {
            physical_process->addMediator(physical_entity_reference, type);
            return physical_process;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    char *PhysicalProcess_str(PhysicalProcess *physical_process_ptr, const char *format, const char *base_uri) {
        try {
            Triples triples = physical_process_ptr->toTriples();
            std::string str = triples.str(format, base_uri);
            triples.freeTriples();
            char *cstr = (char *) malloc((str.size() + 1) * sizeof(char));
            strcpy(cstr, str.c_str());
            return cstr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }


    PhysicalProcess *PhysicalProcess_hasProperty(PhysicalProcess *physical_process_ptr, PhysicalProperty* property) {
        try {

            physical_process_ptr->hasProperty(*property);
            return physical_process_ptr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    PhysicalProcess *PhysicalProcess_hasPropertyisVersionOf(PhysicalProcess *physical_process_ptr, const char* isVersionOf) {
        try {

            physical_process_ptr->hasProperty(isVersionOf);
            return physical_process_ptr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    PhysicalProcess *PhysicalProcess_hasPropertyFull(PhysicalProcess *physical_process_ptr, const char* property_about, eUriType about_uri_type, const char* is_version_of, const char* is_property_of, eUriType is_property_of_uri_type) {
        try {

            physical_process_ptr->hasProperty(property_about, about_uri_type, is_version_of, is_property_of, is_property_of_uri_type);
            return physical_process_ptr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    PhysicalProcess *PhysicalProcess_hasPropertyAutoGeneratePropertyId(PhysicalProcess *physical_process_ptr, const char* property_about, eUriType about_uri_type, const char* is_version_of) {
        try {

            physical_process_ptr->hasProperty(property_about, about_uri_type, is_version_of);
            return physical_process_ptr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    char *PhysicalProcess_getAbout(PhysicalProcess *physical_process_ptr) {
        try {
            const std::string &about = physical_process_ptr->getAbout();
            char *cstr = (char *) malloc((about.size() + 1) * sizeof(char));
            strcpy(cstr, about.c_str());
            return cstr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    int PhysicalProcess_getNumSources(PhysicalProcess *physicalProcess) {
        try {
            return physicalProcess->getNumSources();
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            return -1;
        }
    }

    int PhysicalProcess_getNumSinks(PhysicalProcess *physicalProcess) {
        try {
            return physicalProcess->getNumSinks();
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            return -1;
        }
    }

    int PhysicalProcess_getNumMediators(PhysicalProcess *physicalProcess) {
        try {
            return physicalProcess->getNumMediators();
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            return -1;
        }
    }


    PhysicalProcess *PhysicalProcess_about(PhysicalProcess *physical_process_ptr, const char *about) {
        try {
            physical_process_ptr->about(about);
            return physical_process_ptr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    PhysicalProcess *PhysicalProcess_aboutWithUriType(PhysicalProcess *physical_process_ptr, const char *about, eUriType type) {
        try {
            physical_process_ptr->about(about, type);
            return physical_process_ptr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }


    int PhysicalForce_delete(PhysicalForce *physicalForce) {
        try {
            delete physicalForce;
            return 0;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            return -1;
        }
    }

    int PhysicalForce_freeAll(PhysicalForce *physical_force_ptr) {
        try {
            physical_force_ptr->free();
            delete physical_force_ptr;
            return 0;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            return -1;
        }
    }


    PhysicalForce *PhysicalForce_addSource(PhysicalForce *physical_force_ptr,
                                           const char *physical_entity_reference, eUriType type, int multiplier) {
        try {
            physical_force_ptr->addSource(physical_entity_reference, type, multiplier);
            return physical_force_ptr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    PhysicalForce *PhysicalForce_addSink(PhysicalForce *physical_force_ptr,
                                         const char *physical_entity_reference, eUriType type, int multiplier) {
        try {
            physical_force_ptr->addSink(physical_entity_reference, type, multiplier);
            return physical_force_ptr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    PhysicalForce *PhysicalForce_setPhysicalProperty(PhysicalForce *physical_force_ptr, const char *subject_metaid,
                                                     const char *physical_property) {
        try {
            physical_force_ptr->setPhysicalProperty(subject_metaid, physical_property);
            return physical_force_ptr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    int PhysicalForce_getNumSources(PhysicalForce *physicalForce) {
        try {
            return physicalForce->getNumSources();
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            return -1;
        }
    }

    int PhysicalForce_getNumSinks(PhysicalForce *physicalForce) {
        try {
            return physicalForce->getNumSinks();
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            return -1;
        }
    }

    char *PhysicalForce_str(PhysicalForce *physical_force_ptr, const char *format, const char *base_uri) {
        try {
            Triples triples = physical_force_ptr->toTriples();
            std::string str = triples.str(format, base_uri);
            triples.freeTriples();
            char *cstr = (char *) malloc((str.size() + 1) * sizeof(char));
            strcpy(cstr, str.c_str());
            return cstr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }


    PhysicalForce *PhysicalForce_hasProperty(PhysicalForce *physical_force_ptr, PhysicalProperty* property) {
        try {

            physical_force_ptr->hasProperty(*property);
            return physical_force_ptr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    PhysicalForce *PhysicalForce_hasPropertyisVersionOf(PhysicalForce *physical_force_ptr, const char* isVersionOf) {
        try {

            physical_force_ptr->hasProperty(isVersionOf);
            return physical_force_ptr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    PhysicalForce *PhysicalForce_hasPropertyFull(PhysicalForce *physical_force_ptr, const char* property_about, eUriType about_uri_type, const char* is_version_of, const char* is_property_of, eUriType is_property_of_uri_type) {
        try {

            physical_force_ptr->hasProperty(property_about, about_uri_type, is_version_of, is_property_of, is_property_of_uri_type);
            return physical_force_ptr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    PhysicalForce *PhysicalForce_hasPropertyAutoGeneratePropertyId(PhysicalForce *physical_force_ptr, const char* property_about, eUriType about_uri_type, const char* is_version_of) {
        try {

            physical_force_ptr->hasProperty(property_about, about_uri_type, is_version_of);
            return physical_force_ptr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }


    char *PhysicalForce_getAbout(PhysicalForce *physical_force_ptr) {
        try {
            std::string about = physical_force_ptr->getAbout();
            char *cstr = (char *) malloc((about.size() + 1) * sizeof(char));
            strcpy(cstr, about.c_str());
            return cstr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    PhysicalForce *PhysicalForce_about(PhysicalForce *physical_force_ptr, const char *about) {
        try {
            physical_force_ptr->about(about);
            return physical_force_ptr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    PhysicalForce *PhysicalForce_aboutWithUriType(PhysicalForce *physical_force_ptr, const char *about, eUriType type) {
        try {
            physical_force_ptr->about(about, type);
            return physical_force_ptr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    int PersonalInformation_delete(PersonalInformation *information) {
        try {
            delete information;
            return 0;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
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
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    int PersonalInformation_setLocalUri(PersonalInformation *information, const char *localUri) {
        try {
            information->setLocalUri(localUri);
            return 0;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            return -1;
        }
    }

    PersonalInformation *PersonalInformation_addCreator(PersonalInformation *information, const char *value) {
        try {
            information->addCreator(value);
            return information;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    PersonalInformation *PersonalInformation_addName(PersonalInformation *information, const char *value) {
        try {
            information->addName(value);
            return information;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    PersonalInformation *PersonalInformation_addMbox(PersonalInformation *information, const char *value) {
        try {
            information->addMbox(value);
            return information;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    PersonalInformation *PersonalInformation_addAccountName(PersonalInformation *information, const char *value) {
        try {
            information->addAccountName(value);
            return information;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    PersonalInformation *
    PersonalInformation_addAccountServiceHomepage(PersonalInformation *information, const char *value) {
        try {
            information->addAccountServiceHomepage(value);
            return information;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    PersonalInformation *
    PersonalInformation_addFoafBlank(PersonalInformation *information, const char *predicate, const char *blank_value) {
        try {
            information->addFoafBlank(predicate, blank_value);
            return information;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    PersonalInformation *
    PersonalInformation_addFoafUri(PersonalInformation *information, const char *predicate, const char *uri_value) {
        try {
            information->addFoafUri(predicate, uri_value);
            return information;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    PersonalInformation *
    PersonalInformation_addFoafLiteral(PersonalInformation *information, const char *predicate,
                                       const char *literal_value) {
        try {
            information->addFoafLiteral(predicate, literal_value);
            return information;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    PersonalInformation *
    PersonalInformation_addFoaf(PersonalInformation *information, const char *predicate, const LibrdfNode &value_node) {
        try {
            information->addFoaf(predicate, value_node);
            return information;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    char *PersonalInformation_getMetaid(PersonalInformation *information) {
        try {
            std::string about = information->getMetaid();
            char *cstr = (char *) malloc((about.size() + 1) * sizeof(char));
            strcpy(cstr, about.c_str());
            return cstr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    int PersonalInformation_setMetaid(PersonalInformation *information, const char *metaid) {
        try {
            information->setMetaid(metaid);
            return 0;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            return -1;
        }
    }

    char *PersonalInformation_getModelUri(PersonalInformation *information) {
        try {
            std::string about = information->getModelUri();
            char *cstr = (char *) malloc((about.size() + 1) * sizeof(char));
            strcpy(cstr, about.c_str());
            return cstr;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            exit(1);
        }
    }

    int PersonalInformation_setModelUri(PersonalInformation *information, const char *modelUri) {
        try {
            information->setModelUri(modelUri);
            return 0;
        } catch (std::exception &error) {
            fprintf(stderr, "OmexMetaException: %s", error.what());
            return -1;
        }
    }


}// namespace omexmeta
