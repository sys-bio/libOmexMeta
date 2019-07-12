# ifndef SEMSIM_ENTITY_BASE_H_
# define SEMSIM_ENTITY_BASE_H_

# include "semsim/Preproc.h"
# include "semsim/Resource.h"
# include "semsim/EntityDescriptor.h"
# include "semsim/util/Indent.h"

# include <raptor2.h>

# include <string>
# include <sstream>

namespace semsim {

    /**
     * Base class of @ref Entity and @ref SingularAnnotation.
     * Maintains a list of @e definitions (resources linked via bqb:is)
     * and extraneous SBML CV terms (resources linked with any other qualifier).
     * Extraneous terms are not very useful for semantic information extraction.
     *
     * An @ref EntityBase will always have its own URI in the serialized RDF.
     */
    class SEMSIM_PUBLIC EntityBase {
      public:
        /// The type used to store the list of definition URIs. Treat as opaque.
        typedef std::vector<Resource> Definitions;
        /// The type used to store the list of extraneous terms. Treat as opaque.
        typedef std::vector<Term> Terms;

        /// Construct from a definition URI
        EntityBase(const std::string& metaid, const Resource& definition)
          : metaid_(metaid), definitions_(1,definition) {}

        # if __cplusplus >= 201103L
        /// Move-construct from an @ref EntityDescriptor
        EntityBase(const std::string& metaid, Resource&& definition)
          : metaid_(metaid), definitions_({std::move(definition)}) {}

        /// Move-construct from an @ref EntityDescriptor
        EntityBase(std::string&& metaid, Resource&& definition)
          : metaid_(std::move(metaid)), definitions_({std::move(definition)}) {}
        # endif

        /// Construct from a meta id for this entity
        EntityBase(const std::string& metaid)
          : metaid_(metaid) {}

        /// Get the meta id for this element
        const std::string& getMetaId() const {
          return metaid_;
        }

        /// Set the meta id
        void setMetaId(const std::string& metaid) {
          metaid_ = metaid;
        }

        /// Get the local URI of this entity
        virtual URI getURI(const URI& base) const {
          return "#"+metaid_;
        }

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

        /// Convert to human-readable string.
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

        /**
         * Serialize this @ref EntityBase to RDF using the Raptor library.
         * The RDF serialization format is chosen when initializing the
         * @c raptor_serializer, and must be done before calling this function.
         * @param sbml_base_uri   The base URI of the SBML document relative to this (e.g. a relative path in a COMBINE archive).
         * @param world      Raptor world object. Must be initialized prior to calling this function.
         * @param serializer Raptor serializer object. Must be initialized prior to calling this function.
         * @return the URI for this entity.
         */
        void serializeToRDF(const URI& sbml_base_uri, raptor_world* world, raptor_serializer* serializer) const {
          // std::cerr << "serialize " << metaid_ << " definitions " << definitions_.size() << ", terms " << terms_.size() << "\n";
          for(Definitions::const_iterator i(definitions_.begin()); i!=definitions_.end(); ++i)
            serializeDefinition(*i, sbml_base_uri, world, serializer);
          for(Terms::const_iterator i(terms_.begin()); i!=terms_.end(); ++i)
            serializeTerm(*i, sbml_base_uri, world, serializer);
        }

      protected:

        void serializeDefinition(
              const Resource& def,
              const URI& sbml_base_uri,
              raptor_world* world,
              raptor_serializer* serializer) const {
          URI this_uri = getURI(sbml_base_uri);

          raptor_statement* s = raptor_new_statement(world);
          s->subject = raptor_new_term_from_uri_string(world, (const unsigned char*)this_uri.encode().c_str());
          s->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)bqb::is.getURI().encode().c_str());
          s->object = raptor_new_term_from_uri_string(world, (const unsigned char*)def.getURI().encode().c_str());
          raptor_serializer_serialize_statement(serializer, s);
          raptor_free_statement(s);
        }

        void serializeTerm(
              const Term& term,
              const URI& sbml_base_uri,
              raptor_world* world,
              raptor_serializer* serializer) const {
          URI this_uri = getURI(sbml_base_uri);

          raptor_statement* s = raptor_new_statement(world);
          s->subject = raptor_new_term_from_uri_string(world, (const unsigned char*)this_uri.encode().c_str());
          s->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)term.getRelation().getURI().encode().c_str());
          s->object = raptor_new_term_from_uri_string(world, (const unsigned char*)term.getResource().getURI().encode().c_str());
          raptor_serializer_serialize_statement(serializer, s);
          raptor_free_statement(s);
        }

        /// The metaid for this entity - will be used to construct a URI in the serialized RDF
        std::string metaid_;
        /// The base URI for this entity (everything but the fragment part)
        // URI base_uri_;
        /// Collection of definition URIs for this annotation / entity
        Definitions definitions_;
        /// Collection of extraneous terms
        Terms terms_;
    };

}

# endif
