//
// Created by Ciaran on 4/15/2020.
//

#ifndef LIBOMEXMETA_EDITOR_H
#define LIBOMEXMETA_EDITOR_H


#include "omexmeta/EnergyDiff.h"
#include "omexmeta/Error.h"
#include "omexmeta/MarkupIdentifier.h"
#include "omexmeta/OmexMetaUtils.h"
#include "omexmeta/OmexMetaXml.h"
#include "omexmeta/Participant.h"
#include "omexmeta/PersonalInformation.h"
#include "omexmeta/PhysicalEntity.h"
#include "omexmeta/PhysicalProcess.h"
#include "omexmeta/Predicate.h"
#include "omexmeta/PropertyBearer.h"
#include "omexmeta/SBMLSemanticExtraction.h"
#include "omexmeta/Triple.h"
#include "omexmeta/UriHandler.h"
#include "omexmeta_export.h"
#include "redland/RedlandAPI.h"
#include "redland/librdf.h"

#include <filesystem>

using namespace redland;


namespace omexmeta {

    class IRDF;

    /**
     * @brief Add or change annotations in xml.
     *
     */
    class OMEXMETA_EXPORT Editor {
    public:
        /**
         * @brief constructor for Editor.
         * @param xml_or_file The valid xml content for annotation OR the path to the file on disk containing this content
         * @param generate_new_metaids. Autogenerate metaids for xml element that do not already have them
         * @param sbml_semantic_extraction. When @param xml_or_file is determined to be sbml, automatically extract some information regarding species and reactions. This
         * option is ignored when @param xml_or_file is not sbml. Default is true.
         * @param model a reference to the current model (owned by RDF).
         * @param nm_map a set of namespaces for current xml
         *
         * The Editor is usually instantiated from the RDF::to_editor class which
         * automatically takes care of the @param model and @param ns_map arguments. When
         * instantiated, the editor class automatically reads the XML and adds metaids to
         * some or all of the elements, depending on the XML type parameter. If the user
         * specifies that they are annotating an SBML model, the elements returned by
         * SBMLAssistant::getValidElements() are given metaids (if not exist), while if
         * the user chooses cellml the elements returned by CellMLAssistant::getValidElements()
         * are used. If the type is unknown, then all elements are given metaids.
         */
        explicit Editor(std::string xml_or_file, bool create_ids, LibrdfModel &model, NamespaceMap &ns_map,
                        UriHandler &uriHandler, bool generate_new_metaids = false, bool sbml_semantic_extraction = true);

        /**
         * We no longer required to free the
         * triples_ used by Editor since they are
         * created and freed inplace - i.e.
         * locally, not at the class scope.
         */
        ~Editor() = default;

        [[nodiscard]] int size() const;

        /**
         * @brief returns a hashmap of namespaces to prefixes.
         * @return Map where keys are namespaces and values are prefixes
         */
        [[nodiscard]] const NamespaceMap &getNamespaces() const;

        /**
         * @brief return the underlying librdf_model* pointer
         * @return the librdf_model pointer
         */
        [[nodiscard]] LibrdfModel& getModel() const;

        /**
         * @brief set the namespace map.
         */
        void setNamespaces(const NamespaceMap &namespaces);

        /**
         * @brief return the xml
         * @return the xml string after metaids are added
         */
        [[nodiscard]] const std::string &getXml() const;

        /**
         * @brief returns a list of metaids both that existed previously and that was added
         * during instantiation.
         * @return vector of metaids used in the xml
         */
        [[nodiscard]] const std::vector<std::string> &getMetaids() const;

        /**
         * @brief add a namespace
         * @param ns the namespace
         * @param prefix the prefix used in serialized annotations to refer to the namespace
         */
        void addNamespace(const std::string &ns, std::string prefix);

        /**
         * @brief Add a SingleAnnotation (aka a Triple) to the model
         * @param subject the subject portion of the triple
         * @param pointer to the predicate the predicate portion of the triple. Ths is a pointer to support polymorphic calls.
         * @param resource the resource portion of the triple
         */
        void addSingleAnnotation(LibrdfNode subject, const PredicatePtr &predicate_ptr, const LibrdfNode &resource);

        /**
         * @brief Add a SingleAnnotation (aka Triple) to the rdf graph.
         * @param singularAnnotation An instance of SingularAnnotation to add to the model
         */
        void addSingleAnnotation(SingularAnnotation &singularAnnotation);

        /**
         * @brief remove a singular annotation (aka Triple) from the rdf graph
         * @param singularAnnotation An instance of SingularAnnotation to remove from the model
         */
        void removeSingleAnnotation(const SingularAnnotation &singularAnnotation) const;

        /**
         * @brief add a composite annotation to the rdf graph.
         * @param phenomenonPtr A pointer to an object of type PhysicalPhenomenon, the superclass of
         * the composite annotations.
         *
         * Composite annotations currently supported are PhysicalEntity,
         * PhysicalProcess and EnergyDiff. The PhysicalDependency
         * type will be supported in future releases.
         *
         * For developers. Consider removing this function in favour of using the
         * add* functions.
         */
        void addCompositeAnnotation(PropertyBearer *phenomenonPtr);

        /**
         * @brief add a physical process to the rdf graph
         */
        void addPhysicalProperty(PhysicalProperty &physicalProperty);

        /**
         * @brief add a composite annotation of type PhysicalEntity to the rdf graph
         * @param physicalEntity An instance of a PhysicalEntity object to add to the rdf graph.
         */
        void addPhysicalEntity(PhysicalEntity &physicalEntity);

        /**
         * @brief remove triples associated with a a PhysicalEntity object from the rdf graph
         * @param physicalEntity the PhysicalEntityto remove
         */
        void removePhysicalEntity(PhysicalEntity &physicalEntity) const;

        /**
         * @brief remove triples associated with a PersonalInformation object from the rdf graph
         * @param information the PersonalInformation object to remove.
         */
        void removePersonalInformation(PersonalInformation *information) const;

        /**
         * @brief add a composite annotation of type PhysicalProcess to the rdf graph
         * @param physicalProcess An instance of a PhysicalProcess object to add to the rdf graph.
         */
        void addPhysicalProcess(PhysicalProcess &physicalProcess);

        /**
         * @brief remove triples associated with a PhysicalProcess object from the rdf graph
         * @param physicalProcess the PhysicalProcessto remove
         */
        void removePhysicalProcess(PhysicalProcess &physicalProcess) const;

        /**
         * @brief add a composite annotation of type EnergyDiff to the rdf graph
         * @param ediff An instance of a EnergyDiff objec to add to the rdf graph.
         */
        void addEnergyDiff(EnergyDiff &ediff);

        /**
         * @brief add a PersonalInformation class to the rdf model
         * @param personalInformation An instance of a PersonalInformation object to add to the rdf graph.
         */
        void addPersonalInformation(PersonalInformation *personalInformation);

        /**
         * @brief remove triples associated with a a EnergyDiff object from the rdf graph
         * @param physicalForce the EnergyDiff to remove
         */
        void removeEnergyDiff(EnergyDiff &physicalForce) const;

        /**
         * @brief check that a metaid is valid by comparing
         * with the output from Editor::getMetaIds()
         */
        void checkValidMetaid(const std::string &metaid);

        /**
         * @brief extract namespace part of uri from @parameter predicate_string
         * and add it to namespace_ if we know it.
         */
        void addNamespaceFromAnnotation(const std::string &predicate_string);

        /**
         * @brief get the string that is being used for the metaid base (default is OmexMetaID)
         * @details this base will only be used when the generate_metaids boolean is set to true in the constructor.
         * @returns std::string of metaid base
         */
        const std::string &getMetaidBase() const;

        /**
         * @brief set the base metaid string (default is OmexMetaId)
         * @param metaidBase the string you want to use for metaid base
         * @returns void
         * @details using editor.setMetaidBase("MyNewMetaid") will make metaids
         * added by libomexmeta look like MyNewMetaid0001, MyNewMetaid0002, etc.
         * It is assumed that it will not be necessary to have more than 9999 new metaids.
         */
        void setMetaidBase(const std::string &metaidBase);

        /**
         * @brief getter for the current xml type identification variable.
         * @return OmexMetaType
         * @details This should be set automatically in the Editor constructor
         */
        [[nodiscard]] OmexMetaXmlType getType() const;

        /**
         * @brief setter for the current xml type identification variable.
         * @return void
         * @details This should be set automatically in the Editor constructor
         */
        void setType(OmexMetaXmlType type);

        /**
         * @brief create a new PhysicalEntity object.
         * @details PhysicalEntity objects should only be instantiated
         * via the Editor because this enables the passing of necessary information
         * behind the scenes, rather than needing to be provided by the user.
         */
        PhysicalEntity newPhysicalEntity();

        /**
         * @brief create a new EnergyDiff object.
         * @details EnergyDiff objects should only be instantiated
         * via the Editor because this enables the passing of necessary information
         * behind the scenes, rather than needing to be provided by the user.
         */
        EnergyDiff newEnergyDiff();

        /**
         * @brief create a new PhysicalProcess object.
         * @details PhysicalProcess objects should only be instantiated
         * via the Editor because this enables the passing of necessary information
         * behind the scenes, rather than needing to be provided by the user.
         */
        PhysicalProcess newPhysicalProcess();

        /**
         * @brief create a new PersonalInformation object.
         * @details PersonalInformation objects should only be instantiated
         * via the Editor because this enables the passing of necessary information
         * behind the scenes, rather than needing to be provided by the user.
         */
        PersonalInformation newPersonalInformation();

        /**
         * @brief like addSingleAnnotation
         */
        void addSingleAnnotationNoValidation(SingularAnnotation &singularAnnotation);

        OMEXMETA_DEPRECATED void addCompositeAnnotation2(PropertyBearer *phenomenonPtr);

        void addTriples(Triples &triples);

        void removePropertyBearer(PropertyBearer *physicalPhenomenon) const;

        /**
         * @brief get the current value of archive_uri_
         */
        [[nodiscard]] std::string getArchiveUri() const;

        /**
         * @brief get the current value of local_uri_
         */
        std::string getLocalUri() const;

        /**
         * @brief get the current value of model_uri_
         */
        [[nodiscard]] std::string getModelUri() const;

        /**
         * @brief get the current value of the uri used to
         * annotate model level annotations
         */
        std::string getModelLevelAnnotationUri() const;

        /**
         * @brief get the current value of archive_uri_
         */
        [[nodiscard]] std::string getRepositoryUri() const;

        /**
         * @brief instantiate a LibrdfNode that is prefixed with the current local_uri
         *
         */
        [[nodiscard]] LibrdfNode createNodeWithModelUri(const std::string &string) const;

        /**
         * @brief add the "creator" model level annotation
         * @param an orcid_id as string
         */
        Editor &addCreator(std::string orcid_id);

        /**
         * @brief add the "curator" model level annotation
         * @param an orcid_id as string
         */
        Editor &addContributor(std::string orcid_id);

        /**
         * @brief add the "taxon id" model level annotation
         * @param an taxon_id as string
         */
        Editor &addTaxon(const std::string &taxon_id);

        /**
         * @brief add the "pubmed id" model level annotation
         * @param a pubmed id as string
         */
        Editor &addPubmed(const std::string &pubmedid);

        /**
         * @brief add the "description" model level annotation
         * @param a description of the model as string
         */
        Editor &addDescription(const std::string &date);

        /**
         * @brief add the "date created" model level annotation
         * @param The date that the model was created
         */
        Editor &addDateCreated(const std::string &date);

        /**
         * @brief create a new singular annotation object with metaid
         * @param metaid the string to use in the "rdf:about" field or subject
         * @return a new SingularAnnotation object
         */
        SingularAnnotation newSingularAnnotation(std::string metaid) const;

        /**
         * @brief add the "parent model" model level annotation
         * @param The biomodels id for the model in which this model was derived from
         */
        Editor &addParentModel(const std::string &biomod_id);

        /**
         * @brief create a new SingularAnnotation object
         * @return A SingularAnnotation object
         * @details a SingularAnnotation is a typedefed Triple object.
         */
        SingularAnnotation newSingularAnnotation() const;

        /**
         * @brief instantiate a new PhysicalProperty instance and return
         */
        PhysicalProperty newPhysicalProperty();

        /**
         * @brief instantiate a pointer to a new PhysicalProperty instance and return
         * @details the caller is responsible for deleting the returned PhysicalProperty
         * using deletePhysicalProperty
         */
        PhysicalProperty *newPhysicalPropertyPtr();

        /**
         * @brief get a reference to the current UriHandler
         */
        UriHandler &getUriHandler() const;

        /**
         * @brief remove all <annotation> elements from the xml
         * associated with this Editor instance.
         *
         * @param annotationElementName the name of the element that contains the annotations.
         * The default is "annotation" since sbml embedded annotations are all contained within
         * an <annotation> element. Other languages
         *
         * @details returns a copy of xml without any annotations (i.e. CellML) may not
         * follow this convention and have the option of changing check element contains
         * the annotations. Users should be warned that no verification is in place
         * to prevent you from stripping away arbitrary elements with this method - all elements
         * named @param annotationElementName will be removed from this xml document, regardless
         * of content.
         */
        std::string stripAnnotations(const std::string& annotationElementName = "annotation");

    private:
        std::string xml_;
        std::vector<std::string> metaids_;
        LibrdfModel &model_;
        bool create_ids_ = false;
        std::unordered_map<std::string, std::string> &namespaces_;
        bool generate_new_metaids_;
        bool sbml_semantic_extraction_;
        std::string metaid_base_ = "#OmexMetaId"; // maybe unused?
        OmexMetaXmlType type_;
        OmexMetaXmlPtr omexMetaXmlPtr_;

        UriHandler &uriHandler_;

        void extractNamespacesFromTriplesVector(PropertyBearer *pp);
    };

}// namespace omexmeta

#endif//LIBOMEXMETA_EDITOR_H
