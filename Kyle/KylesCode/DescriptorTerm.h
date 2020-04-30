# ifndef SEMSIM_DESCRIPTOR_TERM_H_
# define SEMSIM_DESCRIPTOR_TERM_H_


# include "semsim/Resource.h"
# include "semsim/Relation.h"
# include "semsim/Term.h"

namespace semsim {
    /**
     * A descriptor term is used as part of a @ref DomainDescriptor
     * to describe "where" a model element is in the physical world.
     */
    class DescriptorTerm : public Term {
    public:
        /// Construct from a @ref Resource (URI) and @ref Relation
        DescriptorTerm(Relation &relation, Resource &resource)
                : Term(relation, resource) {}

        /// Move-construct from a @ref Resource (URI) and @ref Relation
        DescriptorTerm(Relation &&relation, Resource &&resource)
                : Term(relation, resource) {}
    };
}

# endif
