# ifndef SEMSIM_QUERY_QUERY_H_
# define SEMSIM_QUERY_QUERY_H_


<<<<<<< HEAD
#include <memory>
#include "QueryResults.h"
#include "semsim/SemSimModel.h"
=======
#include <semsim/Model.h>
#include "QueryResults.h"
>>>>>>> ciaran-develop

namespace semsim {

    /**
     * The base class for all queries in libSemSim.
     */
    class Query {
<<<<<<< HEAD
    public:
=======
      public:
>>>>>>> ciaran-develop
        /// Virtual dtor
        virtual ~Query() = default;

        /**
         * Run the query on a model. The model must be passed in as a
         * reference because the return results will contain element references.
         * @param  model The model to run the query on.
         * @return       The query results.
         */
        virtual QueryResults run(SemSimModel &model) const = 0;
    };

    /**
     * An owning pointer for a @ref Query.
     * Automatically uses std::unique_ptr or std::tr1::shared_ptr depending on C++ standard.
     * @see UniquePtr.
     */
<<<<<<< HEAD
    typedef std::unique_ptr<Query> QueryPtr;
=======
    typedef std::unique_ptr<Query>  QueryPtr;
>>>>>>> ciaran-develop

}

# endif
