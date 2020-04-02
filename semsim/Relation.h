# ifndef SEMSIM_RELATION_H_
# define SEMSIM_RELATION_H_


# include "semsim/url.h"

namespace semsim {

    /**
     * A relation is the predicate part of an RDF triple.
     * SemSim uses the
     * <a href="http://co.mbine.org/standards/qualifiers">BioModels biology qualifiers</a>
     * for describing model elements.
     */
    class  Relation {
    public:
        /**
         * Construct from URI.
         * @param url The URI of the ontology term
         */
        Relation(const Url &url)
                : url_(url) {}

        Relation(Url &&uri) : url_(std::move(uri)) {}

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
