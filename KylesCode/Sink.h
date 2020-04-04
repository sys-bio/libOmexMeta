# ifndef SEMSIM_SINK_H_
# define SEMSIM_SINK_H_

# include "semsim/Component.h"
# include "semsim/SemSimQualifiers.h"

# include <sstream>

namespace semsim {

    /**
     * A @ref Sink is a @ref Participant that is produced
     * by a reaction (the end point of the reaction).
     */
    class Sink : public Participant {

    public:
        /**
         * Construct from the given component and multiplier.
         * @param component A pre-existing component in the model associated with a species.
         * @param multiplier The stoichiometric coefficient for this participant in the reaction.
         */
        Sink( std::string &id, Component *component, double multiplier = 1)
                : id_(id), component_(component), multiplier_(multiplier) {}

        bool containsMetaId( std::string &metaid)  {
            return id_ == metaid;
        }

        /**
         * Serialize this participant to RDF using the Raptor library.
         * @param sbml_base_uri   The base URI of the SBML document relative to this (e.g. a relative path in a COMBINE archive).
         * @param world      Raptor world object. Must be initialized prior to calling this function.
         * @param serializer Raptor serializer object. Must be initialized prior to calling this function.
         * @return the URI for this entity.
         */
        virtual Url serializeToRDF(Url &sbml_base_uri, raptor_world *world, raptor_serializer *serializer)  {
            Url this_uri = Url("#" + id_);

            // serialize multiplier
            {
                std::stringstream ss;
                ss << multiplier_;

                raptor_statement *s = raptor_new_statement(world);
                s->subject = raptor_new_term_from_uri_string(world, ( unsigned char *) this_uri.str().c_str());
                s->predicate = raptor_new_term_from_uri_string(world,
                                                               ( unsigned char *) semsim::hasMultiplier.getURI().str().c_str());
                s->object = raptor_new_term_from_literal(world, ( unsigned char *) ss.str().c_str(), NULL, NULL);
                raptor_serializer_serialize_statement(serializer, s);
                raptor_free_statement(s);
            }
            // serialize physical entity reference
            {
                raptor_statement *s = raptor_new_statement(world);
                s->subject = raptor_new_term_from_uri_string(world, ( unsigned char *) this_uri.str().c_str());
                s->predicate = raptor_new_term_from_uri_string(world,
                                                               ( unsigned char *) semsim::hasPhysicalEntityReference.getURI().str().c_str());
                s->object = raptor_new_term_from_uri_string(
                        world,
                        ( unsigned char *) component_->getURI(sbml_base_uri).str().c_str()
                        );
                raptor_serializer_serialize_statement(serializer, s);
                raptor_free_statement(s);
            }

            return this_uri;
        }

    protected:
        std::string id_;
        Component *component_;
        double multiplier_;
    };

}

# endif
