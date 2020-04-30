# ifndef SEMSIM_ENTITY_BASE_H_
# define SEMSIM_ENTITY_BASE_H_


# include "semsim/Resource.h"
# include "semsim/EntityDescriptor.h"
# include "semsim/RaptorUtils.h"

# include "raptor2.h"

# include <string>
# include <sstream>
#include <utility>

namespace semsim {

    /**
     * Base class of @ref Entity and @ref SingularAnnotation.
     * Maintains a list of @e definitions (resources linked via bqb:is)
     * and extraneous SBML CV terms (resources linked with any other qualifier).
     * Extraneous terms are not very useful for semantic information extraction.
     *
     * An @ref EntityBase will always have its own Url in the serialized RDF.
     */
    class EntityBase {
    public:
        /// The type used to store the list of definition URIs. Treat as opaque.
        typedef std::vector<Resource> Definitions;
        /// The type used to store the list of extraneous terms. Treat as opaque.
        typedef std::vector<Term> Terms;

        /// Construct from a definition Url
        EntityBase(std::string metaid, Resource &definition)
                : metaid_(std::move(metaid)), definitions_(1, definition) {}

        /// Move constructor
        EntityBase(EntityBase &&other) noexcept
                : metaid_(std::move(other.metaid_)),
                  definitions_(std::move(other.definitions_)),
                  terms_(std::move(other.terms_)) {}

        /// Move-construct from an @ref EntityDescriptor
        EntityBase(std::string metaid, Resource &&definition)
                : metaid_(std::move(metaid)), definitions_({std::move(definition)}) {}

        /// Move-construct from an @ref EntityDescriptor
        EntityBase(std::string &&metaid, Resource &&definition)
                : metaid_(std::move(metaid)), definitions_({std::move(definition)}) {}

        /// Construct from a meta id for this entity
        explicit EntityBase(std::string &metaid)
                : metaid_(metaid) {}

        /// Copy constructor
        EntityBase(EntityBase &other) : metaid_(other.metaid_), definitions_(other.definitions_),
                                        terms_(other.terms_) {}

        /// Get the meta id for this element
        std::string &getMetaId() {
            return metaid_;
        }

        /// Set the meta id
        void setMetaId(std::string &metaid) {
            metaid_ = metaid;
        }

        /// Get the local Url of this entity
        virtual Url getURI(Url &base) {
            return "#" + metaid_;
        }

        /// Get the number of @ref EntityDescriptor elements contained in this @ref EntityBase.
        std::size_t getNumDefinitions() {
            return definitions_.size();
        }

        /// Get the definition at index @p k.
        Resource &getDefinition(std::size_t k) {
            return definitions_.at(k);
        }

        /**
         * Get an iterable range of definitions.
         * Treat the return type as opaque, as it may change
         * to some other iterable in a future release.
         *
         * @return An iterable of @ref Resource "Resources".
         */
        Definitions &getDefinitions() {
            return definitions_;
        }

        /**
         * Get an iterable range of definitions.
         * Treat the return type as opaque, as it may change
         * to some other iterable in a future release.
         *
         * @return An iterable of @ref Resource "Resources".
         */
        Definitions &getDefinitions() {
            return definitions_;
        }

        /**
         * Add a definition to this entity.
         */
        void addDefinition(Resource &definition) {
            definitions_.push_back(definition);
        }

        /**
         * Check whether the entity's list of definitions contains a term that matches
         * the supplied definition.
         * @param definition The definition to match against.
         * @return @c true if this entity has a definition that matches the given definition
         */
        bool matchesDefinition(Resource &definition) {
            for (auto &i : definitions_) {
                if (i == definition)
                    return true;
            }
            return false;
        }

        /**
         * Add an extraneous term that cannot be classified as a definition
         * because it does not use the bqb:is qualifier.
         * Common causes are using bqb:isVersionOf, which is too non-committal
         * to be semantically useful.
         */
        void addExtraneousTerm(Term &term) {
            terms_.push_back(term);
        }

        /**
         * Add an extraneous term that cannot be classified as a definition
         * because it does not use the bqb:is qualifier.
         * Common causes are using bqb:isVersionOf, which is too non-committal
         * to be semantically useful.
         */
        void addExtraneousTerm(Term &&term) {
            terms_.emplace_back(std::move(term));
        }

        /// @return Whether this @ref Entity is empty (i.e. has no definitions).
        bool isEmpty() {
            return definitions_.empty();
        }

        /// Convert to human-readable string.
        std::string toString(std::size_t indent) {
            std::stringstream ss;
            ss << "    " << "definitions:\n";
            for (auto &definition : definitions_)
                ss << "    " << "  " << definition.toString() << "\n";
            if (!terms_.empty()) {
                ss << "    " << "extraneous terms:\n";
                for (auto &term : terms_)
                    ss << "    " << "  " << term.toString() << "\n";
            } else {
                ss << "    " << "extraneous terms: none\n";
            }
            return ss.str();
        }

        /**
         * Serialize this @ref EntityBase to RDF using the Raptor library.
         * The RDF serialization format is chosen when initializing the
         * @c raptor_serializer, and must be done before calling this function.
         * @param sbml_base_uri   The base Url of the SBML document relative to this (e.g. a relative path in a COMBINE archive).
         * @param world      Raptor world object. Must be initialized prior to calling this function.
         * @param serializer Raptor serializer object. Must be initialized prior to calling this function.
         * @return the Url for this entity.
         */
        void serializeToRDF(Url &sbml_base_uri, raptor_world *world, raptor_serializer *serializer) {
            // std::cerr << "serialize " << metaid_ << " definitions " << definitions_.size() << ", terms " << terms_.size() << "\n";
            for (auto &definition : definitions_)
                serializeDefinition(definition, sbml_base_uri, world, serializer);
            for (auto &term : terms_)
                serializeTerm(term, sbml_base_uri, world, serializer);
        }

        /**
         * Return a human--readable representation of the annotation
         * information. Ontology terms will be replaced with human-readable
         * names.
         */
        virtual std::string humanize() {
            return metaid_ + " -> (is) -> " + humanizeDefintions();
        }

    protected:

        void serializeDefinition(
                Resource &def,
                Url &sbml_base_uri,
                raptor_world *world,
                raptor_serializer *serializer) {
            Url this_uri = getURI(sbml_base_uri);

            SerializeURIStatement(this_uri.str(), bqb::is.getURI().str(), def.getURI().str(), world,
                                  serializer);
        }

        void serializeTerm(
                Term &term,
                Url &sbml_base_uri,
                raptor_world *world,
                raptor_serializer *serializer) {
            Url this_uri = getURI(sbml_base_uri);

            if (!term.isValue())
                SerializeURIStatement(this_uri.str(), term.getRelation().getURI().str(),
                                      term.getResource().getURI().str(), world, serializer);
            else
                SerializeURIStatement(this_uri.str(), term.getRelation().getURI().str(), term.getValue(), world,
                                      serializer);
        }

        std::string humanizeDefintions() {
            std::stringstream ss;
            for (auto i = definitions_.begin(); i != definitions_.end(); ++i) {
                if (i != definitions_.begin())
                    ss << "/";
                ss << i->humanize();
            }
            return ss.str();
        }

        /// The metaid for this entity - will be used to construct a Url in the serialized RDF
        std::string metaid_;
        /// The base Url for this entity (everything but the fragment part)
        // Url base_uri_;
        /// Collection of definition URIs for this annotation / entity
        Definitions definitions_;
        /// Collection of extraneous terms
        Terms terms_;
    };

}

# endif
