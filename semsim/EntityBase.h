# ifndef SEMSIM_ENTITY_BASE_H_
# define SEMSIM_ENTITY_BASE_H_

# include "semsim/Preproc.h"
# include "semsim/Resource.h"
# include "semsim/EntityDescriptor.h"
# include "semsim/util/Indent.h"

# include <string>
# include <sstream>

namespace semsim {

    /**
     * Base class of @ref Entity and @ref SingularAnnotation.
     * Maintains a list of @e definitions (resources linked via bqb:is)
     * and extraneous SBML CV terms (resources linked with any other qualifier).
     * Extraneous terms are not very useful for semantic information extraction.
     */
    class SEMSIM_PUBLIC EntityBase {
      public:
        /// The type used to store the list of definition URIs. Treat as opaque.
        typedef std::vector<Resource> Definitions;
        /// The type used to store the list of extraneous terms. Treat as opaque.
        typedef std::vector<Term> Terms;

        /// Construct from a definition URI
        EntityBase(const Resource& definition)
          : definitions_(1,definition) {}

        # if __cplusplus >= 201103L
        /// Move-construct from an @ref EntityDescriptor
        EntityBase(Resource&& definition)
          : definitions_({std::move(definition)}) {}
        # endif

        /// Empty constructor
        EntityBase() {}

        /// Get the number of @ref EntityDescriptor elements contained in this @ref EntityBase.
        std::size_t getNumDefinitions() const {
          return definitions_.size();
        }

        /// Get the definition at index @p k.
        const Resource& getDefinition(std::size_t k) const {
          return definitions_.at(k);
        }

        /**
         * Get an iterable range of definitions.
         * Treat the return type as opaque, as it may change
         * to some other iterable in a future release.
         *
         * @return An iterable of @ref Resource "Resources".
         */
        const Definitions& getDefinitions() const {
          return definitions_;
        }

        /**
         * Get an iterable range of definitions.
         * Treat the return type as opaque, as it may change
         * to some other iterable in a future release.
         *
         * @return An iterable of @ref Resource "Resources".
         */
        Definitions& getDefinitions() {
          return definitions_;
        }

        /**
         * Add a definition to this entity.
         */
        void addDefinition(const Resource& definition) {
          definitions_.push_back(definition);
        }

        /**
         * Add an extraneous term that cannot be classified as a definition
         * because it does not use the bqb:is qualifier.
         * Common causes are using bqb:isVersionOf, which is too non-committal
         * to be semantically useful.
         */
        void addExtraneousTerm(const Term& term) {
          terms_.push_back(term);
        }

        # if __cplusplus >= 201103L
        /**
         * Add an extraneous term that cannot be classified as a definition
         * because it does not use the bqb:is qualifier.
         * Common causes are using bqb:isVersionOf, which is too non-committal
         * to be semantically useful.
         */
        void addExtraneousTerm(Term&& term) {
          terms_.emplace_back(std::move(term));
        }
        # endif

        /// @return Whether this @ref Entity is empty (i.e. has no definitions).
        bool isEmpty() const {
          return !definitions_.size();
        }

        std::string toString(std::size_t indent) const {
          std::stringstream ss;
          ss << spaces(indent) << "definitions:\n";
          for (Definitions::const_iterator i(definitions_.begin()); i!=definitions_.end(); ++i)
            ss << spaces(indent) << "  " << i->toString() << "\n";
          if (terms_.size()) {
            ss << spaces(indent) << "extraneous terms:\n";
            for (Terms::const_iterator i(terms_.begin()); i!=terms_.end(); ++i)
              ss << spaces(indent) << "  " << i->toString() << "\n";
          } else {
            ss << spaces(indent) << "extraneous terms: none\n";
          }
          return ss.str();
        }

      protected:
        /// Collection of definition URIs for this annotation / entity
        Definitions definitions_;
        /// Collection of extraneous terms
        Terms terms_;
    };

}

# endif
