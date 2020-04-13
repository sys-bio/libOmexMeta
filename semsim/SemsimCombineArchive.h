//
// Created by Ciaran on 4/11/2020.
//

#ifndef LIBSEMGEN_SEMSIMCOMBINEARCHIVE_H
#define LIBSEMGEN_SEMSIMCOMBINEARCHIVE_H


#include <string>
#include <third_party/libCombine-0.2.3/INSTALL/include/combine/combinearchive.h>
#include "semsim/CurlGet.h"

namespace semsim {

/*
 * duck typed CombineArchive with a few additional
 * methods for getting from url
 */
//    class SemsimCombineArchive {
//    private:
//        CombineArchive archive_;
//
//    public:
//
//        SemsimCombineArchive() = default;
//
//        ~SemsimCombineArchive();
//
//        SemsimCombineArchive(const SemsimCombineArchive &semsimCombineArchive);
//
//        SemsimCombineArchive(SemsimCombineArchive &&semsimCombineArchive) noexcept;
//
//        SemsimCombineArchive &operator=(const SemsimCombineArchive &semsimCombineArchive);
//
//        SemsimCombineArchive &operator=(SemsimCombineArchive &&semsimCombineArchive) noexcept;
//
//
//        static semsim::SemsimCombineArchive fromUrl(const std::string &url, const std::string &output_filename);
//
//        static SemsimCombineArchive fromFile(const std::string &file);
//
//        void printMetaData(const std::string &location);
//
//        const CombineArchive &getArchive() const;
//
//        void setArchive(const CombineArchive &archive);
//
//        void cleanUp();
//
//    };

    class SemsimCombineArchive : public CombineArchive {
    public:
        using CombineArchive::CombineArchive;

        static semsim::SemsimCombineArchive fromUrl(const std::string &url, const std::string &output_filename);

        static SemsimCombineArchive fromFile(const std::string &file);

    };
}

#endif //LIBSEMGEN_SEMSIMCOMBINEARCHIVE_H
