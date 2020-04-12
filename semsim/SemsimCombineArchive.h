//
// Created by Ciaran on 4/11/2020.
//

#ifndef LIBSEMGEN_SEMSIMCOMBINEARCHIVE_H
#define LIBSEMGEN_SEMSIMCOMBINEARCHIVE_H


#include <string>
#include "semsim/CurlGet.h"

namespace semsim {

/*
 * duck typed CombineArchive with a few additional
 * methods for getting from url
 */
    class SemsimCombineArchive {
    private:
        std::string file_or_uri_;

        bool isfile();

        bool isurl();

        void fromFile();

    public:

        explicit SemsimCombineArchive(std::string file_or_uri);

        bool open();

        int fromUrl(const std::string &output_filename);
    };
}

#endif //LIBSEMGEN_SEMSIMCOMBINEARCHIVE_H
