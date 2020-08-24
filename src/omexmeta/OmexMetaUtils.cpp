//
// Created by Ciaran on 4/13/2020.
//
#include "OmexMetaUtils.h"

namespace omexmeta {

    bool OmexMetaUtils::exists(const std::string &filename) {
        struct stat buffer{};
        return (stat(filename.c_str(), &buffer) == 0);
    }

    int OmexMetaUtils::removeFile(const std::string &filename) {
        if (!exists(filename)) {
            std::ostringstream os;
            os << "Filename \"" << filename << "\" does not exist, so can't be removed";
            throw std::invalid_argument(os.str());
        }
        return remove(filename.c_str());
    }

    void OmexMetaUtils::removeIfExists(const std::string &filename) {
        if (OmexMetaUtils::exists(filename)) {
            OmexMetaUtils::removeFile(filename);
        }
    }

/*
 * wrapper around the CurlGet function, as the utils
 * class seems like a good place for the download features.
 */
    void OmexMetaUtils::download(const std::string &url, const std::string filename) {
        CurlGet::download(url, filename);
    }

    std::vector<std::string> OmexMetaUtils::splitStringBy(const std::string &str, char delimiter) {
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

    bool OmexMetaUtils::isSubString(const std::string &full_string, const std::string &substring) {
        if (full_string.find(substring) != std::string::npos) {
            return true;
        }
        return false;
    }

    std::string OmexMetaUtils::generateUniqueMetaid(
            librdf_model *model, const std::string &metaid_base,
            const std::vector<std::string> &exclusions,
            const std::string &local_uri) {

        std::string q = "SELECT ?subject ?predicate ?object\n"
                        "WHERE {?subject ?predicate ?object}";
        Query query(model, q);
        ResultsMap results_map = query.resultsAsMap();
        query.freeQuery();
        std::vector<std::string> subjects = results_map["subject"];
        // add other exclusions to subjects
        for (auto &i : exclusions) {
            subjects.push_back(i);
        }

        // Because we added the "local_uri" stuff ad hock,
        // we introduced a bug with generation of metaids.
        // namely that comparison is done before adding the
        // local uri. Therefore here, we do post processing
        // on subject elements to remove the local uri portion
        for (int i = 0; i < subjects.size(); i++) {
            std::string sub = subjects[i];
            if (OmexMetaUtils::startsWith(sub, "http")) {
//                LOG_DEBUG("subject string that starts with http: %s %s %s", sub.c_str(), results_map["predicate"][i].c_str(), results_map["object"][i].c_str());
                auto v = OmexMetaUtils::splitStringBy(sub, '#');
                assert(v.size() == 2);
                subjects[i] = "#" + v[1];
            }
        }

        int count = 0;
        std::string metaid;
        while (true) {
            MetaID metaId(metaid_base, count, 4);
            metaid = metaId.generate();
            if (std::find(subjects.begin(), subjects.end(), metaid) == subjects.end()) {
                break; // not found existing metaid
            }
            count++;
        }

        return metaid;
    }

    std::string OmexMetaUtils::prepareBaseUri(std::string str, bool absolute_path) {
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

    std::string OmexMetaUtils::getNamespaceFromUri(const std::string &uri) {
        std::vector<std::string> vec = splitStringBy(uri, '/');
        std::ostringstream os;
        // Uri's we want all begin with http.
        if (vec[0].rfind("http", 0) != 0)
            throw std::invalid_argument("std::invalid_argument: OmexMetaUtils::getNamespaceFromUri: \"" + vec[0]
                                        + R"(". Predicate arguments are URI's, they should begin with "http")");

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
            std::vector<std::string> split_on_hash = OmexMetaUtils::splitStringBy(vec[last_index], '#');
            os << split_on_hash[0] << "#"; // remember to put it back
        } else {
//            os << vec[last_index];
        }
        return os.str();
    }

    bool OmexMetaUtils::isFormattedUri(std::string uri) {
        std::string file_prefix = "file://";
        std::string http_protocol = "http://";
        std::string https_protocol = "https://";

        return uri.rfind(https_protocol, 0) == 0
               || uri.rfind(http_protocol, 0) == 0
               || uri.rfind(file_prefix, 0) == 0;
    }

    bool OmexMetaUtils::endsWith(const std::string &full_string, const std::string &ending) {
        if (full_string.length() >= ending.length()) {
            return (0 == full_string.compare(full_string.length() - ending.length(), ending.length(), ending));
        } else {
            return false;
        }
    }

    bool OmexMetaUtils::startsWith(const std::string &full_string, const std::string &start) {
        return full_string.rfind(start) == 0;
    }

    /*
     * @brief test that expected_string matches actual_string when
     * split by new lines and matched as a regex
     */
    bool
    OmexMetaUtils::assertRegexMatchSplitByNewLine(const std::string &expected_string,
                                                  const std::string &actual_string) {
        bool all_lines_match = true;
        // split the expected string into lines
        std::vector<std::string> vec = omexmeta::OmexMetaUtils::splitStringBy(expected_string, '\n');
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
    }

    bool
    OmexMetaUtils::assertMatchByNewLine(const std::string &expected_string, const std::string &actual_string) {
        bool all_lines_match = true;
        // split the expected string into lines
        std::vector<std::string> vec = omexmeta::OmexMetaUtils::splitStringBy(expected_string, '\n');
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
    OmexMetaUtils::configurePrefixStrings(std::string repository_name, std::string omex_name, std::string model_name) {
        std::vector<std::string> vec;
        if (!OmexMetaUtils::endsWith(repository_name, "/")) {
            repository_name += "/";
        }

        if (!OmexMetaUtils::endsWith(omex_name, ".omex/")) {
            throw std::invalid_argument("Input to omex_name argument must end in \".omex/\"");
        }

        std::string OMEXlib_string = repository_name;
        vec.push_back(OMEXlib_string);

        if (!OmexMetaUtils::endsWith(model_name, "#")) {
            model_name += "#";
        }

        std::string myomex_string = OMEXlib_string + omex_name;
        vec.push_back(myomex_string);
        assert(!myomex_string.empty());
        // now we know we have a string that definitely contains a suffux like .xml
        // we need to remove it so we can add .rdf.
        // We do this in a way that enables multiple "." in a model_name
        std::vector<std::string> split = OmexMetaUtils::splitStringBy(model_name, '.');
        if (split.size() <= 1) {
            throw std::logic_error("std::logic_error: Triple::str: You should never get a "
                                   "a value less than 2 here because you are splitting a string. "
                                   "If you are seeing this message this is a bug. Please report "
                                   "it as a github issue (https://github.com/sys-bio/libOmexMeta/issues)");
        }
        // remove the last element which should contain the extension.
        split.pop_back();
        std::ostringstream os;
        for (auto &it : split) {
            os << it << ".";
        }

        // Now we can build up the local string
        std::string local_string = myomex_string + os.str() + "rdf#";
        vec.push_back(local_string);
        assert(vec.size() == 3);
        return vec;

    }

    std::string OmexMetaUtils::concatMetaIdAndUri(std::string metaid, std::string uri) {
        // if metaid already has uri in the string, we just return
        if (metaid.find(uri) != std::string::npos) {
            return metaid;
        }
        // if metaid is already a uri, we throw an error as doing this is
        // probably not what you want
        if (OmexMetaUtils::startsWith(metaid, "http")) {
            std::ostringstream err;
            err << "Cannot concatonate metaid \"" << metaid << "\"and uri \"" << uri << "\" because ";
            err << "metaid is already a uri" << std::endl;
            throw std::logic_error("std::logic_error: OmexMetaUtils::startsWith() " + err.str());
        }

        // Otherwise we concatonate:
        // first we check if uri has the # at the end. It should do.
        if (!OmexMetaUtils::endsWith(uri, "#")) {
            uri = uri + "#";
        }
        // if metaid also begins with '#' character, remove it.
        if (metaid.rfind('#', 0) == 0) {
            metaid = metaid.substr(1, metaid.size());
        }
        return uri + metaid;
    }

    std::string
    OmexMetaUtils::stringReplace(std::string str, const std::string &string_to_replace,
                                 const std::string &replacement) {
        size_t start_pos = 0;
        while ((start_pos = str.find(string_to_replace, start_pos)) != std::string::npos) {
            str.replace(start_pos, string_to_replace.length(), replacement);
            start_pos += replacement.length();
        }
        return str;
    }

    /*
     * @brief return true if @param string is in @param vec
     */
    bool OmexMetaUtils::stringInVector(std::vector<std::string> vec, const std::string &string) {
        return std::find(vec.begin(), vec.end(), string) != vec.end();
    }

    /*
     * @brief read an xml document using libxml2.
     * @return xmlDoc*. Caller is responsible for calling xmlFreeDoc(doc).
     */
    xmlDoc *OmexMetaUtils::parseXmlDocument(const std::string &xml_string) {
        xmlDoc *doc_ = xmlReadMemory(xml_string.c_str(), (int) xml_string.length() + 1, "noname.xml", nullptr, 0);
        if (doc_ == nullptr) {
            throw NullPointerException(
                    "NullPointerException: OmexMetaUtils::parseXmlDocument: Could not read xml into document. nullptr");
        }
        return doc_;
    }

    std::string OmexMetaUtils::getXmlNodeProperty(xmlNode *node, const std::string &property) {

        char *s = (char *) xmlGetProp(node, (const xmlChar *) property.c_str());
        if (s == nullptr) {
            std::ostringstream os;
            os << "xmlNode* with element tag \"" << (const char *) node->name << "\" does not have a property";
            os << "by the name of \"" << property << "\"";
            throw std::logic_error(os.str());
        }
        std::string value(s);
        free(s);
        return value;
    }

    xmlNode *OmexMetaUtils::getChildElementCalled(xmlNode *node, const std::string &name) {
        unsigned long count = xmlChildElementCount(node);
        xmlNode *child = xmlFirstElementChild(node);
        for (int i = 0; i < count - 1; i++) {
            if (strcmp((const char *) child->name, name.c_str()) == 0) {
                return child;
            }
            child = xmlNextElementSibling(child);
        }
        return nullptr;
    }

    std::vector<xmlNode *> OmexMetaUtils::getAllChildElements(xmlNode *node) {
        std::vector<xmlNode *> v;
        unsigned long count = xmlChildElementCount(node);
        xmlNode *child = xmlFirstElementChild(node);
        if (child == nullptr) {
            return v;
        }
        v.push_back(child);
        for (int i = 0; i < count - 1; i++) {
            child = xmlNextElementSibling(child);
            if (child == nullptr)
                break;
            v.push_back(child);
        }
        return v;
    }


}
