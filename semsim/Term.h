# ifndef SEMSIM_TERM_H_
# define SEMSIM_TERM_H_

# include "semsim/Preproc.h"
# include "semsim/Resource.h"

# include <string>

namespace semsim {

    /**
     * A term contains a qualifier and a resource.
     * The qualifier is typically one of the BioModels qualifiers.
     */
    class SEMSIM_PUBLIC Term {
      public:
        /// Construct from a @ref Resource (URI) and @ref Relation
        Term(const Relation& relation, const Resource& resource)
          : relation_(relation), resource_(resource) {}

        # if __cplusplus >= 201103L
        /// Move-construct from a @ref Resource (URI) and @ref Relation
        Term(Relation&& relation, Resource&& resource)
          : relation_(std::move(relation)), resource_(std::move(resource)) {}
        # endif

        /// @return The @ref Resource of this term.
        const Relation& getRelation() const {
          return relation_;
        }

        /// @return The @ref Resource of this term.
        const Resource& getResource() const {
          return resource_;
        }

      protected:
        Relation relation_;
        Resource resource_;
    };

}

# endif
