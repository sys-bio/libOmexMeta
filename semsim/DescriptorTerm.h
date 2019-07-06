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
      /// Construct from a @ref Resource (URI) and @ref Relation
      DescriptorTerm(const Relation& relation, const Resource& resource)
        : relation_(relation), resource_(resource) {}

      # if __cplusplus >= 201103L
      /// Move-construct from a @ref Resource (URI) and @ref Relation
      DescriptorTerm(Relation&& relation, Resource&& resource)
        : relation_(std::move(relation)), resource_(std::move(resource)) {}
      # endif
    };
}

# endif
