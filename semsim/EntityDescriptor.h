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

      protected:
        /// A sequence of descriptor terms joined by structural relations
        DescriptorTerms terms_;
    };
}

# endif
