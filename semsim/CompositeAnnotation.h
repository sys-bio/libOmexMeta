# ifndef SEMSIM_COMPOSITE_ANNOTATION_H_
# define SEMSIM_COMPOSITE_ANNOTATION_H_

# include "semsim/Preproc.h"
# include "semsim/AnnotationBase.h"
# include "semsim/PhysicalProperty.h"
# include "semsim/Entity.h"
# include "semsim/SingularAnnotation.h"

namespace semsim {
    /**
     * Composite annotations allow more precise descriptions of model
     * elements than singular ("plain") @ref Annotation "Annotations".
     * Whereas singular annotations specify the *chemical identity* of an SBML
     * species or the *physiological identity* of a CellML variable,
     * composite annotations also provide two additional pieces of information:
     * the @ref PhysicalProperty of an element, which specifies the physical
     * quantity the element represents (e.g. *concentration* or *amount* of an
     * SBML species; *liquid volume* or *electric current* of a CellML variable),
     * and a linear chain of terms (the @ref EntityDescriptor) that describes
     * *what* the element is (e.g. the chemical identity of an SBML species)
     * and *where* it is in the physical world.
     *
     * For example, to describe an SBML species representing the
     * *cytosolic glucose concentration in a pancreatic beta cell*,
     * one would need to specify that the species represents
     * glucose (<a href="https://identifiers.org/CHEBI:17234">CHEBI:17234</a>)
     * inside the cytosolic compartment (<a href="https://identifiers.org/GO:0005829">GO:0005829</a>)
     * of a pancreatic beta cell (<a href="https://identifiers.org/CL:0000169">CL:0000169</a>).
     * The following code snippet illustrates how to construct a @ref CompositeAnnotation
     * for this example:
     *
     * @code{.cpp}
     * // this example assumes you are using C++11 mode
     * // (controlled by the SEMSIM_CXX_STANDARD CMake variable)
     * @endcode
     */
    class SEMSIM_PUBLIC CompositeAnnotation : public AnnotationBase {
      public:
        /**
         * Construct a @ref CompositeAnnotation given a physical property (what is the quantity being represented - chemical concentration, fluid volume, etc.?)
         * and a domain descriptor ("what" is the chemical identity and "where" does the entity reside in physical space?)
         * @param property The physical property of this composite annotation. Always provided.
         * @param entity The entity contains all information outside of the physical property. This tells you "what" the element is (e.g. by specifying chemical identity) and "where". For example, if the annotation describes "cytosolic glucose concentration in a pancreatic beta cell", the entity would contain a definition (glycose) and two *structural relations* specifying the entity is *occurs in* the cytosol, which in turn *is part of* a pancreatic beta cell.
         */
        CompositeAnnotation(const PhysicalProperty& property, const Entity& entity)
          : property_(property), entity_(entity) {}

        # if __cplusplus >= 201103L
        /**
         * Construct a @ref CompositeAnnotation given a physical property (what is the quantity being represented - chemical concentration, fluid volume, etc.?)
         * and a domain descriptor ("what" is the chemical identity and "where" does the entity reside in physical space?)
         * @param property The physical property of this composite annotation. Always provided.
         * @param entity The entity contains all information outside of the physical property. This tells you "what" the element is (e.g. by specifying chemical identity) and "where". For example, if the annotation describes "cytosolic glucose concentration in a pancreatic beta cell", the entity would contain a definition (glycose) and two *structural relations* specifying the entity is *occurs in* the cytosol, which in turn *is part of* a pancreatic beta cell.
         */
        CompositeAnnotation(PhysicalProperty&& property, Entity&& entity)
          : property_(std::move(property)), entity_(std::move(entity)) {}
        # endif

        /// Copy constructor
        CompositeAnnotation(const CompositeAnnotation& other)
          :property_(other.property_), entity_(other.entity_) {}

        # if __cplusplus >= 201103L
        /// Move constructor
        CompositeAnnotation(CompositeAnnotation&& other)
          :property_(std::move(other.property_)), entity_(std::move(other.entity_)) {}
        # endif

        /**
         * Construct from a singular annotation.
         * Copy all definitions and terms.
         * @param other The singular annotation to copy.
         * @param property The physical property to assign to the composite annotation.
         * @param
         */
        CompositeAnnotation(const SingularAnnotation& other, const PhysicalProperty& property)
          : property_(property), entity_(other) {}

        /// Get the meta id for this element.
        const std::string& getMetaId() const {
          return getEntity().getMetaId();
        }

        /**
         * This function returns @p true if the physical entity
         * descriptor is empty. This should not be the case
         * for any useful annotation.
         * @return Whether the physical entity descriptor is empty.
         */
        // bool isEntityEmpty() const {
          // return entity_.isEmpty();
        // }

        /**
         * @return The @ref EntityDescriptor describing the physical entity of this annotation.
         */
        // const EntityDescriptor& getEntity() const {
        //   return entity_;
        // }

        /**
         * This function returns @p true if the @ref Entity element of this composite annotation is empty.
         * The entity describes "what" the model element is and "where"
         * the it is located.
         * IGNORE:
         * It is typically empty for
         * annotations read in from SBML models, since SBML has
         * no way of expressing the "where" part of a composite annotation.
         * However, if the SBML entity is a **species** that resides in
         * a **compartment**, SemSim may automatically insert a domain
         * descriptor encoding the species/compartment relationship (
         * and this function will return false).
         * @return Whether the physical domain descriptor is empty.
         */
        bool isEntityEmpty() const {
          return entity_.isEmpty();
        }

        /**
         * @return The @ref EntityDescriptor describing the physical entity of this annotation.
         */
        const Entity& getEntity() const {
          return entity_;
        }

        /**
         * This function returns @p true if this annotation
           * can be encoded in an SBML model (i.e. its domain
         * descriptor must be empty).
         * The only exception to this is when the domain descriptor
         * consists of a single term, and that term describes the
         * *compartment* that the entity resides in.
         * @return [description]
         */
        // bool isSBMLCompatible() const {
        //   return isDomainEmpty();
        // }


        /// Create a copy of this object using the correct derived class's type.
        virtual AnnotationBase* clone() const {
          return new CompositeAnnotation(*this);
        }

        /**
         * Serialize this annotation to RDF using the Raptor library.
         * The RDF serialization format is chosen when initializing the
         * @c raptor_serializer, and must be done before calling this function.
         * @param world      Raptor world object. Must be initialized prior to calling this function.
         * @param serializer Raptor serializer object. Must be initialized prior to calling this function.
         */
        virtual void serializeToRDF(const URI& sbml_base_uri, raptor_world* world, raptor_serializer* serializer) const {
          entity_.serializeToRDF(sbml_base_uri, world, serializer);
        }

        /**
         * @return the URI for this element (usually a local identifier).
         */
        const URI& getURI() const {
          return uri_;
        }

        /**
         * Convert singular annotations to composite annotations
         * by copying their definitions and terms.
         * Effect when called on an instance of @ref CompositeAnnotation
         * is to create a clone.
         * @return A new composite annotation
         */
        AnnotationPtr makeComposite(const PhysicalProperty& prop) const {
          return AnnotationPtr(clone());
        }

      protected:
        /// Stores the physical entity descriptor for this annotation
        // EntityDescriptor entity_;
        /// Stores the physical property for this annotation
        PhysicalProperty property_;
        /// Stores the physical domain descriptor for this annotation
        Entity entity_;
        /// Stores the URI of this element (usu. a local identifier)
        URI uri_;
    };
}

# endif
