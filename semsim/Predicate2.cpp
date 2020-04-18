//
// Created by Ciaran on 4/17/2020.
//

#include "Predicate2.h"

#include <cstring>
#include <utility>
#include <iostream>
#include "librdf.h"

namespace semsim {

    Predicate2::Predicate2(
            librdf_world *world,
            const std::string &namespace_,
            std::string term,
            std::string prefix)
            : world_(world), namespace_(namespace_), term_(std::move(term)),
              prefix_(std::move(prefix)) {
        if (namespace_.back() == '/') {
            uri_ = namespace_ + term_;
        } else {
            uri_ = namespace_ + "/" + term_;
        }
        RDFURINode node(world_, uri_);
        this->rdf_node_ptr_ = std::make_unique<RDFURINode>(node);
    }

    std::string Predicate2::str() {
        return uri_;
    }

    librdf_node *Predicate2::toRdfNode() {
        if (!rdf_node_ptr_) {
            std::ostringstream err;
            err << __FILE__ << ":" << __LINE__ << ": rdf_node_ptr_ has not been initialized" << std::endl;
            throw std::invalid_argument(err.str());
        }
        return rdf_node_ptr_->toRdfNode();
    }

    int Predicate2::verify(std::vector<std::string> valid_terms, std::string term) {
        // when valled from the base Predicate class, accept anything
        if (valid_terms.size() == 1)
            if (valid_terms[0] == "All")
                return 0;
        // when called from any other class (which should have overridden valid_terms_), we do validatation
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

    BiomodelsQualifiers::BiomodelsQualifiers(librdf_world *world, const std::string &term) {
        this->world_ = world;
        this->term_ = term;
        Predicate2::verify(valid_terms_, term);
        predicate = Predicate2(world_, namespace_, term_, prefix_);
    }

    std::string BiomodelsQualifiers::str() {
        return predicate.str();
    }

    librdf_node *BiomodelsQualifiers::toRdfNode() {
        return predicate.toRdfNode();
    }


}


/*
 * ITs all about creating this rdf_node_ptr_ object. Since this is a
 * creational problm, should I try a factory?
 *
 * I want to create these subclasses objects without specifying
 * all the information that the superclass needs.
 */