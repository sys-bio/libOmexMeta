# ifndef SEMSIM_ENTITY_DESCRIPTOR_H_
# define SEMSIM_ENTITY_DESCRIPTOR_H_


# include "semsim/DescriptorTerm.h"
# include "semsim/BiomodelsQualifiers.h"
#include "url.h"

# include <raptor2.h>

# include <vector>
# include <sstream>

namespace semsim {
    /**
     * An @ref EntityDescriptor describes "what" a model element is and "where" it is located in the physical world.
     */
    class EntityDescriptor {
    public:

        typedef std::vector<DescriptorTerm> DescriptorTerms;

        /// Empty constructor
        EntityDescriptor() = default;

        /// Copy constructor
        EntityDescriptor(EntityDescriptor &other)
                : terms_(other.terms_) {}

        /// Move constructor
        EntityDescriptor(EntityDescriptor &&other)
                : terms_(std::move(other.terms_)) {}


        /**
         * std::initializer_list constructor.
         * This constructor allows you to create
         * a entity descriptor from a list of terms
         * passed in as arguments.
         *
         * @code{.cpp}
         * EntityDescriptor mydesc = EntityDescriptor(DescriptorTerm(),
         *                                            DescriptorTerm());
         * @endcode
         */
        // https://stackoverflow.com/questions/28370970/forwarding-initializer-list-expressions
        template<class T>
        explicit EntityDescriptor(std::initializer_list<T> l)
                : terms_(l) {}


        /// @return @p true if this descriptor is empty
        bool isEmpty() {
            return !terms_.size();
        }

        /// Add a descriptor term to the sequence of terms
        void addTerm(DescriptorTerm &t) {
            terms_.push_back(t);
        }

        /// Add a descriptor term to the sequence of terms
        void addTerm(DescriptorTerm &&t) {
            terms_.emplace_back(std::move(t));
        }

        /// Shortcut for constructing & adding a descriptor term
        void addTerm(Relation &relation, Resource &resource) {
            terms_.push_back(DescriptorTerm(relation, resource));
        }

        /**
         * Serialize this entity descriptor to RDF using the Raptor library.
         * This function should only be called from the @ref Entity class.
         * The RDF serialization format is chosen when initializing the
         * @c raptor_serializer, and must be done before calling this function.
         * @param sbml_base_uri   The base Url of the SBML model (usu. a relative path in a COMBINE archive).
         * @param metaid   The meta id of the entity this descriptor is attached to.
         * @param world      Raptor world object. Must be initialized prior to calling this function.
         * @param serializer Raptor serializer object. Must be initialized prior to calling this function.
         * @return the Url for this entity.
         */
        void serializeToRDF(Url &sbml_base_uri, std::string &metaid, raptor_world *world,
                            raptor_serializer *serializer) {
            unsigned int k = 0;
            Url last_uri = "#" + metaid;
            for (DescriptorTerms::const_iterator i(terms_.begin()); i != terms_.end(); ++i) {
                if (!i->getResource().isLocal()) {
                    std::stringstream ss_this;
                    ss_this << metaid << "_term" << ++k;
                    Url next_uri = "#" + ss_this.str();
                    serializeDescriptorTermToRDF(*i, last_uri, next_uri, world, serializer);
                    last_uri = next_uri;
                } else {
                    serializeDescriptorTermToRDF(*i, last_uri, i->getResource().getURI(sbml_base_uri), world,
                                                 serializer);
                }
            }
        }

        /**
         * Return a human--readable representation of the annotation
         * information. Ontology terms will be replaced with human-readable
         * names.
         */
        std::string humanize() {
            return humanizeTerms();
        }

    protected:
        void serializeDescriptorTermToRDF(
                DescriptorTerm &term,
                Url &linked_uri,
                Url &term_uri,
                raptor_world *world,
                raptor_serializer *serializer) {
            // term structural relation triple
            raptor_statement *s = raptor_new_statement(world);
            s->subject = raptor_new_term_from_uri_string(world, (unsigned char *) linked_uri.str().c_str());
            s->predicate = raptor_new_term_from_uri_string(world,
                                                           (unsigned char *) term.getRelation().getURI().str().c_str());
            s->object = raptor_new_term_from_uri_string(world, (unsigned char *) term_uri.str().c_str());
            raptor_serializer_serialize_statement(serializer, s);
            raptor_free_statement(s);

            // term definition triple
            if (!term.getResource().isLocal()) {
                s = raptor_new_statement(world);
                s->subject = raptor_new_term_from_uri_string(world, (unsigned char *) term_uri.str().c_str());
                s->predicate = raptor_new_term_from_uri_string(world,
                                                               (unsigned char *) bqb::is.getURI().str().c_str());
                s->object = raptor_new_term_from_uri_string(world,
                                                            (unsigned char *) term.getResource().getURI().str().c_str());
                raptor_serializer_serialize_statement(serializer, s);
                raptor_free_statement(s);
            }
        }

        std::string humanizeTerms() {
            std::stringstream ss;
            for (DescriptorTerms::const_iterator i = terms_.begin(); i != terms_.end(); ++i) {
                ss << " -> ";
                ss << "(" + i->getRelation().humanize() + ")";
                ss << " -> ";
                ss << i->getResource().humanize();
            }
            return ss.str();
        }

        /// A sequence of descriptor terms joined by structural relations
        DescriptorTerms terms_;
    };
}

# endif
