# ifndef SEMSIM_QUERY_RASQAL_QUERY_RESULT_H_
# define SEMSIM_QUERY_RASQAL_QUERY_RESULT_H_

# include "semsim/Preproc.h"

# include "raptor2.h"
# include "rasqal.h"

# include <string>
# include <vector>

namespace semsim {

    /**
     * Class for storing the results of a query.
     * @c begin and @c end iterators can be used to access
     * elements returned by the query.
     */
    class SEMSIM_PUBLIC RasqalQueryResult {
      public:
        RasqalQueryResult(rasqal_query_results* results)
          : results_(results) {}
        ~RasqalQueryResult();

        /// Converts the query results to a string
        std::string toString();

        /// Converts the query results to an RDF string
        std::string toRDFString(const std::string& format="rdfxml");

        /// Converts the query results to a list
        std::vector<std::vector<std::string> > asList();

      protected:
        void toRaptorGraph(raptor_world* world, raptor_serializer* serializer);

        rasqal_query_results* results_;
    };

}

# endif
