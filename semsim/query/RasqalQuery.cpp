# include "semsim/query/RasqalQuery.h"

namespace semsim {
    RasqalQuery::RasqalQuery(const std::string& rdf, const std::string& format, bool is_file) {
      rdf_ = rdf;

      rasqal_world_ = rasqal_new_world();
      rasqal_world_open(rasqal_world_);
      raptor_world_ = rasqal_world_get_raptor(rasqal_world_);

      if (!is_file)
        raptor_iostr_ = raptor_new_iostream_from_string(raptor_world_, (void*)rdf_.c_str(), rdf_.size());
      else
        raptor_iostr_ = raptor_new_iostream_from_filename(raptor_world_, (const char*)rdf_.c_str());

      unsigned char* uri_string_ = raptor_uri_filename_to_uri_string("./mymodel.xml");
      uri_ = raptor_new_uri(raptor_world_, uri_string_);
      base_uri_ = raptor_uri_copy(uri_);

      dg_ = rasqal_new_data_graph_from_iostream(
                rasqal_world_,
                raptor_iostr_,
                base_uri_,
                NULL,
                RASQAL_DATA_GRAPH_BACKGROUND,
                NULL,
                (const char*)format.c_str(),
                NULL);
    }

    RasqalQuery::~RasqalQuery() {
    }

    RasqalQueryResult RasqalQuery::run(const std::string& query) {
      query_=rasqal_new_query(rasqal_world_,(const char*)"sparql",NULL);
      const unsigned char* query_string=(const unsigned char*)query.c_str();
      rasqal_query_prepare(query_,query_string,base_uri_);
      rasqal_query_add_data_graph(query_, dg_);
      return RasqalQueryResult(rasqal_query_execute(query_));
    }
}
