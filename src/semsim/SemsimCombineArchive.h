//
// Created by Ciaran on 4/11/2020.
//

#ifndef LIBSEMGEN_SEMSIMCOMBINEARCHIVE_H
#define LIBSEMGEN_SEMSIMCOMBINEARCHIVE_H


#include <string>
#include <third_party/libCombine-0.2.3/INSTALL/include/combine/combinearchive.h>
#include "CurlGet.h"

/*
 * Food for thought:
 *
 * In the future libcombine would probably want to
 * rip out its existing annotation support and replace
 * it with the features provided by libsesim. Therefore
 * libcombine will want to depend on libsemsim. If this
 * is the same then it might not be such a great idea to
 * have libsemsim depend on libcombine.
 *
 * Future developers should consider working together
 * with libcombine developers to present a unified
 * and well structured interface for annotation.
 *
 *
 */

namespace semsim {


    class SemsimCombineArchive : public CombineArchive {
    public:
        using CombineArchive::CombineArchive;

        static semsim::SemsimCombineArchive fromUrl(const std::string &url, const std::string &output_filename);

        static SemsimCombineArchive fromFile(const std::string &file);

    };
}

#endif //LIBSEMGEN_SEMSIMCOMBINEARCHIVE_H
