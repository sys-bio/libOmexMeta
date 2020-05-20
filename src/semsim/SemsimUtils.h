//
// Created by Ciaran on 4/13/2020.
//

#ifndef LIBSEMSIM_SEMSIMUTILS_H
#define LIBSEMSIM_SEMSIMUTILS_H

#include "semsim/Query.h"
#include "semsim/CurlGet.h"
#include "semsim/MetaID.h"

#include <librdf.h>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <stdexcept>
#include <sstream>



namespace semsim {

    class SemsimUtils {
    public:
        SemsimUtils() = default;

        static bool exists(const std::string &filename);

        static int removeFile(const std::string &filename);

        static void removeIfExists(const std::string &filename);

        static void download(const std::string &url, std::string filename);

        static std::vector<std::string> splitStringBy(const std::string &str, char delimiter);

        static std::string generateUniqueMetaid(
                LibrdfWorld world, LibrdfModel model, std::string metaid_base,
                std::vector<std::string> exclusions = std::vector<std::string>()
        );

        static std::string addFilePrefixToString(std::string str);

    };
}

#endif //LIBSEMSIM_SEMSIMUTILS_H
