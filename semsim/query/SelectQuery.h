# ifndef SEMSIM_QUERY_SELECT_QUERY_H_
# define SEMSIM_QUERY_SELECT_QUERY_H_

# include "semsim/query/Condition.h"

namespace semsim {

    /**
     * A query to select a subset of elements of a model
     * based on certain criteria.
     */
    class SEMSIM_PUBLIC SelectQuery {
      public:
        # if __cplusplus >= 201103L
        /// Construct from given where-clause.
        SelectQuery(ConditionPtr&& where)
          : where_(std::move(where)) {}
        # endif

      protected:
        ConditionPtr where_;
    };

}

# endif
