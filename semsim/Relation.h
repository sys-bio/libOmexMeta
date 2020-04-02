# ifndef SEMSIM_RELATION_H_
# define SEMSIM_RELATION_H_


# include "semsim/Url.h"

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
        Relation( Url &url)
                : url_(url) {}

        Relation(Url &&uri) : url_(std::move(uri)) {}

        std::string toString()  {
            return url_.str();
        }

        /**
         * @return the URI for this relation.
         */
         Url &getURI()  {
            return url_;
        }

        /**
         * Return a human--readable representation of the annotation
         * information. Ontology terms will be replaced with human-readable
         * names.
         */
        std::string humanize() ;

        /// Comparison operator
        bool operator==( Relation &other)  {
            return url_.str() == other.url_.str();
        }

    protected:
        Url url_;
    };
}
# endif
