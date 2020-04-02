# ifndef SEMSIM_TERM_H_
# define SEMSIM_TERM_H_


# include "semsim/Resource.h"

# include <string>

namespace semsim {

    /**
     * A term contains a qualifier and a resource.
     * The qualifier is typically one of the BioModels qualifiers.
     */
    class  Term {
    public:
        /// Construct from a @ref Resource (URI) and @ref Relation
        Term(Relation &relation, Resource &resource)
                : relation_(relation), resource_(resource), is_value_(false) {}

        /// Construct from a @ref Resource (URI) and a double value (literal)
        Term(Relation &relation, double value)
                : relation_(relation),  resource_(Url("")), value_(value), is_value_(true) {}

        /// @return The @ref Resource of this term.
         Relation &getRelation()  {
            return relation_;
        }

        /// @return The @ref Resource of this term.
         Resource &getResource()  {
            return resource_;
        }

        std::string toString()  {
            return relation_.toString() + "->" + resource_.toString();
        }

        bool isValue()  {
            return is_value_;
        }

        double getValue()  {
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
