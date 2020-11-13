//
// Created by Ciaran on 4/15/2020.
//

#include "omexmeta/Editor.h"
#include <filesystem>
#include <utility>

namespace omexmeta {

    Editor::Editor(std::string xml_or_file, bool create_ids,
                   const LibrdfModel &model, NamespaceMap &ns_map,
                   bool generate_new_metaids, bool sbml_semantic_extraction,
                   const std::string &repository_uri,
                   const std::string &archive_uri, const std::string &model_uri,
                   const std::string &local_uri)
        : xml_(std::move(xml_or_file)), create_ids_(create_ids), model_(model), namespaces_(ns_map),
          generate_new_metaids_(generate_new_metaids),
          sbml_semantic_extraction_(sbml_semantic_extraction),
          repository_uri_(repository_uri), archive_uri_(archive_uri),
          model_uri_(model_uri), local_uri_(local_uri) {


        // sometimes in the python api users can accidently start the sbml
        // string with a new line character. Catch this and error.
        if (OmexMetaUtils::startsWith(xml_, "\n")) {
            throw std::invalid_argument("std::invalid_argument: Editor::Editor() "
                                        "xml input string starts with a newline character. "
                                        "Please remove the newline.");
        }
        // if xml_does not start with < and exists on disk, read it. The first condition is not included we get a filename too long error from exists
        if (xml_.find("<", 0) != 0) {// != 0 means not found
            if (std::filesystem::exists(xml_)) {
                // read from disk
                xml_ = OmexMetaUtils::readFromFile(xml_);
            }
        }
        MarkupIdentifier identifier(xml_);
        if (identifier.isSBML()) {
            type_ = OMEXMETA_TYPE_SBML;
        } else if (identifier.isCellML()) {
            type_ = OMEXMETA_TYPE_CELLML;
        } else {
            throw std::logic_error(
                    "Editor(): the string given as xml to editor was not recognized to"
                    " be either SBML or CellML. ");
        }
        assert(getType() != OMEXMETA_TYPE_NOTSET);// this should never happen
        XmlAssistantPtr xmlAssistantPtr = OmexMetaXmlAssistantFactory::generate(
                xml_, getType(), generate_new_metaids, "OmexMetaId", 4);
        std::pair<std::string, std::vector<std::string>> xml_and_metaids = xmlAssistantPtr->addMetaIds();
        xml_ = xml_and_metaids.first;
        metaids_ = xml_and_metaids.second;

        if (getType() == OMEXMETA_TYPE_SBML && sbml_semantic_extraction) {
            // with sbml models we extract some information directly from the sbml
            SBMLSemanticExtraction extraction(this);
            extraction.extractSpeciesCompartmentSemantics();
            extraction.extractProcessesFromReactions();
        }
    }

    int Editor::size() const { return model_.size(); }

    const std::string &Editor::getXml() const { return xml_; }

    const std::vector<std::string> &Editor::getMetaids() const { return metaids_; }

    const std::unordered_map<std::string, std::string> &
    Editor::getNamespaces() const {
        return namespaces_;
    }

    void Editor::setNamespaces(
            const std::unordered_map<std::string, std::string> &namespaces) {
        namespaces_ = namespaces;
    }

    librdf_model *Editor::getModel() const { return model_.get(); }

    void Editor::checkValidMetaid(const std::string &metaid) {
        // Check is metaid is a substring of one of the metaids.
        // throw error if not
        bool found = false;
        for (auto &it : metaids_) {
            if (metaid.find(it) != std::string::npos) {
                found = true;
                break;
            }
        }
        if (!found) {
            std::ostringstream err;
            err << "std::invalid_argument(): metaid \"" << metaid
                << "\" is not equal to or a substring ";
            err << "of any of your metaids. ";
            err << "These are your available metaids: ";
            for (auto &it : metaids_) {
                err << it << ", ";
            }
            throw std::invalid_argument(err.str());
        }
    }

    void Editor::extractNamespacesFromTriplesVector(PhysicalPhenomenon *pp) {
        // here we create our own localized Triples object
        // and deplete it during the while loop. This
        // is preferable to passing in a Triples object
        // as argument because that would take copies and
        // mess with cleaning up the triples later.
        Triples triples = pp->toTriples();
        while (!triples.isEmpty()) {
            Triple triple = triples.pop_front();
            addNamespaceFromAnnotation(triple.getPredicateStr());
            triple.freeStatement();
        }
    }

    void Editor::addNamespace(const std::string &ns, std::string prefix) {
        namespaces_[ns] = std::move(prefix);
    }

    void Editor::addSingleAnnotation(Subject subject,
                                     const PredicatePtr &predicate_ptr,
                                     const Resource &resource) {
        if (!predicate_ptr) {
            std::ostringstream err;
            err << __FILE__ << ":" << __LINE__ << ":PredicatePtr argument is null"
                << std::endl;
            throw NullPointerException(err.str());
        }
        checkValidMetaid(subject.str());
        Triple triple(subject, predicate_ptr, resource);
        model_.addStatement(triple);
        triple.freeStatement();
        namespaces_[predicate_ptr->getNamespace()] = predicate_ptr->getPrefix();
    }

    void Editor::addSingleAnnotation(SingularAnnotation &singularAnnotation) {
        checkValidMetaid(singularAnnotation.getSubjectStr());
        addNamespaceFromAnnotation(singularAnnotation.getPredicateStr());
        model_.addStatement(singularAnnotation);
    }

    void Editor::addSingleAnnotationNoValidation(
            SingularAnnotation &singularAnnotation) {
        addNamespaceFromAnnotation(singularAnnotation.getPredicateStr());
        model_.addStatement(singularAnnotation);
    }

    void Editor::addNamespaceFromAnnotation(const std::string &predicate_string) {
        // store namespaces for later
        NamespaceMap flippedNSMap;
        for (auto &it : Predicate::namespaceMap()) {
            flippedNSMap[it.second] = it.first;
        }
        std::string ns = OmexMetaUtils::getNamespaceFromUri(predicate_string);
        if (Predicate::namespaceKnown(ns)) {
            namespaces_[ns] = flippedNSMap[ns];
        };
    }

    void Editor::addCompositeAnnotation(PhysicalPhenomenon *phenomenonPtr) {
        /**
        * Implementation note: This method generates triples on the
        * fly and then frees. This was implemented this way as it helped avoid
        * memory issues but perhaps a better implementation would be similar to
        * that in the PersonalInformation class.
        */
        Triples triples = phenomenonPtr->toTriples();
        while (!triples.isEmpty()) {
            // remove a Triple off the front of triples
            Triple triple = triples.pop_front();

            // collect the namespace from the triple
            addNamespaceFromAnnotation(triple.getPredicateStr());

            //todo consider whether to also call AddNamespaceFromAnnotation(triple.getResourseStr())

            // add to the model
            model_.addStatement(triple.getStatement());
            // remember to free it.
            triple.freeStatement();
        }
    }

    void Editor::addCompositeAnnotation2(PhysicalPhenomenon *phenomenonPtr) {
        Triples triples = phenomenonPtr->toTriples();
        for (auto &triple : triples) {
            // collect the namespace from the triple
            addNamespaceFromAnnotation(triple.getPredicateStr());
            addSingleAnnotationNoValidation(triple);
        }
        triples.freeTriples();
    }

    void Editor::addTriples(Triples &triples) {
        for (auto &triple : triples) {
            // collect the namespace from the triple
            addNamespaceFromAnnotation(triple.getPredicateStr());
            addSingleAnnotationNoValidation(triple);
        }
    }

    void Editor::addPhysicalProperty(PhysicalProperty &physicalProperty) {
        Triples triples = physicalProperty.toTriples();
        for (auto &triple : triples) {
            // collect the namespace from the triple
            addNamespaceFromAnnotation(triple.getPredicateStr());
            addSingleAnnotationNoValidation(triple);
        }
        triples.freeTriples();
    }
    void Editor::addPhysicalEntity(PhysicalEntity &physicalEntity) {
        //        checkValidMetaid(physicalEntity.getAbout());
        addCompositeAnnotation((PhysicalPhenomenon *) &physicalEntity);
    }

    void Editor::addPhysicalProcess(PhysicalProcess &physicalProcess) {
        //        checkValidMetaid(physicalEntity.getAbout());
        addCompositeAnnotation((PhysicalPhenomenon *) &physicalProcess);
    }

    void Editor::addPhysicalForce(PhysicalForce &physicalForce) {
        //        checkValidMetaid(physicalEntity.getAbout());
        addCompositeAnnotation((PhysicalPhenomenon *) &physicalForce);
    }

    void Editor::addPersonalInformation(PersonalInformation *personalInformation) {
        // take the triples object - this is not a copy

        Triples triples = personalInformation->getTriples();
        for (auto &triple : triples) {
            // collect the namespace from the triple
            addNamespaceFromAnnotation(triple.getPredicateStr());
            // add to the model
            model_.addStatement(triple.getStatement());
            //             remember to free it.
            //            triple.freeStatement();
        }
        // give the triples object back so we can reuse it in a potential call to
        // delete
        personalInformation->setTriples(std::move(triples));
    }

    void Editor::removeSingleAnnotation(
            const SingularAnnotation &singularAnnotation) const {
        librdf_statement *stmt = singularAnnotation.getStatement();
        model_.removeStatement(stmt);
    }

    void Editor::removePhysicalPhenomenon(PhysicalPhenomenon *physicalPhenomenon) const {
        Triples triples = physicalPhenomenon->toTriples();
        while (!triples.isEmpty()) {
            Triple triple = triples.pop();
            model_.removeStatement(triple.getStatement());
        }
        //        triples.freeTriples();
    }

    void Editor::removePhysicalEntity(PhysicalEntity &physicalEntity) const {
        removePhysicalPhenomenon(&physicalEntity);
    }

    void Editor::removePersonalInformation(PersonalInformation *information) const {
        Triples triples = information->getTriples();
        while (!triples.isEmpty()) {
            Triple triple = triples.pop();
            model_.removeStatement(triple.getStatement());
            triple.freeTriple();
        }
    }

    void Editor::removePhysicalForce(PhysicalForce &physicalForce) const {
        removePhysicalPhenomenon(&physicalForce);
    }

    void Editor::removePhysicalProcess(PhysicalProcess &physicalProcess) const {
        removePhysicalPhenomenon(&physicalProcess);
    }

    PhysicalProperty Editor::newPhysicalProperty() {
        return PhysicalProperty(model_.get(), getModelUri(), getLocalUri());
    }

    PhysicalEntity Editor::newPhysicalEntity() {
        return PhysicalEntity(model_.get(), getModelUri(), getLocalUri());
    }

    PhysicalForce Editor::newPhysicalForce() {
        return PhysicalForce(model_.get(), getModelUri(), getLocalUri());
    }

    PhysicalProcess Editor::newPhysicalProcess() {
        return PhysicalProcess(model_.get(), getModelUri(), getLocalUri());
    }

    PersonalInformation Editor::newPersonalInformation() {
        // todo consider whether local_uri argument is needed
        return PersonalInformation(model_.get(), getModelUri(), getLocalUri());
    }

    Editor &Editor::addCreator(std::string orcid_id) {
        std::string orcid_namespace = "https://orchid.org/";
        if (orcid_id.rfind(orcid_namespace, 0) != 0) {
            orcid_id = orcid_namespace + orcid_id;
        }
        Triple triple(LibrdfNode::fromUriString(getModelUri()).get(),
                      PredicateFactory("dc", "creator")->getNode(),
                      LibrdfNode::fromUriString(orcid_id).get());
        model_.addStatement(triple);
        addNamespace(Predicate::namespaceMap()["dc"], "dc");
        triple.freeTriple();
        return *this;
    }

    Editor &Editor::addCurator(std::string orcid_id) {
        std::string orcid_namespace = "https://orchid.org/";
        if (orcid_id.rfind(orcid_namespace, 0) != 0) {
            orcid_id = orcid_namespace + orcid_id;
        }
        Triple triple(LibrdfNode::fromUriString(getLocalUri()).get(),
                      PredicateFactory("dc", "creator")->getNode(),
                      LibrdfNode::fromUriString(orcid_id).get());
        model_.addStatement(triple);
        addNamespace(Predicate::namespaceMap()["dc"], "dc");
        triple.freeTriple();
        return *this;
    }

    Editor &Editor::addDateCreated(const std::string &date) {
        LibrdfNode anon = LibrdfNode::fromBlank("");
        Triple triple1(LibrdfNode::fromUriString(getModelUri()).get(),
                       PredicateFactory("dc", "created")->getNode(),
                       anon.get());
        Triple triple2(anon.get(),
                       PredicateFactory("dc", "W3CDTF")->getNode(),
                       LibrdfNode::fromLiteral(date).get());
        model_.addStatement(triple1);
        model_.addStatement(triple2);
        addNamespace(Predicate::namespaceMap()["dc"], "dc");
        return *this;
    }

    Editor &Editor::addDescription(const std::string &date) {
        Triple triple(LibrdfNode::fromUriString(getModelUri()).get(),
                      PredicateFactory("dc", "description")->getNode(),
                      LibrdfNode::fromLiteral(date).get());
        model_.addStatement(triple);
        addNamespace(Predicate::namespaceMap()["dc"], "dc");
        triple.freeTriple();
        return *this;
    }

    Editor &Editor::addPubmed(const std::string &pubmedid) {
        Triple triple(LibrdfNode::fromUriString(getModelUri()).get(),
                      PredicateFactory("bqmodel", "isDescribedBy")->getNode(),
                      LibrdfNode::fromUriString("pubmed:" + pubmedid).get());
        model_.addStatement(triple);
        addNamespace(Predicate::namespaceMap()["bqmodel"], "bqmodel");
        addNamespace(Predicate::namespaceMap()["pubmed"], "pubmed");
        triple.freeTriple();
        return *this;
    }

    Editor &Editor::addParentModel(const std::string &biomod_id) {
        Triple triple(LibrdfNode::fromUriString(getModelUri()).get(),
                      PredicateFactory("bqmodel", "isDerivedFrom")->getNode(),
                      LibrdfNode::fromUriString("biomodels.db:" + biomod_id).get());
        model_.addStatement(triple);
        addNamespace(Predicate::namespaceMap()["bqmodel"], "bqmodel");
        addNamespace(Predicate::namespaceMap()["biomod"], "biomod");
        triple.freeTriple();
        return *this;
    }

    Editor &Editor::addTaxon(const std::string &taxon_id) {
        Triple triple(LibrdfNode::fromUriString(getModelUri()).get(),
                      PredicateFactory("bqbiol", "hasTaxon")->getNode(),
                      LibrdfNode::fromUriString("taxonomy:" + taxon_id).get());
        model_.addStatement(triple);
        addNamespace(Predicate::namespaceMap()["bqbiol"], "bqbiol");
        addNamespace(Predicate::namespaceMap()["NCBI_Taxon"], "NCBI_Taxon");

        triple.freeTriple();
        return *this;
    }

    std::string Editor::getLocalUri() const { return local_uri_; }

    std::string Editor::getModelUri() const { return model_uri_; }

    std::string Editor::getArchiveUri() const { return archive_uri_; }

    std::string Editor::getRepositoryUri() const { return repository_uri_; }

    LibrdfNode Editor::createNodeWithModelUri(const std::string &string) const {
        if (getModelUri().empty()) {
            throw std::logic_error(
                    "std::logic_error: Editor::createNodeWithModelUri: "
                    "Trying to create a node with a uri relative to "
                    "the model prefix without previously setting the model prefix "
                    "namespace. Please use the setModelUri() method. ");
        }
        std::string model_uri = getModelUri();
        if (OmexMetaUtils::endsWith(model_uri, "#")) {
            model_uri.erase(model_uri.end() - 1);
        }
        if (OmexMetaUtils::startsWith(string, "#")) {
            return LibrdfNode::fromUriString(model_uri + string);
        } else {
            return LibrdfNode::fromUriString(model_uri + "#" + string);
        }
    }

    SingularAnnotation Editor::newSingularAnnotation() const {
        SingularAnnotation singularAnnotation;
        singularAnnotation.setModelUri(getModelUri());
        singularAnnotation.setLocalUri(getLocalUri());
        return singularAnnotation;
    }

    SingularAnnotation Editor::newSingularAnnotation(std::string metaid) const {
        SingularAnnotation singularAnnotation;
        singularAnnotation.setModelUri(getModelUri());
        singularAnnotation.about(
                OmexMetaUtils::concatMetaIdAndUri(std::move(metaid), getModelUri()));
        return singularAnnotation;
    }

    const std::string &Editor::getMetaidBase() const { return metaid_base_; }

    void Editor::setMetaidBase(const std::string &metaidBase) {
        metaid_base_ = metaidBase;
    }

    OmexMetaXmlType Editor::getType() const { return type_; }

    void Editor::setType(OmexMetaXmlType type) { type_ = type; }

}// namespace omexmeta
