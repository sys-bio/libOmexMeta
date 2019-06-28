# ifndef SEMSIM_ANNOTATION_H_
# define SEMSIM_ANNOTATION_H_

# include "semsim/Preproc.h"
# include "semsim/PhysicalProperty.h"
# include "semsim/DomainDescriptor.h"

namespace semsim {
    /**
     * The main class for storing all info related to the
     * annotation of a particular model element, i.e. any
     * physical quantity in the model. Examples of model
     * elements include SBML species concentrations,
     * compartment volumes, or any CellML variable that
     * represents a physical quantity (e.g. volume of the
     * left ventricle in the
     * <a href="https://github.com/combine-org/Annotations/blob/master/nonstandardized/CellML/smith_chase_nokes_shaw_wake_2004.omex">
     * Smith et al. example</a>).
     * Unlike the Java SemSim library, in this project,
     * **all** annotations in SemSim are encoded in the composite annotation
     * scheme (whether they are "true" composite annotations or not)
     * because its generality makes processing easier.
     * Traditional SBML annotations (which are called "CV terms")
     * consist of a single <a href="http://co.mbine.org/standards/qualifiers">qualifier</a> (e.g. bqb:is)
     * and a resource (usually an ontology term).
     * These annotations describe the "what" but not the "where"
     * parts of a composite annotation.
     * This means that the domain descriptor will be empty.
     * You can check whether an annotation is SBML-compatible
     * by calling @ref Annotation::isSBMLCompatible
     * True composite annotations (which can include a domain descriptor
     * with multiple terms describing the physical domain where the
     * model applies) are not expressible in SBML and **must** instead be
     * written out to the OMEX RDF metadata.
     */
    SEMSIM_PUBLIC class Annotation {
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
        Annotation(const PhysicalProperty& property, const DomainDescriptor& domain)
          : property_(property), domain_(domain) {}

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
         * This function returns @p true if the physical domain
         * descriptor is empty. The domain describes "where"
         * the physical entity is located. It is typically empty for
         * annotations read in from SBML models, since SBML has
         * no way of expressing the "where" part of a composite annotation.
         * However, if the SBML entity is a **species** that resides in
         * a **compartment**, SemSim may automatically insert a domain
         * descriptor encoding the species/compartment relationship (
         * and this function will return false).
         * @return Whether the physical domain descriptor is empty.
         */
        bool isDomainEmpty() const {
          return domain_.isEmpty();
        }

        /**
         * @return The @ref EntityDescriptor describing the physical entity of this annotation.
         */
        const DomainDescriptor& getDomain() const {
          return domain_;
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
        bool isSBMLCompatible() const {
          return isDomainEmpty();
        }

      protected:
        /// Stores the physical entity descriptor for this annotation
        // EntityDescriptor entity_;
        /// Stores the physical property for this annotation
        PhysicalProperty property_;
        /// Stores the physical domain descriptor for this annotation
        DomainDescriptor domain_;
    }
}

# endif
