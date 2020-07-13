//
// Created by Ciaran on 4/15/2020.
//

#include "omexmeta/Editor.h"

#include <utility>
#include "filesystem"

namespace omexmeta {
//    Editor::Editor(const std::string &xml, SemsimXmlType type, bool create_ids,
//                   const LibrdfModel &model, NamespaceMap &nsmap)
//            : model_(model), namespaces_(nsmap), create_ids_(create_ids) {
//        XmlAssistantPtr xmlAssistantPtr = SemsimXmlAssistantFactory::generate(xml, type);
//        std::pair<std::string, std::vector<std::string>> xml_and_metaids = xmlAssistantPtr->addMetaIds();
//        xml_ = xml_and_metaids.first;
//        //todo create a structure mapping metaids to more useful information for the user.
//        metaids_ = xml_and_metaids.second;
//    }

    Editor::Editor(const std::string &xml, SemsimXmlType type, bool create_ids,
                   const LibrdfModel &model, NamespaceMap &nsmap,
                   const std::string& repository_uri,
                   const std::string& archive_uri,
                   const std::string& model_uri,
                   const std::string& local_uri)
            : model_(model), create_ids_(create_ids), namespaces_(nsmap),
              repository_uri_(repository_uri),
              archive_uri_(archive_uri),
              model_uri_(model_uri),
              local_uri_(local_uri) {
        XmlAssistantPtr xmlAssistantPtr = SemsimXmlAssistantFactory::generate(xml, type);
        std::pair<std::string, std::vector<std::string>> xml_and_metaids = xmlAssistantPtr->addMetaIds();
        xml_ = xml_and_metaids.first;
        metaids_ = xml_and_metaids.second;
    }

    int Editor::size() const {
        return model_.size();
    }

    const std::string &Editor::getXml() const {
        return xml_;
    }

    const std::vector<std::string> &Editor::getMetaids() const {
        return metaids_;
    }

    const std::unordered_map<std::string, std::string> &Editor::getNamespaces() const {
        return namespaces_;
    }

    void Editor::setNamespaces(const std::unordered_map<std::string, std::string> &namespaces) {
        namespaces_ = namespaces;
    }

    librdf_model *Editor::getModel() const {
        return model_.get();
    }

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
            err << "std::invalid_argument(): metaid \"" << metaid << "\" is not equal to or a substring ";
            err << "of any of your metaids. ";
            err << "These are your available metaids: ";
            for (auto &it: metaids_) {
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

    void Editor::addSingleAnnotation(
            Subject subject, const PredicatePtr &predicate_ptr,
            const Resource &resource) {
        if (!predicate_ptr) {
            std::ostringstream err;
            err << __FILE__ << ":" << __LINE__ << ":PredicatePtr argument is null" << std::endl;
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

    void Editor::addSingleAnnotationNoValidation(SingularAnnotation &singularAnnotation) {
        addNamespaceFromAnnotation(singularAnnotation.getPredicateStr());
        model_.addStatement(singularAnnotation);
    }

    void Editor::addNamespaceFromAnnotation(const std::string &predicate_string) {
        // store namespaces for later
        std::string ns = OmexMetaUtils::getNamespaceFromUri(predicate_string);
        if (Predicate::namespaceKnown(ns)) {
            namespaces_[ns] = Predicate::namespaceMap()[ns];
        };
    }

    void Editor::addCompositeAnnotation(PhysicalPhenomenon *phenomenonPtr) {
        /*
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
            // add to the model
            model_.addStatement(triple.getStatement());
            // remember to free it.
            triple.freeStatement();
        }
    }

    void Editor::addCompositeAnnotation2(PhysicalPhenomenon *phenomenonPtr) {
        Triples triples = phenomenonPtr->toTriples();
        for (auto &triple: triples) {
            // collect the namespace from the triple
            addNamespaceFromAnnotation(triple.getPredicateStr());
            addSingleAnnotationNoValidation(triple);
        }
        triples.freeTriples();
    }

    void Editor::addTriples(Triples &triples) {
        for (auto &triple: triples) {
            // collect the namespace from the triple
            addNamespaceFromAnnotation(triple.getPredicateStr());
            addSingleAnnotationNoValidation(triple);
        }
    }

    void Editor::addPhysicalEntity(PhysicalEntity &physicalEntity) {
        if (physicalEntity.getAbout().empty()) {
            throw NullPointerException(
                    "NullPointerException: Editor::addPhysicalEntity() physicalEntity::subject_ (i.e. about) node is empty");
        }
        /*
         * Because we now want to use @prefix local for the
         * about section, we need to inject it here,
         * if not already formatted properly.
         */
        physicalEntity.setAbout(
                OmexMetaUtils::addLocalPrefixToMetaid(physicalEntity.getAbout(), getLocalUri())
        );
        checkValidMetaid(physicalEntity.getAbout());
        addCompositeAnnotation((PhysicalPhenomenon *) &physicalEntity);
    }

    void Editor::addPhysicalProcess(PhysicalProcess &physicalProcess) {
        if (physicalProcess.getAbout().empty()) {
            throw NullPointerException(
                    "NullPointerException: Editor::addPhysicalProcess() PhysicalProcess::subject_ (i.e. about) node is empty");
        }
        checkValidMetaid(physicalProcess.getAbout());
        /*
         * Because we now want to use @prefix local for the
         * about section, we need to inject it here,
         * if not already formatted properly.
         */
        physicalProcess.setAbout(
                OmexMetaUtils::addLocalPrefixToMetaid(physicalProcess.getAbout(), getLocalUri())
        );
        addCompositeAnnotation((PhysicalPhenomenon *) &physicalProcess);

    }

    void Editor::addPhysicalForce(PhysicalForce &physicalForce) {
        if (physicalForce.getAbout().empty()) {
            throw NullPointerException(
                    "NullPointerException: Editor::addPhysicalForce() PhysicalForce::subject_ (i.e. about) node is empty");
        }
        checkValidMetaid(physicalForce.getAbout());
        /*
         * Because we now want to use @prefix local for the
         * about section, we need to inject it here,
         * if not already formatted properly.
         */
        physicalForce.setAbout(
                OmexMetaUtils::addLocalPrefixToMetaid(physicalForce.getAbout(), getLocalUri())
        );
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
        // give the triples object back so we can reuse it in a potential call to delete
        personalInformation->setTriples(std::move(triples));
    }

    void Editor::removeSingleAnnotation(const SingularAnnotation &singularAnnotation) const {
        librdf_statement *stmt = singularAnnotation.getStatement();
        model_.removeStatement(stmt);
    }

    void Editor::removePhysicalPhenomenon(PhysicalPhenomenon *physicalPhenomenon) const {
        Triples triples = physicalPhenomenon->toTriples();
        while (!triples.isEmpty()) {
            Triple triple = triples.pop();
            model_.removeStatement(triple.getStatement());
            triple.freeTriple();
        }
    }

    void Editor::removePhysicalEntity(PhysicalEntity &physicalEntity) const {
        removePhysicalPhenomenon(&physicalEntity);
    }

    void Editor::removePersonalInformation(PersonalInformation *information) const {
        Triples triples = information->getTriples();
        while (!triples.isEmpty()) {
            Triple triple = triples.pop();
            model_.removeStatement(triple.getStatement());
//            triple.freeTriple();
        }
    }

    void Editor::removePhysicalForce(PhysicalForce &physicalForce) const {
        removePhysicalPhenomenon(&physicalForce);
    }

    void Editor::removePhysicalProcess(PhysicalProcess &physicalProcess) const {
        removePhysicalPhenomenon(&physicalProcess);
    }

    PhysicalEntity Editor::newPhysicalEntity() {
        return PhysicalEntity(model_.get(), getLocalUri());
    }

    PhysicalForce Editor::newPhysicalForce() {
        return PhysicalForce(model_.get(), getLocalUri());
    }

    PhysicalProcess Editor::newPhysicalProcess() {
        return PhysicalProcess(model_.get(), getLocalUri());
    }

    PersonalInformation Editor::newPersonalInformation() {
        return PersonalInformation(model_.get(), getLocalUri(), getModelUri());
    }

    void Editor::addCreator(std::string orcid_id) {
        std::string orcid_namespace = "https://orchid.org/";
        if (orcid_id.rfind(orcid_namespace, 0) != 0) {
            orcid_id = orcid_namespace + orcid_id;
        }
        Triple triple(
                LibrdfNode::fromUriString(getModelUri()).get(),
                PredicateFactory("dc", "creator")->getNode(),
                LibrdfNode::fromUriString(orcid_id).get()
        );
        model_.addStatement(triple);
        triple.freeTriple();
    }

    void Editor::addCurator(std::string orcid_id) {
        std::string orcid_namespace = "https://orchid.org/";
        if (orcid_id.rfind(orcid_namespace, 0) != 0) {
            orcid_id = orcid_namespace + orcid_id;
        }
        Triple triple(
                LibrdfNode::fromUriString(getArchiveUri()).get(),
                PredicateFactory("dc", "creator")->getNode(),
                LibrdfNode::fromUriString(orcid_id).get()
        );
        model_.addStatement(triple);
        triple.freeTriple();
    }

    void Editor::addDateCreated(const std::string &date) {
        Triple triple(
                LibrdfNode::fromUriString(getModelUri()).get(),
                PredicateFactory("dc", "created")->getNode(),
                LibrdfNode::fromLiteral(date).get()
        );
        model_.addStatement(triple);
        triple.freeTriple();
    }

    void Editor::addDescription(const std::string &date) {
        Triple triple(
                LibrdfNode::fromUriString(getModelUri()).get(),
                PredicateFactory("dc", "description")->getNode(),
                LibrdfNode::fromLiteral(date).get()
        );
        model_.addStatement(triple);
        triple.freeTriple();
    }

    void Editor::addPubmed(const std::string &pubmedid) {
        Triple triple(
                LibrdfNode::fromUriString(getModelUri()).get(),
                PredicateFactory("bqmodel", "isDescribedBy")->getNode(),
                LibrdfNode::fromUriString("pubmed:" + pubmedid).get()
        );
        model_.addStatement(triple);
        triple.freeTriple();
    }

    void Editor::addParentModel(const std::string &biomod_id) {
        Triple triple(
                LibrdfNode::fromUriString(getModelUri()).get(),
                PredicateFactory("bqmodel", "isDerivedFrom")->getNode(),
                LibrdfNode::fromUriString("biomod:" + biomod_id).get()
        );
        model_.addStatement(triple);
        triple.freeTriple();
    }

    void Editor::addTaxon(const std::string &taxon_id) {
        Triple triple(
                LibrdfNode::fromUriString(getModelUri()).get(),
                PredicateFactory("bqbiol", "hasTaxon")->getNode(),
                LibrdfNode::fromUriString("NCBI_Taxon:" + taxon_id).get()
        );
        model_.addStatement(triple);
        triple.freeTriple();
    }

    std::string Editor::getLocalUri() const {
        return local_uri_;
    }

    std::string Editor::getModelUri() const {
        return model_uri_;
    }

    std::string Editor::getArchiveUri() const {
        return archive_uri_;
    }

    std::string Editor::getRepositoryUri() const {
        return repository_uri_;
    }

    LibrdfNode Editor::createNodeWithLocalUri(const std::string &string) const {
        if (getLocalUri().empty()) {
            throw std::logic_error("std::logic_error: Editor::createNodeWithLocalUri: "
                                   "Trying to create a node with a uri relative to "
                                   "the local namespace without previously setting the local "
                                   "namespace. Please use the setLocalUri() method. ");
        }
        return LibrdfNode::fromUriString(getLocalUri() + string);
    }

    SingularAnnotation Editor::newSingularAnnotation(std::string metaid) const {
        SingularAnnotation singularAnnotation;
        singularAnnotation.setAbout(OmexMetaUtils::addLocalPrefixToMetaid(std::move(metaid), getLocalUri()));
        return singularAnnotation;
    }


}








