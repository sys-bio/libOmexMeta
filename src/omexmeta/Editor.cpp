//
// Created by Ciaran on 4/15/2020.
//

#include "omexmeta/Editor.h"
#include <filesystem>
#include <utility>

namespace omexmeta {

    Editor::Editor(std::string xml_or_file, bool create_ids,
                   LibrdfModel &model, NamespaceMap &ns_map, UriHandler &uriHandler,
                   bool generate_new_metaids, bool sbml_semantic_extraction)
        : xml_(std::move(xml_or_file)), create_ids_(create_ids), model_(model), namespaces_(ns_map),
          generate_new_metaids_(generate_new_metaids),
          sbml_semantic_extraction_(sbml_semantic_extraction),
          uriHandler_(uriHandler) {
        // sometimes in the python api users can accidentally start the sbml
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
        // identiy the type of xml that we have parsed
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

        // instantiate an instance of OmexMetaXml, depending on what type we have
        omexMetaXmlPtr_ = OmexMetaXmlFactory::generate(xml_, getType(), generate_new_metaids, "OmexMetaId", 4);

        // add metaids if we want to
        std::pair<std::string, std::vector<std::string>> xml_and_metaids = omexMetaXmlPtr_->addMetaIds();

        // todo this xml_ should be replaced with omexMetaXml(Ptr)
        xml_ = xml_and_metaids.first;
        metaids_ = xml_and_metaids.second;

        // collect metaid of first model element in the model. This is default for model level annotations
        uriHandler.setModelMetaid(omexMetaXmlPtr_->getDefaultModelMetaid());

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

    const std::unordered_map<std::string, std::string> &Editor::getNamespaces() const {
        return namespaces_;
    }

    void Editor::setNamespaces(
            const std::unordered_map<std::string, std::string> &namespaces) {
        namespaces_ = namespaces;
    }

    LibrdfModel& Editor::getModel() const { return model_; }

    void Editor::checkValidMetaid(const std::string &metaid) {
        // metaid's containing local uri's are valid metaids.
        if (OmexMetaUtils::startsWith(metaid, getLocalUri())) {
            return;
        }

        // if metaid is an empty string, a local uri will be generated automatically
        if (metaid.empty()) {
            return;
        }

        // Check if metaid is a substring of one of the metaids.
        // throw error if not
        bool found = false;
        for (auto &it : metaids_) {
            if (OmexMetaUtils::startsWith(metaid, "http")) {
                // if we are dealing with a full uri, split off the end (after fragment #)
                if (!OmexMetaUtils::isSubString(metaid, "#")) {
                    // if "#" is not in the metaid uri, raise error
                    throw std::invalid_argument("Editor::checkValidMetaid: metaid "
                                                "\"" +
                                                metaid + "\" was given but it does not "
                                                         "contain a fragment portion "
                                                         "(i.e. the bit after \"#\"). ");
                }
                // now that we've checked we have a "#" in the uri, we can split on it
                std::vector<std::string> split_string = OmexMetaUtils::splitStringBy(metaid, '#');

                // this should always be true
                assert(split_string.size() == 2);

                // we now check that the fragment of the full uri == metaid
                if (it == split_string[1]) {
                    found = true;
                    break;
                }

            } else {
                // if we are not dealing with a full uri (starts with http)
                // we can just compare against the metaid
                if (metaid == it) {
                    found = true;
                    break;
                }
            }
        }

        if (!found) {
            std::ostringstream err;
            err << "std::invalid_argument(): metaid \"" << metaid
                << "\" is not  ";
            err << "one of your metaids. ";
            err << "These are your available metaids: ";
            for (auto &it : metaids_) {
                err << it << ", ";
            }
            throw std::invalid_argument(err.str());
        }
    }

    void Editor::extractNamespacesFromTriplesVector(PropertyBearer *pp) {
        // here we create our own localized Triples object
        // and deplete it during the while loop. This
        // is preferable to passing in a Triples object
        // as argument because that would take copies and
        // mess with cleaning up the triples later.
        Triples triples = pp->toTriples();
        for (auto &triple : triples) {
            addNamespaceFromAnnotation(triple.getPredicateNode().str());
        }
    }

    void Editor::addNamespace(const std::string &ns, std::string prefix) {
        namespaces_[ns] = std::move(prefix);
    }

    void Editor::addSingleAnnotation(LibrdfNode subject,
                                     const PredicatePtr &predicate_ptr,
                                     const LibrdfNode &resource) {
        if (!predicate_ptr) {
            std::ostringstream err;
            err << __FILE__ << ":" << __LINE__ << ":PredicatePtr argument is null"
                << std::endl;
            throw NullPointerException(err.str());
        }
        checkValidMetaid(subject.str());
        Triple triple(uriHandler_, subject, predicate_ptr->getNode(), resource);
        model_.addStatement(triple);
        namespaces_[predicate_ptr->getNamespace()] = predicate_ptr->getPrefix();
    }

    void Editor::addSingleAnnotation(SingularAnnotation &singularAnnotation) {
        checkValidMetaid(singularAnnotation.getSubjectNode().str());
        addNamespaceFromAnnotation(singularAnnotation.getPredicateNode().str());
        model_.addStatement(singularAnnotation);
    }

    void Editor::addSingleAnnotationNoValidation(
            SingularAnnotation &singularAnnotation) {
        addNamespaceFromAnnotation(singularAnnotation.getPredicateNode().str());
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

    void Editor::addCompositeAnnotation(PropertyBearer *phenomenonPtr) {
        /**
        * Implementation note: This method generates triples on the
        * fly and then frees. This was implemented this way as it helped avoid
        * memory issues but perhaps a better implementation would be similar to
        * that in the PersonalInformation class.
        */
        Triples triples = phenomenonPtr->toTriples();
        for (auto &triple : triples) {

            // collect the namespace from the triple
            addNamespaceFromAnnotation(triple.getPredicateNode().str());

            //todo consider whether to also call AddNamespaceFromAnnotation(triple.getResourseStr())

            // add to the model
            model_.addStatement(triple);
        }
    }

    void Editor::addCompositeAnnotation2(PropertyBearer *phenomenonPtr) {
        Triples triples = phenomenonPtr->toTriples();
        for (auto &triple : triples) {
            // collect the namespace from the triple
            addNamespaceFromAnnotation(triple.getPredicateNode().str());
            addSingleAnnotationNoValidation(triple);
        }
    }

    void Editor::addTriples(Triples &triples) {
        for (auto &triple : triples) {
            // collect the namespace from the triple
            addNamespaceFromAnnotation(triple.getPredicateNode().str());
            addSingleAnnotationNoValidation(triple);
        }
    }

    void Editor::addPhysicalProperty(PhysicalProperty &physicalProperty) {
        Triples triples = physicalProperty.toTriples();
        for (auto &triple : triples) {
            // collect the namespace from the triple
            addNamespaceFromAnnotation(triple.getPredicateNode().str());
            addSingleAnnotationNoValidation(triple);
        }
    }

    void Editor::addPhysicalEntity(PhysicalEntity &physicalEntity) {
        checkValidMetaid(physicalEntity.getAbout());
        addCompositeAnnotation((PropertyBearer *) &physicalEntity);
    }

    void Editor::addPhysicalProcess(PhysicalProcess &physicalProcess) {
        checkValidMetaid(physicalProcess.getAbout());
        addCompositeAnnotation((PropertyBearer *) &physicalProcess);
    }


    void Editor::addEnergyDiff(EnergyDiff &ediff) {
        checkValidMetaid(ediff.getAbout());
        addCompositeAnnotation((PropertyBearer *) &ediff);
    }

    void Editor::addPersonalInformation(PersonalInformation *personalInformation) {
        // take the triples object - this is not a copy

        Triples triples = personalInformation->getTriples();
        for (auto &triple : triples) {
            // collect the namespace from the triple
            addNamespaceFromAnnotation(triple.getPredicateNode().str());
            // add to the model
            model_.addStatement(triple);
        }
        // give the triples object back so we can reuse it in a potential call to
        // delete
        personalInformation->setTriples(std::move(triples));
    }

    void Editor::removeSingleAnnotation(
            const SingularAnnotation &singularAnnotation) const {
        model_.removeStatement(singularAnnotation);
    }

    void Editor::removePropertyBearer(PropertyBearer *physicalPhenomenon) const {
        Triples triples = physicalPhenomenon->toTriples();
        for (auto &triple : triples) {
            model_.removeStatement(triple);
        }
    }

    void Editor::removePhysicalEntity(PhysicalEntity &physicalEntity) const {
        removePropertyBearer(&physicalEntity);
    }

    void Editor::removePersonalInformation(PersonalInformation *information) const {
        Triples triples = information->getTriples();
        for (auto &triple : triples) {
            model_.removeStatement(triple);
        }
    }

    void Editor::removeEnergyDiff(EnergyDiff &physicalForce) const {
        removePropertyBearer(&physicalForce);
    }

    void Editor::removePhysicalProcess(PhysicalProcess &physicalProcess) const {
        removePropertyBearer(&physicalProcess);
    }

    PhysicalProperty Editor::newPhysicalProperty() {
        return PhysicalProperty(model_, uriHandler_);
    }

    PhysicalProperty *Editor::newPhysicalPropertyPtr() {
        auto *property = new PhysicalProperty(model_, uriHandler_);
        return property;
    }

    PhysicalEntity Editor::newPhysicalEntity() {
        return PhysicalEntity(model_, uriHandler_);
    }

    EnergyDiff Editor::newEnergyDiff() {
        return EnergyDiff(model_, uriHandler_);
    }

    PhysicalProcess Editor::newPhysicalProcess() {
        return PhysicalProcess(model_, uriHandler_);
    }

    PersonalInformation Editor::newPersonalInformation() {
        // todo consider whether local_uri argument is needed
        return PersonalInformation(model_, uriHandler_);
    }

    Editor &Editor::addCreator(std::string orcid_id) {
        std::string orcid_namespace = "https://orcid.org/";
        if (orcid_id.rfind(orcid_namespace, 0) != 0) {
            orcid_id = orcid_namespace + orcid_id;
        }
        Triple triple(uriHandler_, LibrdfNode::fromUriString(getModelLevelAnnotationUri()),
                      PredicateFactory("dc", "creator")->getNode(),
                      LibrdfNode::fromUriString(orcid_id));
        model_.addStatement(triple);
        addNamespace(Predicate::namespaceMap()["dc"], "dc");
        return *this;
    }

    Editor &Editor::addContributor(std::string orcid_id) {
        std::string orcid_namespace = "https://orcid.org/";
        if (orcid_id.rfind(orcid_namespace, 0) != 0) {
            orcid_id = orcid_namespace + orcid_id;
        }
        Triple triple(uriHandler_, LibrdfNode::fromUriString(getLocalUri()),
                      PredicateFactory("dc", "contributor")->getNode(),
                      LibrdfNode::fromUriString(orcid_id));
        model_.addStatement(triple);
        addNamespace(Predicate::namespaceMap()["dc"], "dc");
        return *this;
    }

    Editor &Editor::addDateCreated(const std::string &date) {
        //        LibrdfNode anon = LibrdfNode::fromBlank("");
        auto ptr = PredicateFactory("dc", "W3CDTF");
        std::string w3 = ptr->str();
        Triple triple1(
                uriHandler_, LibrdfNode::fromUriString(getModelLevelAnnotationUri()),
                PredicateFactory("dc", "created")->getNode(),
                LibrdfNode::fromLiteral(date, w3));
        model_.addStatement(triple1);
        addNamespace(Predicate::namespaceMap()["dc"], "dc");
        return *this;
    }

    Editor &Editor::addDescription(const std::string &date) {
        Triple triple(uriHandler_, LibrdfNode::fromUriString(getModelLevelAnnotationUri()),
                      PredicateFactory("dc", "description")->getNode(),
                      LibrdfNode::fromLiteral(date));
        model_.addStatement(triple);
        addNamespace(Predicate::namespaceMap()["dc"], "dc");
        return *this;
    }

    Editor &Editor::addPubmed(const std::string &pubmedid) {
        Triple triple(uriHandler_, LibrdfNode::fromUriString(getModelLevelAnnotationUri()),
                      PredicateFactory("bqmodel", "isDescribedBy")->getNode(),
                      LibrdfNode::fromUriString("pubmed:" + pubmedid));
        model_.addStatement(triple);
        addNamespace(Predicate::namespaceMap()["bqmodel"], "bqmodel");
        addNamespace(Predicate::namespaceMap()["pubmed"], "pubmed");
        return *this;
    }

    Editor &Editor::addParentModel(const std::string &biomod_id) {
        Triple triple(uriHandler_, LibrdfNode::fromUriString(getModelLevelAnnotationUri()),
                      PredicateFactory("bqmodel", "isDerivedFrom")->getNode(),
                      LibrdfNode::fromUriString("biomodels.db:" + biomod_id));
        model_.addStatement(triple);
        addNamespace(Predicate::namespaceMap()["bqmodel"], "bqmodel");
        addNamespace(Predicate::namespaceMap()["biomod"], "biomod");
        return *this;
    }

    Editor &Editor::addTaxon(const std::string &taxon_id) {
        Triple triple(uriHandler_, LibrdfNode::fromUriString(getModelLevelAnnotationUri()),
                      PredicateFactory("bqbiol", "hasTaxon")->getNode(),
                      LibrdfNode::fromUriString("taxonomy:" + taxon_id));
        model_.addStatement(triple);
        addNamespace(Predicate::namespaceMap()["bqbiol"], "bqbiol");
        addNamespace(Predicate::namespaceMap()["NCBI_Taxon"], "NCBI_Taxon");

        return *this;
    }

    std::string Editor::getLocalUri() const { return uriHandler_.getLocalUri(); }

    std::string Editor::getModelUri() const { return uriHandler_.getModelUri(); }

    std::string Editor::getModelLevelAnnotationUri() const { return uriHandler_.getModelLevelAnnotationUri(); }

    std::string Editor::getArchiveUri() const { return uriHandler_.getArchiveUri(); }

    std::string Editor::getRepositoryUri() const { return uriHandler_.getRepositoryUri(); }

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
        SingularAnnotation singularAnnotation(uriHandler_);
        return singularAnnotation;
    }

    SingularAnnotation Editor::newSingularAnnotation(std::string metaid) const {
        SingularAnnotation singularAnnotation(uriHandler_);
        singularAnnotation.about(
                OmexMetaUtils::concatMetaIdAndUri(std::move(metaid), uriHandler_.getModelUri()));
        return singularAnnotation;
    }

    const std::string &Editor::getMetaidBase() const { return metaid_base_; }

    void Editor::setMetaidBase(const std::string &metaidBase) {
        metaid_base_ = metaidBase;
    }

    OmexMetaXmlType Editor::getType() const { return type_; }

    void Editor::setType(OmexMetaXmlType type) { type_ = type; }
    UriHandler &Editor::getUriHandler() const {
        return uriHandler_;
    }

    std::string Editor::stripAnnotations(const std::string &annotationElementName) {
        return omexMetaXmlPtr_->removeElement(annotationElementName);
    }


}// namespace omexmeta
