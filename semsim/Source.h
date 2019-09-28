# ifndef SEMSIM_SOURCE_H_
# define SEMSIM_SOURCE_H_

# include "semsim/Component.h"
# include "semsim/SemSimQualifiers.h"

# include <sstream>

namespace semsim {

    /**
     * A @ref Source is a @ref Participant that is consumed
     * by a reaction.
     */
    class SEMSIM_PUBLIC Source : public Participant {
      public:
        /**
         * Construct from the given component and multiplier.
         * @param component A pre-existing component in the model associated with a species.
         * @param multiplier The stoichiometric coefficient for this participant in the reaction.
         */
        Source(const std::string& id, Component* component, double multiplier=1)
          : id_(id), component_(component), multiplier_(multiplier) {}

        bool containsMetaId(const std::string& metaid) const {
          return id_ == metaid;
        }

        /**
         * Serialize this participant to RDF using the Raptor library.
         * @param sbml_base_uri   The base URI of the SBML document relative to this (e.g. a relative path in a COMBINE archive).
         * @param world      Raptor world object. Must be initialized prior to calling this function.
         * @param serializer Raptor serializer object. Must be initialized prior to calling this function.
         * @return the URI for this entity.
         */
        virtual URI serializeToRDF(const URI& sbml_base_uri, raptor_world* world, raptor_serializer* serializer) const {
          URI this_uri = URI("#"+id_);

          // serialize multiplier
          {
            std::stringstream ss;
            ss << multiplier_;

            raptor_statement* s = raptor_new_statement(world);
            s->subject = raptor_new_term_from_uri_string(world, (const unsigned char*)this_uri.encode().c_str());
            s->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)semsim::hasMultiplier.getURI().encode().c_str());
            s->object = raptor_new_term_from_literal(world, (const unsigned char*)ss.str().c_str(), NULL, NULL);
            raptor_serializer_serialize_statement(serializer, s);
            raptor_free_statement(s);
          }
          // serialize physical entity reference
          {
            raptor_statement* s = raptor_new_statement(world);
            s->subject = raptor_new_term_from_uri_string(world, (const unsigned char*)this_uri.encode().c_str());
            s->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)semsim::hasPhysicalEntityReference.getURI().encode().c_str());
            s->object = raptor_new_term_from_uri_string(world, (const unsigned char*)component_->getURI(sbml_base_uri).encode().c_str());
            raptor_serializer_serialize_statement(serializer, s);
            raptor_free_statement(s);
          }

          return this_uri;
        }

      protected:
        std::string id_;
        Component* component_;
        double multiplier_;
    };

}

# endif
