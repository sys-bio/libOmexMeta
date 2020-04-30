# ifndef SEMSIM_RELATION_H_
# define SEMSIM_RELATION_H_


#include <utility>

# include "semsim/uri.h"

namespace semsim {

    /**
     * A relation is the predicate part of an RDF triple.
     * SemSim uses the
     * <a href="http://co.mbine.org/standards/qualifiers">BioModels biology qualifiers</a>
     * for describing model elements.
     */
    class Relation {
    public:
        /**
         * Construct from URI.
         * @param url The URI of the ontology term
         */
        explicit Relation(Url url)
                : url_(std::move(url)) {}

        /**
         * Construct from string.
         * @param url The URI of the ontology term
         */
        explicit Relation(const std::string &url)
                : url_(Url(url)) {}

        std::string toString() const {
            return url_.str();
        }

        /**
         * @return the URI for this relation.
         */
        const Url &getURI() const {
            return url_;
        }

        /**
         * Return a human--readable representation of the annotation
         * information. Ontology terms will be replaced with human-readable
         * names.
         */
        std::string humanize() const;

        /// Comparison operator
        bool operator==(const Relation &other) const {
            return url_.str() == other.url_.str();
        }

    protected:
        Url url_;
    };
}
# endif
