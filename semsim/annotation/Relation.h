# ifndef SEMSIM_RELATION_H_
# define SEMSIM_RELATION_H_

# include <string>
# include "semsim/annotation/URI.h"

namespace semsim {

    /**
     * Interface that provides methods for getting information about
     * relations (AKA predicates, AKA qualifiers) used in annotations.
     */
    class Relation {
      public:
        virtual const std::string& getName() = 0;

        /** @return The URI of the relation */
        virtual const URI& getURI() = 0;

        /** @return The URI of the relation as a string*/
        virtual const std::string& getURIasString() = 0;

        /** @return The free-text description of the relation*/
        virtual const std::string& getDescription() = 0;

        /** @return The relation encoded for SPARQL queries*/
        virtual const std::string& getSPARQLCode() = 0;

        /** @return The IRI of the relation*/
        // virtual IRI* getIRI() = 0;

        /** @return The relation instantiated as an RDF property*/
        // virtual Property* getRDFproperty() = 0;
    };
}

# endif
