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
          : relation_(relation), resource_(resource), is_value_(false) {}

        # if __cplusplus >= 201103L
        /// Move-construct from a @ref Resource (URI) and @ref Relation
        Term(Relation&& relation, Resource&& resource)
          : relation_(std::move(relation)), resource_(std::move(resource)), is_value_(false) {}
        # endif

        /// Construct from a @ref Resource (URI) and a double value (literal)
        Term(const Relation& relation, const double value)
          : relation_(relation), value_(value), resource_(""), is_value_(true) {}

        /// @return The @ref Resource of this term.
        const Relation& getRelation() const {
          return relation_;
        }

        /// @return The @ref Resource of this term.
        const Resource& getResource() const {
          return resource_;
        }

        std::string toString() const {
          return relation_.toString() + "->" + resource_.toString();
        }

        const bool isValue() const {
          return is_value_;
        }

        const double getValue() const {
          return value_;
        }

      protected:
        Relation relation_;
        Resource resource_;
        bool is_value_;
        double value_;
    };

}

# endif
