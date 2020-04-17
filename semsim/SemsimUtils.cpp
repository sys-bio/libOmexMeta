//
// Created by Ciaran on 4/13/2020.
//
#include <sys/stat.h>
#include <stdexcept>
#include <sstream>
#include "SemsimUtils.h"
#include "CurlGet.h"

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