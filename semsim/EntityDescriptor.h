# ifndef SEMSIM_ENTITY_DESCRIPTOR_H_
# define SEMSIM_ENTITY_DESCRIPTOR_H_

# include "semsim/Preproc.h"
# include "semsim/DescriptorTerm.h"
# include <vector>

namespace semsim {
    /**
     * An @ref EntityDescriptor describes "what" a model element is and "where" it is located in the physical world.
     */
    class SEMSIM_PUBLIC EntityDescriptor {
      public:
        typedef std::vector<DescriptorTerm> DescriptorTerms;

        /// Empty constructor
        EntityDescriptor() {}

        # if __cplusplus >= 201103L
        /**
         * Variadic move constructor.
         * This constructor allows you to create
         * a entity descriptor from a list of terms
         * passed in as arguments.
         *
         * @code{.cpp}
         * EntityDescriptor mydesc = EntityDescriptor(DescriptorTerm(),
         *                                            DescriptorTerm());
         * @endcode
         */
        // http://cpptruths.blogspot.com/2012/06/perfect-forwarding-of-parameter-groups.html
        template <class ...T>
        EntityDescriptor(T&&... args)
          : terms_(std::forward(args)...) {}
        # endif

        /// @return @p true if this descriptor is empty
        bool isEmpty() const {
          return !terms_.size();
        }

        /// Add a descriptor term to the sequence of terms
        void addTerm(const DescriptorTerm& t) {
          terms_.push_back(t);
        }

        # if __cplusplus >= 201103L
        /// Add a descriptor term to the sequence of terms
        void addTerm(DescriptorTerm&& t) {
          terms_.emplace_back(std::move(t));
        }
        # endif

        /**
         * Serialize this entity to RDF using the Raptor library.
         * This function should only be called from the @ref Entity class.
         * The RDF serialization format is chosen when initializing the
         * @c raptor_serializer, and must be done before calling this function.
         * @param base_metaid   The meta id of the entity this descriptor is attached to.
         * @param world      Raptor world object. Must be initialized prior to calling this function.
         * @param serializer Raptor serializer object. Must be initialized prior to calling this function.
         * @return the URI for this entity.
         */
        void serializeToRDF(const URI& base_uri, const std::string& metaid, raptor_world* world, raptor_serializer* serializer) const {
          unsigned int k=0;
          URI last_uri=base_uri;
          for (DescriptorTerms::const_iterator i(terms_.begin()); i!=terms_.end(); ++i) {
            std::stringstream ss_this;
            ss_this << metaid << "_term" << ++k;
            std::string next_uri=base_uri.withFrag(ss_this.str());
            serializeDescriptorTermToRDF(*i, last_uri, next_uri, world, serializer);
            last_uri = next_uri;
          }
        }

      protected:
        void serializeDescriptorTermToRDF(
              const DescriptorTerm& term,
              const URI& linked_uri,
              const URI& term_uri,
              raptor_world* world,
              raptor_serializer* serializer) const {

          // term definition triple
          raptor_statement* s = raptor_new_statement(world);
          s->subject = raptor_new_term_from_uri_string(world, (const unsigned char*)term_uri.encode().c_str());
          s->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)bqb::is.getURI().encode().c_str());
          s->object = raptor_new_term_from_uri_string(world, (const unsigned char*)term.getResource().getURI().encode().c_str());
          raptor_serializer_serialize_statement(serializer, s);
          raptor_free_statement(s);

          // term structural relation triple
          s = raptor_new_statement(world);
          s->subject = raptor_new_term_from_uri_string(world, (const unsigned char*)linked_uri.encode().c_str());
          s->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)term.getRelation().getURI().encode().c_str());
          s->object = raptor_new_term_from_uri_string(world, (const unsigned char*)term_uri.encode().c_str());
          raptor_serializer_serialize_statement(serializer, s);
          raptor_free_statement(s);
        }

        /// A sequence of descriptor terms joined by structural relations
        DescriptorTerms terms_;
    };
}

# endif
