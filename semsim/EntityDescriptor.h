# ifndef SEMSIM_ENTITY_DESCRIPTOR_H_
# define SEMSIM_ENTITY_DESCRIPTOR_H_

# include "semsim/Preproc.h"
# include "semsim/DescriptorTerm.h"
# include <vector>

namespace semsim {
    /**
     * An @ref EntityDescriptor describes "what" a model element is and "where" it is located in the physical world.
     * An entity descriptor is essentially a linear chain of descriptor terms joined by
     * *structural relations*, which are <a href="http://co.mbine.org/standards/qualifiers">BioModels qualifiers</a> that describe the relationship between subsequent
     * entries in the descriptor term sequence.
     * For example, if an annotation describes
     * *cytosolic glucose concentration in a pancreatic beta cell*, then
     * the entity descriptor would be the:
     *
     * <a href="https://identifiers.org/CHEBI:17234">glucose</a>
     *  -> <a href="http://co.mbine.org/standards/qualifiers">occursIn</a>(structural relation) ->
     * <a href="https://identifiers.org/GO:0005829">cytosolic compartment</a>
     *  -> <a href="http://co.mbine.org/standards/qualifiers">isPartOf</a>(structural relation) ->
     * <a href="https://identifiers.org/CL:0000169">pancreatic beta cell</a>
     *
     * Consider another example from an physiological model.
     * Suppose the model contains a variable that represents the
     * *volume of blood in the left ventricle*:
     *
     * <a href="http://identifiers.org/fma/FMA:9670">blood</a>
     * -> <a href="http://co.mbine.org/standards/qualifiers">isPartOf</a>(structural relation) ->
     * <a href="http://identifiers.org/fma/FMA:9466">left ventricle</a>
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

      protected:
        /// A sequence of descriptor terms joined by structural relations
        DescriptorTerms terms_;
    };
}

# endif
