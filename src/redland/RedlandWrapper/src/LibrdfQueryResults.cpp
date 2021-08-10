#include "redland/LibrdfQueryResults.h"
#include "redland/LibrdfNode.h"

namespace redland {

    LibrdfQueryResults::LibrdfQueryResults(librdf_query_results *query_results)
        : RedlandType_query_results(query_results, librdf_free_query_results) {}

    std::string LibrdfQueryResults::str(std::string format) {
        return std::string();
    }

    bool LibrdfQueryResults::isBoolean() {
        return librdf_query_results_is_boolean(obj_);
    }

    bool LibrdfQueryResults::isBindings() {
        return librdf_query_results_is_bindings(obj_);
    }

    int LibrdfQueryResults::getBoolean() {
        return librdf_query_results_get_boolean(obj_);
    }

    librdf_stream *LibrdfQueryResults::resultsAsLibRdfStream() {
        return librdf_query_results_as_stream(obj_);
    }

    int LibrdfQueryResults::getCount() {
        return librdf_query_results_get_count(obj_);
    }

    std::string LibrdfQueryResults::getBindingValueByName(const std::string &name) {
        librdf_node *n = librdf_query_results_get_binding_value_by_name(
                obj_, (const char *) name.c_str());
        if (n) {
            LibrdfNode node(n);
            std::string s = node.str();
            return s;
        }
        return {};
    }

    int LibrdfQueryResults::getBindingsCount() {
        return librdf_query_results_get_bindings_count(obj_);
    }

    std::string LibrdfQueryResults::stringReplace(
            std::string str, const std::string &string_to_replace, const std::string &replacement) {
        size_t start_pos = 0;
        while ((start_pos = str.find(string_to_replace, start_pos)) != std::string::npos) {
            str.replace(start_pos, string_to_replace.length(), replacement);
            start_pos += replacement.length();
        }
        return str;
    }

    std::string LibrdfQueryResults::toString(const std::string &output_format) const {
        if (std::find(valid_output_formats_.begin(), valid_output_formats_.end(), output_format) ==
            valid_output_formats_.end()) {
            std::ostringstream err;
            err << __FILE__ << ":" << __LINE__ << ": requested output format \"" << output_format << "\"";
            err << "is not valid. These formats are valid: ";
            for (auto &it : valid_output_formats_) {
                err << it << ", ";
            }
            err << std::endl;
            throw std::invalid_argument(err.str());
        }
        //        LibrdfUri uri(baseuri);
        unsigned char *s = librdf_query_results_to_string2(
                obj_, output_format.c_str(),
                nullptr, nullptr, nullptr);
        std::string res = (const char *) s;// makes a copy
        // the above string using \r\n for line endings. Convert to \n like any sane program should.
        res = stringReplace(res, "\r\n", "\n");
        free(s);
        return res;
    }


    int LibrdfQueryResults::next() {
        return librdf_query_results_next(obj_);
    }

    std::string LibrdfQueryResults::getBindingsName(int index) {
        return librdf_query_results_get_binding_name(obj_, index);
    }

    ResultsMap LibrdfQueryResults::resultsAsMap() {
        ResultsMap map;
        // configure a data structure for storing the results
        // binding name is x, y, z of sparql query for example.
        for (int i = 0; i < getBindingsCount(); i++) {
            std::string binding_name = getBindingsName(i);
            map[binding_name] = std::vector<std::string>();
        }

        // iterate over bindings until no more left
        bool done = false;
        while (!done) {
            for (auto &key : map) {
                map[key.first].push_back(getBindingValueByName(key.first));
            }
            int failed = next();
            if (failed) {
                done = true;
            }
        }
//        // we rerun the query to overwrite the serializer_
//        // variable with a fresh object (since once you've
//        // hit the end you can't seem to go back).
//        // todo look more into this.
//        runQuery();
        return map;
    }


    //    void LibrdfQueryResults::printQueryResults() {
    //        auto results = resultsAsMap();
    //        for (auto [name, list] : results) {
    //            std::cout << name << std::endl;
    //            for (auto x : list) {
    //                std::cout << "\t" << x << std::endl;
    //            }
    //        }
    //    }

    std::vector<std::string> LibrdfQueryResults::getValidOutputFormats() const {
        return valid_output_formats_;
    }
};// namespace redland