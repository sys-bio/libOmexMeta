//
// Created by Ciaran on 4/13/2020.
//

#ifndef LIBSEMGEN_SEMSIMUTILS_H
#define LIBSEMGEN_SEMSIMUTILS_H

#include <string>

namespace semsim {

    class SemsimUtils {
    public:
        SemsimUtils() = default;

        static bool exists(const std::string &filename);

        static int removeFile(const std::string &filename);

        static void removeIfExists(const std::string &filename);


        static void download(const std::string &url, const std::string filename);
    };
}

#endif //LIBSEMGEN_SEMSIMUTILS_H
