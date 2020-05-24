//
// Created by Ciaran on 4/17/2020.
//



#include "semsim/Predicate.h"

namespace semsim {

    Predicate::Predicate(const std::string &namespace_,
                         std::string term, std::string prefix)
            : namespace_(namespace_), term_(std::move(term)),
              prefix_(std::move(prefix)) {
        if (namespace_.back() == '/' || namespace_.back() == '#') {
            this->uri_ = namespace_ + term_;
        } else {
            this->uri_ = namespace_ + "/" + term_;
        }
        verify(valid_terms_, term_);
        this->uri_node_ = std::make_unique<LibrdfNode>(LibrdfNode::fromUriString(uri_));
    }

    Predicate::Predicate(LibrdfNode node)
            : uri_node_(std::make_unique<LibrdfNode>(std::move(node))) {
        // some logic for processing the uri in a node to automatically produce the fields we want.
        std::string val = uri_node_->str();

        // split the uri by '/'
        std::vector<std::string> v = SemsimUtils::splitStringBy(val, '/');
        std::ostringstream os;
        // add protocol portion which should always be the first bit
        os << v[0] << "//";

        // add the middle portion to the stream.
        for (unsigned long i = 1; i < v.size() - 1; i++) {
            os << v[i] << "/"; // other parts of the url - up until the last bit
        }
        // When predicate ends in '#' we need different logic to when the predicate ends in '/'
        if (v[v.size() - 1].find('#') != std::string::npos) {
            // split last portion by '#' such as .../semsim#hasSourceParticipant
            std::vector<std::string> last_bit = SemsimUtils::splitStringBy(v[v.size() - 1], '#');
            if (last_bit.size() != 2) {
                throw std::logic_error("Predicate::Predicate(): For developers. Should never have more than two "
                                       "strings in this vector of strings");
            }
            // into semsim# and hasSourceParticipant
            os << last_bit[0] << "#";
            term_ = last_bit[1];
        } else {
            term_ = v[v.size() - 1];
        }

        namespace_ = os.str();

        prefix_ = Predicate::prefix_map()[namespace_];
        if (prefix_.empty()) {
            prefix_ = "NotSet";
        }

        if (namespace_.back() == '/') {
            this->uri_ = namespace_ + term_;
        } else {
            this->uri_ = namespace_ + "/" + term_;
        }
        verify(valid_terms_, term_);
        uri_node_ = std::make_unique<LibrdfNode>(LibrdfNode::fromUriString(uri_));

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
        return (Predicate::prefix_map().find(ns) != Predicate::prefix_map().end());
    }

    std::unordered_map<std::string, std::string> Predicate::prefix_map() {
        return std::unordered_map<std::string, std::string>{
                {"http://purl.org/dc/terms/",                "dcterms"},
                {"http://biomodels.net/biology-qualifiers/", "bqbiol"},
                {"http://biomodels.net/model-qualifiers/",   "bqmodel"},
                {"http://www.bhi.washington.edu/semsim#",    "semsim"},
        };
    }


    std::string Predicate::str() {
        return uri_;
    }

    const std::vector<std::string> &Predicate::getValidTerms() const {
        return valid_terms_;
    }

    int Predicate::verify(std::vector<std::string> valid_terms, const std::string &term) {
        // when valled from the base Predicate class, accept anything
        if (valid_terms.size() == 1)
            if (valid_terms[0] == "All")
                return 0;
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
        return 0;
    }

    const std::unique_ptr<LibrdfNode> &Predicate::getNode() const {
        return uri_node_;
    }

    BiomodelsBiologyQualifier::BiomodelsBiologyQualifier(const std::string &term) :
            Predicate("http://biomodels.net/biology-qualifiers/", term, "bqbiol") {
        verify(valid_terms_, term_);

    }

    BiomodelsModelQualifier::BiomodelsModelQualifier(const std::string &term) :
            Predicate("http://biomodels.net/model-qualifiers/", term, "bqmodel") {
        verify(valid_terms_, term_);

    }

    DCTerm::DCTerm(const std::string &term) :
            Predicate("http://purl.org/dc/terms/", term, "dcterms") {
        verify(valid_terms_, term_);
    }

    SemSim::SemSim(const std::string &term) :
            Predicate("http://www.bhi.washington.edu/semsim#", term, "semsim") {
        verify(valid_terms_, term_);
    }


    /*
     * A factory function for creating PredicatePtr objects.
     */
    PredicatePtr PredicateFactory(std::string namespace_, const std::string &term) {

        std::vector<std::string> valid_namespace_strings = {
                "bqb",
                "bqm",
                "dc",
                "ss",
                "BiomodelsBiologyQualifier",
                "BiomodelsModelQualifier",
                "SemSim",
        };

        if (std::find(
                valid_namespace_strings.begin(),
                valid_namespace_strings.end(), namespace_
        ) == valid_namespace_strings.end()) {
            std::ostringstream os;
            os << "Namespace \"" << namespace_ << "\" is not valid. These are ";
            os << " valid namespaces: ";
            for (auto &i : valid_namespace_strings) {
                os << i << ", ";
            }
            os
                    << ". Note, they are not case sensitive. See also \"setPredicateFromUri\" for using a predicate URI not built in.";
            os << std::endl;
            throw std::invalid_argument(os.str());
        }
        // ensure we only compare in lowercase
        std::for_each(namespace_.begin(), namespace_.end(), [](char &c) {
            c = std::tolower(c);
        });


        PredicatePtr predicatePtr;
        if (namespace_ == "bqb" || namespace_ == "biomodelsbiologyqualifier") {
            predicatePtr = std::make_shared<BiomodelsBiologyQualifier>(
                    BiomodelsBiologyQualifier(term));
        } else if (namespace_ == "bqm" || namespace_ == "biomodelsmodelqualifier") {
            predicatePtr = std::make_shared<BiomodelsModelQualifier>(
                    BiomodelsModelQualifier(term));
        } else if (namespace_ == "dc" || namespace_ == "dcterms") {
            predicatePtr = std::make_shared<DCTerm>(
                    DCTerm(term));
        } else if (namespace_ == "ss" || namespace_ == "semsim") {
            predicatePtr = std::make_shared<SemSim>(
                    SemSim(term));
        };
        return predicatePtr;
    }
}

