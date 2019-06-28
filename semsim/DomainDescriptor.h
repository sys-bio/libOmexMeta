# ifndef SEMSIM_DOMAIN_DESCRIPTOR_H_
# define SEMSIM_DOMAIN_DESCRIPTOR_H_

# include "semsim/Preproc.h"
# include "semsim/DescriptorTerm.h"
# include <vector>

namespace semsim {
    /**
     * The domain descriptor is one of the two parts of a composite annotation.
     * It describes "where" a model element is located in the physical world
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
     *  -> <a href="http://co.mbine.org/standards/qualifiers">isPartOf</a>(structural relation) ->
     * <a href="https://identifiers.org/CL:0000169">pancreatic beta cell</a>
     *
     * Consider another example from an physiological model.
     * Suppose the model contains a variable that represents the
     * *volume of blood in the left ventricle*. The *domain* part of this
     * composite annotation is *blood in the left ventricle*, which could be represented as
     *
     * <a href="http://identifiers.org/fma/FMA:9670">blood</a>
     * -> <a href="http://co.mbine.org/standards/qualifiers">isPartOf</a>(structural relation) ->
     * <a href="http://identifiers.org/fma/FMA:9466">left ventricle</a>
     */
    SEMSIM_PUBLIC class DomainDescriptor {
      public:
        typedef std::vector<DescriptorTerm> DescriptorTerms;

        /// Empty constructor
        DomainDescriptor() {}

        # if __cplusplus >= 201103L
        /**
         * Variadic move constructor.
         * This constructor allows you to create
         * a domain descriptor from a list of terms
         * passed in as arguments.
         *
         * @code
         * DomainDescriptor mydesc = DomainDescriptor(DescriptorTerm(),
         *                                            DescriptorTerm());
         * @endcode
         */
        // http://cpptruths.blogspot.com/2012/06/perfect-forwarding-of-parameter-groups.html
        template <class ...T>
        DomainDescriptor(T&&... args)
          : terms_(std::forwardargs...) {}
        # endif

        /// @return @p true if this descriptor is empty
        bool isEmpty() const {
          return !terms_.size();
        }

      protected:
        /// A sequence of descriptor terms joined by structural relations
        DescriptorTerms terms_;
    };
}

# endif
