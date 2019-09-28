# include "semsim/query/RasqalQueryResult.h"
# include "semsim/BiomodelsQualifiers.h"
# include "semsim/SemSimQualifiers.h"

# include <sstream>

namespace semsim {
    std::string RasqalQueryResult::toString() {
      std::stringstream ss;
      if (rasqal_query_results_is_boolean(results_)) {
        ss << "Result: " << (rasqal_query_results_get_boolean(results_) ? "True" : "False") << "\n";
      } else if (rasqal_query_results_is_bindings(results_)) {
        while(!rasqal_query_results_finished(results_)) {
          ss << "results (" << rasqal_query_results_get_count(results_) << ")\n";
          for(int i=0;i<rasqal_query_results_get_bindings_count(results_);i++) {
            const unsigned char *name = rasqal_query_results_get_binding_name(results_,i);
            rasqal_literal *value = rasqal_query_results_get_binding_value(results_,i);
            std::string strvalue = (const char*)rasqal_literal_as_string(value);
            ss << "  " << name << " " << strvalue << "\n";
          }
          rasqal_query_results_next(results_);
        }
      } else if (rasqal_query_results_is_graph(results_)) {
        return toRDFString("turtle");
      } else {
        ss << "Cannot display query results_\n";
      }
      return ss.str();
    }

    RasqalQueryResult::~RasqalQueryResult() {
    }

    std::string RasqalQueryResult::toRDFString(const std::string& format) {
      raptor_world* world = raptor_new_world();
      raptor_serializer* serializer = raptor_new_serializer(world, format.c_str());
      if (!serializer)
        throw std::runtime_error("Could not create Raptor serializer for format "+format);

      raptor_uri* base_uri = raptor_new_uri(world, (const unsigned char*)"");

      raptor_serializer_set_namespace(serializer, raptor_new_uri(world, (const unsigned char*)bqb::root.c_str()), (const unsigned char*)"bqb");
      raptor_serializer_set_namespace(serializer, raptor_new_uri(world, (const unsigned char*)semsim::root.c_str()), (const unsigned char*)"semsim");

      void* output;
      size_t length;
      raptor_serializer_start_to_string(serializer, base_uri, &output, &length);

      toRaptorGraph(world, serializer);

      raptor_serializer_serialize_end(serializer);

      raptor_free_serializer(serializer);
      raptor_free_world(world);

      std::string result((char*)output);
      free(output);
      return result;
    }

    void RasqalQueryResult::toRaptorGraph(raptor_world* world, raptor_serializer* serializer) {
      if (rasqal_query_results_is_graph(results_)) {
        do {
          raptor_statement* s = rasqal_query_results_get_triple(results_);
          if (!s)
            break;
          raptor_statement* s2 = raptor_statement_copy(s);
          if(!s2)
            throw std::runtime_error("Could not copy Raptor statement");
          raptor_serializer_serialize_statement(serializer, s2);
          raptor_free_statement(s2);
        } while (!rasqal_query_results_next_triple(results_));
      }
    }

    std::vector<std::vector<std::string> > RasqalQueryResult::asList() {
      std::stringstream ss;
      std::vector< std::vector<std::string> > results;
      if (rasqal_query_results_is_bindings(results_)) {
        while(!rasqal_query_results_finished(results_)) {
          std::vector< std::string > bindings;
          for(int i=0;i<rasqal_query_results_get_bindings_count(results_);i++) {
            const unsigned char *name = rasqal_query_results_get_binding_name(results_,i);
            rasqal_literal *value = rasqal_query_results_get_binding_value(results_,i);
            std::string strvalue = (const char*)rasqal_literal_as_string(value);
            bindings.push_back(strvalue);
          }
          results.push_back(bindings);
          rasqal_query_results_next(results_);
        }
      } else if (rasqal_query_results_is_graph(results_)) {
        throw std::runtime_error("Graph results TODO");
      } else {
        throw std::runtime_error("Cannot display query results");
      }
      return results;
    }
}
