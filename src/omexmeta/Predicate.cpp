//
// Created by Ciaran on 4/17/2020.
//



#include "omexmeta/Predicate.h"

namespace omexmeta {

    Predicate::Predicate(const std::string &namespace_,
                         std::string term, std::string prefix)
            : namespace_(namespace_), term_(std::move(term)),
              prefix_(std::move(prefix)) {
        if (namespace_.back() == '/' || namespace_.back() == '#') {
            this->uri_ = namespace_ + term_;
        } else {
            this->uri_ = namespace_ + "/" + term_;
        }
        this->node_ = LibrdfNode::fromUriString(uri_).get();
    }

    Predicate::Predicate(librdf_node *node)
            : node_(node) {
        if (!node)
            throw RedlandNullPointerException(
                    "RedlandNullPointerException: Predicate::Predicate(librdf_node* node): node is null");
        // some logic for processing the uri in a node to automatically produce the fields we want.
        std::string val = LibrdfNode::str(node_);

        // split the uri by '/'
        std::vector<std::string> v = OmexMetaUtils::splitStringBy(val, '/');
        std::ostringstream os;
        // add protocol portion which should always be the first bit
        os << v[0] << "//";

        // add the middle portion to the stream.
        for (unsigned long i = 1; i < v.size() - 1; i++) {
            os << v[i] << "/"; // other parts of the url - up until the last bit
        }
        // When predicate ends in '#' we need different logic to when the predicate ends in '/'
        if (v[v.size() - 1].find('#') != std::string::npos) {
            // split last portion by '#' such as .../omexmeta#hasSourceParticipant
            std::vector<std::string> last_bit = OmexMetaUtils::splitStringBy(v[v.size() - 1], '#');
            if (last_bit.size() != 2) {
                throw std::logic_error("Predicate::Predicate(): For developers. Should never have more than two "
                                       "strings in this vector of strings");
            }
            // into omexmeta# and hasSourceParticipant
            os << last_bit[0] << "#";
            term_ = last_bit[1];
        } else {
            term_ = v[v.size() - 1];
        }

        namespace_ = os.str();

        prefix_ = Predicate::namespaceMap()[namespace_];
        if (prefix_.empty()) {
            prefix_ = "NotSet";
        }

        if (namespace_.back() == '/') {
            this->uri_ = namespace_ + term_;
        } else {
            this->uri_ = namespace_ + "/" + term_;
        }
        node_ = LibrdfNode::fromUriString(uri_).get();
    }

    const std::string &Predicate::getNamespace() const {
        return namespace_;
    }

    const std::string &Predicate::getTerm() const {
        return term_;
    }

    const std::string &Predicate::getPrefix() const {
        return prefix_;
    }

    const std::string &Predicate::getUri() const {
        return uri_;
    }

    bool Predicate::namespaceKnown(const std::string &ns) {
        bool known = false;
        for (const auto &it : Predicate::namespaceMap()) {
            if (ns == it.first) {
                known = true;
                break;
            }
        }
        return known;
    }

    std::unordered_map<std::string, std::string> Predicate::namespaceMap() {
        // todo I can't remember exactly why I chose to have prefix second and namespace first
        //  but it no longer seems like it makes sense. Swap these around and change the bits of
        //  code that use the namespaceMap so that first is second and second is first.
        return std::unordered_map<std::string, std::string>{
                {"http://xmlns.com/foaf/0.1/",                                    "foaf"},
                {"https://dublincore.org/specifications/dublin-core/dcmi-terms/", "dc"},
                {"https://orcid.org/",                                            "orcid"},
                {"http://biomodels.net/model-qualifiers/",                        "bqmodel"},
                {"http://biomodels.net/biology-qualifiers/",                      "bqbiol"},
                {"https:identifiers.org/pubmed/",                                 "pubmed"},
                {"http://identifiers.org/taxonomy/",                              "NCBI_Taxon"},
                {"<http://identifiers.org/biomodels.db/>",                        "biomod"},
                {"http://identifiers.org/CHEBI",                                  "chebi"},
                {"http://identifiers.org/uniprot/",                               "uniprot"},
                {"http://www.bhi.washington.edu/semsim#",                         "semsim"},
                {"http://identifiers.org/opb/",                                   "opb"},
                {"http://identifiers.org/fma/",                                   "fma"},
                {"http://purl.org/dc/terms/",                                     "dcterms"},
                {"http://OMEXlibrary.org/",                                     "OMEXlib"},

        };
    }

    std::string Predicate::str() {
        return uri_;
    }

    const std::vector<std::string> &Predicate::getValidTerms() const {
        return valid_terms_;
    }

    void Predicate::verify(std::vector<std::string> valid_terms, const std::string &term) {
        // when valled from the base Predicate class, accept anything
        if (valid_terms.size() == 1)
            if (valid_terms[0] == "All")
                return;
        // when called from any other class (which should have overridden valid_terms), we do validatation
        if (!(std::find(valid_terms.begin(), valid_terms.end(), term) != valid_terms.end())) {
            std::ostringstream os;
            os << __FILE__ << ":" << __LINE__ << ": Invalid term \"" << term << "\"given. Terms available for "
               << " include: ";
            for (auto &i : valid_terms) {
                os << i << ", ";
            }
            throw std::invalid_argument(os.str());
        }
    }

    librdf_node *Predicate::getNode() const {
        return node_;
    }

    void Predicate::setNode(librdf_node *node) {
        node_ = node;
    }

    void Predicate::freeNode() {
        LibrdfNode::freeNode(node_);
    }

    void Predicate::addSeenNamespaceToSerializer(librdf_world *world,
                                                 librdf_serializer *serializer, librdf_node *predicate) {
        // null checks
        if (!world)
            throw RedlandNullPointerException(
                    "RedlandNullPointerException: Predicate::addSeenNamespaceToSerializer: world is null");
        if (!serializer)
            throw RedlandNullPointerException(
                    "RedlandNullPointerException: Predicate::addSeenNamespaceToSerializer: serializer is null");
        if (!predicate)
            throw RedlandNullPointerException(
                    "RedlandNullPointerException: Predicate::addSeenNamespaceToSerializer: predicate is null");

        // grab the uri inside predicate node
        librdf_uri *pred_uri = librdf_node_get_uri(predicate);
        if (!pred_uri)
            throw RedlandNullPointerException(
                    "RedlandNullPointerException: Predicate::addSeenNamespaceToSerializer: uri is null. Maybe your predicate node isn't really a predicate node");

        // retrieve the namespace that we want to check
        unsigned char *s = librdf_uri_as_string(pred_uri);
        std::string pred_string((const char *) s);
        std::string pred_namespace = OmexMetaUtils::getNamespaceFromUri(pred_string);

        // get the namespacs to check against
        NamespaceMap ns_map = Predicate::namespaceMap();

        // if their namespace matches one we know, add it to the model
        for (auto &i : ns_map) {
            const std::string &ns = i.first;
            const std::string &prefix = i.second;
            if (pred_namespace == ns) {
                librdf_uri *u = librdf_new_uri(world, (const unsigned char *) ns.c_str());
                librdf_serializer_set_namespace(serializer, u, prefix.c_str());
                librdf_free_uri(u);
            }
        }
    }

    bool Predicate::operator==(const Predicate &rhs) const {
        return librdf_node_equals(node_, rhs.node_);
    }

    bool Predicate::operator!=(const Predicate &rhs) const {
        return !(rhs == *this);
    }


    BiomodelsBiologyQualifier::BiomodelsBiologyQualifier(const std::string &term) :
            Predicate("http://biomodels.net/biology-qualifiers/", term, "bqbiol") {
        /*
         * note: verify cannot be a virtual function
         * because I want to use it in the constructor.
         * Therefore, I made Predicate::verify static
         * to reduce code duplication.
         */
        verify();
    }

    void BiomodelsBiologyQualifier::verify() {
        Predicate::verify(valid_terms_, term_);
    }

    BiomodelsModelQualifier::BiomodelsModelQualifier(const std::string &term) :
            Predicate("http://biomodels.net/model-qualifiers/", term, "bqmodel") {
        verify();
    }

    void BiomodelsModelQualifier::verify() {
        Predicate::verify(valid_terms_, term_);
    }

    DCTerm::DCTerm(const std::string &term) :
            Predicate("http://purl.org/dc/terms/", term, "dcterms") {
        verify();
    }

    void DCTerm::verify() {
        Predicate::verify(valid_terms_, term_);
    }

    SemSim::SemSim(const std::string &term) :
            Predicate("http://www.bhi.washington.edu/semsim#", term, "semsim") {
        verify();
    }

    void SemSim::verify() {
        Predicate::verify(valid_terms_, term_);
    }

    Foaf::Foaf(const std::string &term) :
            Predicate("http://xmlns.com/foaf/0.1/", term, "foaf") {
        verify();
    }

    void Foaf::verify() {
        Predicate::verify(valid_terms_, term_);
    }

    /*
     * A factory function for creating PredicatePtr objects.
     */
    PredicatePtr PredicateFactory(std::string namespace_, const std::string &term) {

        std::vector<std::string> valid_namespace_strings = {
                "bqbiol",
                "bqmodel",
                "dc",
                "semsim",
                "foaf",
                "BiomodelsBiologyQualifier",
                "BiomodelsModelQualifier",
                "DCTerm"
        };

        if (std::find(valid_namespace_strings.begin(), valid_namespace_strings.end(), namespace_) ==
            valid_namespace_strings.end()) {
            std::ostringstream os;
            os << "Namespace \"" << namespace_ << "\" is not valid. These are ";
            os << " valid namespaces: ";
            for (auto &i : valid_namespace_strings) {
                os << i << ", ";
            }
            os << ". Note, they are not case sensitive. See also \"setPredicateFromUri\" ";
            os << "for using a predicate URI not built in.";
            os << std::endl;
            throw std::invalid_argument(os.str());
        }
        // ensure we only compare in lowercase
        std::for_each(namespace_.begin(), namespace_.end(), [](char &c) {
            c = (char)std::tolower(c);
        });

        PredicatePtr predicatePtr;
        if (namespace_ == "bqbiol" || namespace_ == "biomodelsbiologyqualifier") {
            predicatePtr = std::make_unique<BiomodelsBiologyQualifier>(
                    BiomodelsBiologyQualifier(term)
            );
        } else if (namespace_ == "bqmodel" || namespace_ == "biomodelsmodelqualifier") {
            predicatePtr = std::make_unique<BiomodelsModelQualifier>(
                    BiomodelsModelQualifier(term)
            );
        } else if (namespace_ == "dc" || namespace_ == "dcterms") {
            predicatePtr = std::make_unique<DCTerm>(
                    DCTerm(term)
            );
        } else if (namespace_ == "semsim") {
            predicatePtr = std::make_unique<SemSim>(
                    SemSim(term)
            );
        } else if (namespace_ == "foaf") {
            predicatePtr = std::make_unique<Foaf>(
                    Foaf(term)
            );
        } else {
            throw std::invalid_argument("Invalid term argument: PredicateFactory(): \"" + term + "\"");
        }
        return predicatePtr;
    }


}


