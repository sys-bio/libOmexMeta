# ifndef SEMSIM_ANNOTATION_H_
# define SEMSIM_ANNOTATION_H_

namespace semsim {
    /**
     * The domain descriptor is one of the two parts of a composite annotation.
     * It describes "where" the physical entity of a model element is located
     * (i.e. the physical *domain* that the model entity is designed to represent).
     * A domain descriptor consists of a chain of descriptor terms joined by
     * *structural relations*, which describe the relationship between subsequent
     * entries in the descriptor term sequence.
     * For example, if an annotation describes
     * *cytosolic glucose concentration in a pancreatic beta cell*, then
     * the domain descriptor would be the *cytosolic compartment of a pancreatic beta cell*,
     * and the descriptor terms would be:
     *
     * <a href="https://identifiers.org/GO:0005829">cytosolic compartment</a>
     *  -> <a href="http://co.mbine.org/standards/qualifiers">isPartOf</a> ->
     * <a href=" http://purl.obolibrary.org/obo/CL_0000169">pancreatic beta cell</a>
     * https://identifiers.org/CL:0000169
     *
     *
     */
    class DomainDescriptor {
      public:


      protected:
        /// A sequence of descriptor terms joined by structural relations
        DescriptorTerms terms_;
    }
}

# endif
