//
// Created by Ciaran on 4/13/2020.
//
#include "SemsimUtils.h"

namespace semsim {

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
            const LibrdfModel& model, std::string metaid_base,
            std::vector<std::string> exclusions) {

        std::string q = "SELECT ?subject ?predicate ?object\n"
                        "WHERE {?subject ?predicate ?object}";
        Query query(model, q);
        ResultsMap results_map = query.resultsAsMap();
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

    std::string SemsimUtils::addFilePrefixToString(std::string str) {
        std::string file_prefix = "file://";
        if (str.rfind(file_prefix, 0) == 0) {
            // str already starts with "file://" do nothing
            return str;
        }
        return file_prefix + str;

    }

    std::string SemsimUtils::getNamespaceFromUri(const std::string &uri) {
        std::vector<std::string> vec = splitStringBy(uri, '/');
        vec.pop_back(); // remove last element
        std::ostringstream os;
        // preserve the double slash with http
        os << "http://";
        for (int i = 1; i < vec.size(); i++) {
            os << vec[i] << "/";
        }
        return os.str();
    }

}
