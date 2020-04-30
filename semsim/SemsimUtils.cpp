//
// Created by Ciaran on 4/13/2020.
//
#include <sys/stat.h>
#include <stdexcept>
#include <sstream>
#include <librdf.h>
#include "SemsimUtils.h"
#include "CurlGet.h"
#include "Query.h"
#include "MetaID.h"

bool semsim::SemsimUtils::exists(const std::string &filename) {
    struct stat buffer{};
    return (stat(filename.c_str(), &buffer) == 0);
}

int semsim::SemsimUtils::removeFile(const std::string &filename) {
    if (!exists(filename)) {
        std::ostringstream os;
        os << "Filename \"" << filename << "\" does not exist, so can't be removed";
        throw std::invalid_argument(os.str());
    }
    return remove(filename.c_str());
}

void semsim::SemsimUtils::removeIfExists(const std::string &filename) {
    if (semsim::SemsimUtils::exists(filename)) {
        semsim::SemsimUtils::removeFile(filename);
    }
}

/*
 * wrapper around the CurlGet function, as the utils
 * class seems like a good place for the download features.
 */
void semsim::SemsimUtils::download(const std::string &url, const std::string filename) {
    semsim::CurlGet::download(url, filename);
}

std::vector<std::string> semsim::SemsimUtils::splitStringBy(const std::string &str, char delimiter) {
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

std::string semsim::SemsimUtils::generateUniqueMetaid(
        librdf_world *world, librdf_model *model, std::string metaid_base) {

    std::string q = "SELECT ?subject ?predicate ?object\n"
                    "WHERE {?subject ?predicate ?object}";
    Query query(world, model, q);
    ResultsMap results_map = query.resultsAsMap();
    std::vector<std::string> subjects = results_map["subject"];
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


