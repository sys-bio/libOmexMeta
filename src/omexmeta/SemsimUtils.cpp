//
// Created by Ciaran on 4/13/2020.
//
#include "SemsimUtils.h"

namespace omexmeta {

    bool SemsimUtils::exists(const std::string &filename) {
        struct stat buffer{};
        return (stat(filename.c_str(), &buffer) == 0);
    }

    int SemsimUtils::removeFile(const std::string &filename) {
        if (!exists(filename)) {
            std::ostringstream os;
            os << "Filename \"" << filename << "\" does not exist, so can't be removed";
            throw std::invalid_argument(os.str());
        }
        return remove(filename.c_str());
    }

    void SemsimUtils::removeIfExists(const std::string &filename) {
        if (SemsimUtils::exists(filename)) {
            SemsimUtils::removeFile(filename);
        }
    }

/*
 * wrapper around the CurlGet function, as the utils
 * class seems like a good place for the download features.
 */
    void SemsimUtils::download(const std::string &url, const std::string filename) {
        CurlGet::download(url, filename);
    }

    std::vector<std::string> SemsimUtils::splitStringBy(const std::string &str, char delimiter) {
        std::vector<std::string> tokens;
        if (str.find(delimiter) == std::string::npos) {
            // return the string in the vector
            tokens.push_back(str);
            return tokens;
        }
        std::string token;
        std::istringstream is(str);
        while (std::getline(is, token, delimiter)) {
            if (!token.empty())
                tokens.push_back(token);
        }
        return tokens;
    }

    std::string SemsimUtils::generateUniqueMetaid(
            librdf_model *model, const std::string &metaid_base,
            const std::vector<std::string> &exclusions) {

        std::string q = "SELECT ?subject ?predicate ?object\n"
                        "WHERE {?subject ?predicate ?object}";
        Query query(model, q);
        ResultsMap results_map = query.resultsAsMap();
        query.freeQuery();
        std::vector<std::string> subjects = results_map["subject"];
        // add other exclusions to the subjects like
        for (auto &i : exclusions) {
            subjects.push_back(i);
        }
        int count = 0;
        std::string metaid;
        while (true) {
            MetaID metaId(metaid_base, count, 4);
            metaid = metaId.generate();
            if (std::find(subjects.begin(), subjects.end(), metaId.generate()) == subjects.end()) {
                break;
            }
            count++;
        }
        return metaid;
    }

    std::string SemsimUtils::prepareBaseUri(std::string str, bool absolute_path) {
        std::string file_prefix = "file://";
        std::string http_protocol = "http://";
        std::string https_protocol = "https://";

        // if the base_uri is a web_uri, we leave it alone
        if (str.rfind(https_protocol, 0) == 0 || str.rfind(http_protocol, 0) == 0) {
            // str already starts with "http://" or "https:// do nothing
            return str;
        }

        // Same if it already starts with a "file:/"
        if (str.rfind(file_prefix, 0) == 0) {
            // str already starts with "file://" do nothing
            return str;
        }

        // swap any backslashes with forward slashes
        std::replace(str.begin(), str.end(), '\\', '/');
        if (absolute_path) {
            // otherwise we use the current working directory as an absolute path
            std::filesystem::path out = std::filesystem::current_path() /= str;
            return "file://" + out.string();
        } else {
            return "file://" + str;
        }
    }

    std::string SemsimUtils::getNamespaceFromUri(const std::string &uri) {
        std::vector<std::string> vec = splitStringBy(uri, '/');
        std::ostringstream os;
        // Uri's we want all begin with http.
        if (vec[0].rfind("http", 0) != 0)
            throw std::invalid_argument("std::invalid_argument: SemsimUtils::getNamespaceFromUri: \"" + vec[0]
                                        + "\". Predicate arguments are URI's, they should begin with \"http\"");

        os << vec[0] + "//"; // we keep the first part and add back the missing '/'

        // iterate from second to penultimate, rebuilding the uri
        for (int i = 1; i < vec.size() - 1; i++) {
            os << vec[i] << "/";
        }
        int last_index = vec.size() - 1;

        // The last element of the list we check for a "#" in namespacebool frag_in_ns = false;
        bool frag_in_ns = false;
        if (vec[last_index].find("#") != std::string::npos) {
            // frag is present
            frag_in_ns = true;
        }
        if (frag_in_ns) {
            std::vector<std::string> split_on_hash = SemsimUtils::splitStringBy(vec[last_index], '#');
            os << split_on_hash[0] << "#"; // remember to put it back
        } else {
//            os << vec[last_index];
        }
        return os.str();
    }

    bool SemsimUtils::isFormattedUri(std::string uri) {
        std::string file_prefix = "file://";
        std::string http_protocol = "http://";
        std::string https_protocol = "https://";

        return uri.rfind(https_protocol, 0) == 0
               || uri.rfind(http_protocol, 0) == 0
               || uri.rfind(file_prefix, 0) == 0;
    }

    bool SemsimUtils::stringHasEnding(const std::string &full_string, const std::string &ending) {
        if (full_string.length() >= ending.length()) {
            return (0 == full_string.compare(full_string.length() - ending.length(), ending.length(), ending));
        } else {
            return false;
        }

    }

    /*
     * @brief test that expected_string matches actual_string when
     * split by new lines and matched as a regex
     */
    bool
    SemsimUtils::assertRegexMatchSplitByNewLine(const std::string &expected_string, const std::string &actual_string) {
        bool all_lines_match = true;
        // split the expected string into lines
        std::vector<std::string> vec = omexmeta::SemsimUtils::splitStringBy(expected_string, '\n');
        // we do search line by line
        for (auto &i : vec) {
            std::regex r(i);
            bool truth = false;
            if (std::regex_search(actual_string, r)) {
                truth = true;
            }
            if (!truth) {
                all_lines_match = false;
                std::cerr << "actual is:\n " << actual_string << "\n" << std::endl;
                std::cerr << "Failed on line\n: \"" << i << "\"" << std::endl;
            }
        }
        return all_lines_match;
//        if (!all_lines_match){
//            throw std::logic_error("std::logic_error: assertRegexMatchSplitByNewLine: The "
//                                   "input string \n\n "
//                                   "" + actual_string +
//                                   " does not match the expected string "
//                                   "line for line");
//        }
    }

    bool
    SemsimUtils::assertMatchByNewLine(const std::string &expected_string, const std::string &actual_string) {
        bool all_lines_match = true;
        // split the expected string into lines
        std::vector<std::string> vec = omexmeta::SemsimUtils::splitStringBy(expected_string, '\n');
        // we do search line by line
        for (auto &i : vec) {
            if (actual_string.find(i) == std::string::npos) {
                // not found.
                all_lines_match = false;
                std::cout << "actual is:\n " << actual_string << "\n" << std::endl;
                std::cout << "Failed on line:\n \"" << i << "\"" << std::endl;
            }
        }
        return all_lines_match;
    }

    std::vector<std::string>
    SemsimUtils::configureSelfStrings(std::string omex_name, std::string model_name) {
        std::vector<std::string> vec;
        // create the default namespaces.
        std::string myomexlib_string = "http://MyOmexLibrary.org/" + omex_name;
        vec.push_back(myomexlib_string);

        // we make myomex_string relative to myomexlib_string
        // logic for adding appropriate extension if not exist
        std::vector<std::string> suffixes = {".xml", ".cellml", ".sbml"};
        bool has_appropriate_extension = false;
        for (auto &it : suffixes) {
            if (SemsimUtils::stringHasEnding(model_name, it)) {
                has_appropriate_extension = true;
                break;
            }
        }

        std::string myomex_string;
        if (has_appropriate_extension) {
            myomex_string = myomexlib_string + +"/" + model_name;
        } else {
            myomex_string = myomexlib_string + "/" + model_name + ".xml";
        }
        vec.push_back(myomex_string);
        assert(!myomex_string.empty());

        // now we know we have a string that definitely contains a suffux like .xml
        // we need to remove it so we can add .rdf.
        // We do this in a way that enables multiple "." in a model_name
        std::vector<std::string> split = SemsimUtils::splitStringBy(model_name, '.');
        if (split.size() <= 1) {
            throw std::logic_error("std::logic_error: Triple::str: You should never get a "
                                   "a value less than 2 here because you are splitting a string. "
                                   "If you are seeing this message this is a bug. Please report "
                                   "it as a github issue (https://github.com/sys-bio/libOmexMeta/issues)");
        }
        // remove the last element which should contain the extension.
        split.erase(split.end());
        std::ostringstream os;
        for (auto &it : split) {
            os << it << ".";
        }

        // Now we can build up the local string
        std::string local_string = myomexlib_string + "/" + os.str() + "rdf#";
        vec.push_back(local_string);
        assert(vec.size() == 3);
        return vec;

    }

    std::string SemsimUtils::addLocalPrefixToMetaid(std::string metaid, const std::string &local) {
        // if metaid already has local in the string, we just return
        if (metaid.find(local) != std::string::npos) {
            return metaid;
        }
        // Otherwise we concatonate:
        // first we check if local has the # at the end. It should do.
        if (!SemsimUtils::stringHasEnding(local, "#")) {
            throw std::invalid_argument("std::invalid_argument: addLocalPrefixToMetaid: "
                                        "Was expecting a local prefix to end with a '#' "
                                        "character, like http://MyOmexLibrary.org/myomexarchive.omex/mymodel.rdf#. "
                                        "Recieved: " + local);
        }
        // if metaid also begins with '#' character, remove it.
        if (metaid.rfind('#', 0) == 0) {
            metaid = metaid.substr(1, metaid.size());
        }
        return local + metaid;
    }

    std::string
    SemsimUtils::stringReplace(std::string str, const std::string &string_to_replace, const std::string &replacement) {
        size_t start_pos = 0;
        while ((start_pos = str.find(string_to_replace, start_pos)) != std::string::npos) {
            str.replace(start_pos, string_to_replace.length(), replacement);
            start_pos += replacement.length();
        }
        return str;
    }


}
