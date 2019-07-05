# ifndef SEMSIM_RELATIONX_H_
# define SEMSIM_RELATIONX_H_

# include <string>
# include "semsim/URI.h"

namespace semsim {

    /**
     * Interface that provides methods for getting information about
     * relations (AKA predicates, AKA qualifiers) used in annotations.
     */
    class Relationx {
      public:
        Relation(const std::string& name, const URI& uri, const std::string& description)
          : name_(name), uri_(uri), description_(description) {}

        const std::string& getName() const {
          return name_;
        }

        /** @return The URI of the relation */
        const URI& getURI() const {
          return uri_;
        }

        /** @return The URI of the relation as a string*/
        std::string getURIasString() const {
          return uri_.toString();
        }

        /** @return The free-text description of the relation*/
        const std::string& getDescription() const {
          return description_;
        }

        /** @return The relation encoded for SPARQL queries*/
        // virtual const std::string& getSPARQLCode(){
        //
        // }

        /** @return The IRI of the relation*/
        // virtual IRI* getIRI() = 0;

        /** @return The relation instantiated as an RDF property*/
        // virtual Property* getRDFproperty() = 0;

      protected:
        std::string name_;
        URI uri_;
        std::string description_;
    };
}

# endif
