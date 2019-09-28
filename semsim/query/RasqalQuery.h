# ifndef SEMSIM_QUERY_RASQAL_QUERY_H_
# define SEMSIM_QUERY_RASQAL_QUERY_H_

# include "semsim/Preproc.h"
# include "semsim/query/RasqalQueryResult.h"

# include "raptor2.h"
# include "rasqal.h"

# include <string>

namespace semsim {

    /**
     * Class for storing the results of a query.
     * @c begin and @c end iterators can be used to access
     * elements returned by the query.
     */
    class SEMSIM_PUBLIC RasqalQuery {
      public:
        RasqalQuery(const std::string& rdf, const std::string& format="turtle", bool is_file=false);
        ~RasqalQuery();

        RasqalQueryResult run(const std::string& query);
      protected:
        std::string rdf_;
        rasqal_world* rasqal_world_;
        raptor_world* raptor_world_;
        raptor_iostream* raptor_iostr_;
        rasqal_data_graph* dg_;
        raptor_uri* uri_;
        raptor_uri* base_uri_;
        unsigned char* uri_string_;
        rasqal_query* query_;
    };

}

# endif
