# ifndef SEMSIM_COMPOSITE_ANNOTATION_H_
# define SEMSIM_COMPOSITE_ANNOTATION_H_

# include "semsim/Preproc.h"
# include "semsim/AnnotationBase.h"
# include "semsim/PhysicalProperty.h"
# include "semsim/Entity.h"

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
         * Construct an Annotation given a physical entity description ("what" is being described?)
         * and a domain descriptor ("where" does the entity reside?)
         * All annotations in SemSim are encoded as *composite* annotations.
         * Traditional SBML "CV term"-style annotations are expressible
         * in this more general framework, and are automatically converted
         * into composite annotations when they are read.
         * If the annotation only uses SBML CV term-style features
         * (i.e. the domain descriptor is empty), then the annotation
         * can be written back to the SBML file.
         * @param entity The descriptor for the physical entity in this annotation. The entity tells you "what" the annotation describes.
         * @param domain The descriptor for the physical domain that the model entity applies to. This tells you "where". For example, if the annotation describes "cytosolic glucose concentration in a pancreatic beta cell", the "where" part would be the "cytosol of a pancreatic beta cell".
         */
        CompositeAnnotation(const PhysicalProperty& property, const Entity& entity)
          : property_(property), entity_(entity) {}

        /// Copy constructor
        CompositeAnnotation(const CompositeAnnotation& other)
          :property_(other.property_), entity_(other.entity_) {}

        # if __cplusplus >= 201103L
        /// Move constructor
        CompositeAnnotation(CompositeAnnotation&& other)
          :property_(std::move(other.property_)), entity_(std::move(other.entity_)) {}
        # endif

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

      protected:
        /// Stores the physical entity descriptor for this annotation
        // EntityDescriptor entity_;
        /// Stores the physical property for this annotation
        PhysicalProperty property_;
        /// Stores the physical domain descriptor for this annotation
        Entity entity_;
    };
}

# endif
