# ifndef SEMSIM_DESCRIPTOR_TERM_H_
# define SEMSIM_DESCRIPTOR_TERM_H_

# include "semsim/Preproc.h"
# include "semsim/Resource.h"
# include "semsim/Relation.h"
# include "semsim/Term.h"

namespace semsim {
    /**
     * A descriptor term is used as part of a @ref DomainDescriptor
     * to describe "where" a model element is in the physical world.
     */
    class SEMSIM_PUBLIC DescriptorTerm : public Term {
    };
}

# endif
