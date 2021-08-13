#include "redland/LibrdfQueryResults.h"
#include "redland/LibrdfNode.h"
#include "redland/LibrdfQuery.h"
#include "redland/Logger.h"

namespace redland {

    LibrdfQueryResults::LibrdfQueryResults(librdf_query_results *query_results, LibrdfQuery *query)
        : RedlandType_query_results(query_results, librdf_free_query_results), query_(query) {
        REDLAND_DEBUG("Instantiated a LibrdfQueryResults instance");
    }

    void LibrdfQueryResults::regenerateQueryResults() {
        if (obj_) {
            librdf_free_query_results(obj_);
            obj_ = librdf_query_execute(query_->obj_, query_->getModel().getWithoutIncrement());
            REDLAND_DEBUG("Regenerated a LibrdfQueryResults instance");
        }
    }


    bool LibrdfQueryResults::isFinished() {
        int failed = librdf_query_results_finished(obj_);
        if (failed) {
            std::cout << failed << std::endl;
        }
        return failed;
    }

    std::vector<LibrdfNode> LibrdfQueryResults::getBindings() {
        const char **names = NULL;
        int num = getBindingsCount();
        std::vector<LibrdfNode> v(num);
        std::vector<librdf_node *> vp(num);
        int failed = librdf_query_results_get_bindings(obj_, NULL, vp.data());
        for (int i = 0; i < num; i++) {
            v[i] = LibrdfNode(vp[i]);
        }
        if (failed) {
            REDLAND_WARN("Failed to get bindings");
            throw std::logic_error("Failed to get bindings");
        }
        regenerateQueryResults();
        return v;
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

    LibrdfStream LibrdfQueryResults::toStream() {
        librdf_stream *s = librdf_query_results_as_stream(obj_);
        regenerateQueryResults();
        return LibrdfStream(s);
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

    std::string LibrdfQueryResults::toString(const std::string &output_format) {
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
        regenerateQueryResults();
        return res;
    }


    int LibrdfQueryResults::next() {
        return librdf_query_results_next(obj_);
    }

    std::string LibrdfQueryResults::getBindingsName(int index) {
        return librdf_query_results_get_binding_name(obj_, index);
    }

    ResultsMap LibrdfQueryResults::map() {
        if (!mapExecuted) {
            // only ever do this once
            mapExecuted = true;
            // configure a data structure for storing the results
            // binding name is x, y, z of sparql query for example.
            for (int i = 0; i < getBindingsCount(); i++) {
                std::string binding_name = getBindingsName(i);
                map_[binding_name] = std::vector<std::string>();
            }

            // iterate over bindings until no more left
            bool done = false;
            while (!done) {
                for (auto &key : map_) {
                    map_[key.first].push_back(getBindingValueByName(key.first));
                }
                int failed = next();
                if (failed) {
                    done = true;
                }
            }
        }
        regenerateQueryResults();
        return map_;
    }

    void LibrdfQueryResults::printQueryResults() {
        for (auto [name, list] : map()) {
            std::cout << name << std::endl;
            for (auto x : list) {
                std::cout << "\t" << x << std::endl;
            }
        }
    }

    std::vector<std::string> LibrdfQueryResults::getValidOutputFormats() const {
        return valid_output_formats_;
    }

    bool LibrdfQueryResults::isGraph() {
        return librdf_query_results_is_graph(obj_);
    }

    std::vector<std::string> LibrdfQueryResults::getBindingsNames() {
        std::vector<std::string> v(getBindingsCount());
        for (int i = 0; i < getBindingsCount(); i++) {
            v[i] = getBindingsName(i);
        }
        return v;
    }


};// namespace redland