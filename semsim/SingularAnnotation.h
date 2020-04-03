# ifndef SEMSIM_SINGULAR_ANNOTATION_H_
# define SEMSIM_SINGULAR_ANNOTATION_H_


# include "semsim/AnnotationBase.h"
# include "semsim/PhysicalProperty.h"
# include "semsim/EntityBase.h"
# include "semsim/SemSimQualifiers.h"
# include "semsim/url.h"

// todo Think seriously about the need for multiple inheritance here. I suspect simple composition would be better.

namespace semsim {
    /**
     * The singular / "plain" annotation class is designed to represent
     * traditional MIRIAM annotations found in SBML models.
     * These types of annotations are not as expressive
     * as @ref CompositeAnnotation "CompositeAnnotations"
     * and can only point to one or more @ref Resource "Resources"
     * which define the entity.
     * Overusing definition Urls is generally bad practice and,
     * ideally, one should use a single definition Url that best
     * captures the model element.
     */
    class SingularAnnotation : public AnnotationBase, public EntityBase {
    public:
        /**
         * Construct a SingularAnnotation given a definition URL.
         * For example, to create an annotation describing pyruvate:
         *
         * \code{.cpp}
         * # include "semsim/SemSim.h"
         * using namespace semsim;
         * // will automatically get assigned a "bqb:is" relation
         * // pointing to CHEBI:15361
         * SingularAnnotation a("metaid", CHEBI::get(15361));
         * \endcode
         *
         * Generally, a model element should be defined using
         * only a single Url.
         */
        SingularAnnotation( std::string &metaid,  Resource &definition)
                : EntityBase(metaid, definition) {}

        /// Constructor specifying only the meta id (defintions to be added later by user)
        SingularAnnotation(std::string &metaid)
                : EntityBase(metaid) {}

        /// Move-construct from an @ref EntityDescriptor
        SingularAnnotation( std::string &metaid, Resource &&definition)
                : EntityBase(metaid, {std::move(definition)}) {}

        /// Copy constructor
        SingularAnnotation(SingularAnnotation &other)
                : EntityBase(other) {}

        /// Move constructor
        SingularAnnotation(SingularAnnotation &&other)
                : EntityBase(std::move(other)) {}

        /// Get the meta id for this element.
         std::string &getMetaId()  {
            return EntityBase::getMetaId();
        }

        /// Create a copy of this object using the correct derived class's type.
        // todo: Why not just use the copy constructor for cloning?
        AnnotationBase *clone() override {
            return new SingularAnnotation(*this);
        }

        /**
         * Serialize this annotation to RDF using the Raptor library.
         * This function just delegates to the @ref EntityBase serialization logic.
         * The RDF serialization format is chosen when initializing the
         * @c raptor_serializer, and must be done before calling this function.
         * @param sbml_base_Url   The base Url of the SBML document relative to this (e.g. a relative path in a COMBINE archive).
         * @param world      Raptor world object. Must be initialized prior to calling this function.
         * @param serializer Raptor serializer object. Must be initialized prior to calling this function.
         * @return the Url for this entity.
         */
        void serializeToRDF(Url &sbml_base_uri, raptor_world *world, raptor_serializer *serializer)  override {
            EntityBase::serializeToRDF(sbml_base_uri, world, serializer);
        }

        std::string getRDF(Url &sbml_base_uri,  std::string &format)  override {
            raptor_world *world = raptor_new_world();
            raptor_serializer *serializer = raptor_new_serializer(world, format.c_str());
            if (!serializer)
                throw std::runtime_error("Could not create Raptor serializer for format " + format);

            raptor_uri *base_uri = raptor_new_uri(world, ( unsigned char *) "");

            raptor_serializer_set_namespace(serializer,
                                            raptor_new_uri(world, ( unsigned char *) bqb::root.c_str()),
                                            ( unsigned char *) "bqb");
            raptor_serializer_set_namespace(serializer,
                                            raptor_new_uri(world, ( unsigned char *) semsim::root.c_str()),
                                            ( unsigned char *) "semsim");

            void *output;
            size_t length;
            raptor_serializer_start_to_string(serializer, base_uri, &output, &length);

            serializeToRDF(sbml_base_uri, world, serializer);

            raptor_serializer_serialize_end(serializer);

            raptor_free_serializer(serializer);
            raptor_free_world(world);

            std::string result((char *) output);
            free(output);
            return result;
        }

        /**
         * Convert singular annotations to composite annotations
         * by copying their definitions and terms.
         * @param prop The physical property to assign to the composite annotation.
         * @return A new composite annotation
         */
        AnnotationPtr makeComposite(PhysicalProperty &prop) override;

        /// Get the local URL of this entity
        Url getURI(Url &base)  override {
            return base.fragment(metaid_);
        }

        /**
         * Return a human--readable representation of the annotation
         * information. Ontology terms will be replaced with human-readable
         * names.
         */
        std::string humanize()  override {
            return EntityBase::humanize();
        }

        bool isComposite()  override {
            return false;
        }
    };
}

# endif
