//
// Created by Ciaran on 4/11/2020.
//

#include "semsim/SemsimCombineArchive.h"
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <utility>
#include "CurlGet.h"
#include "combine/combinearchive.h"
#include "semsim/SemSim.h"

//void semsim::SemsimCombineArchive::printMetaData(const std::string &location) {
//    OmexDescription desc = archive_.getMetadataForLocation(location);
//    if (desc.isEmpty()) {
//        std::cout << "  no metadata for '" << location << "'" << std::endl;
//        exit(0);
//    }
//    std::cout << "  metadata for '" << location << "':" << std::endl;
//    std::cout << "     Created : " << desc.getCreated().getDateAsString() << std::endl;
//    for (unsigned int i = 0; i < desc.getNumModified(); ++i) {
//        std::cout << "     Modified : " << desc.getModified(i).getDateAsString() << std::endl;
//    }
//
//    std::cout << "     # Creators: " << desc.getNumCreators() << std::endl;
//    for (unsigned int i = 0; i < desc.getNumCreators(); ++i) {
//        VCard creator = desc.getCreator(i);
//        std::cout << "       " << creator.getGivenName() << " " << creator.getFamilyName() << std::endl;
//    }
//
//}
//
semsim::SemsimCombineArchive
semsim::SemsimCombineArchive::fromUrl(const std::string &url, const std::string &output_filename) {
    // todo check if file exists and is not the same size, only then do the download
    HERE();
    CurlGet::download(url, output_filename);
    HERE();
    SemsimCombineArchive semsimCombineArchive;
    HERE();
    CombineArchive combineArchive;
    HERE();
    if (!combineArchive.initializeFromArchive(output_filename)) {
        std::cerr << __FILE__ << ":" << __LINE__ << "Invalid Combine Archive" << std::endl;
    }
    HERE();
//    semsimCombineArchive.setArchive(combineArchive);
    HERE();

    return semsimCombineArchive;

}


semsim::SemsimCombineArchive semsim::SemsimCombineArchive::fromFile(const std::string &file) {
    CombineArchive combineArchive;
    if (!combineArchive.initializeFromArchive(file)) {
        std::cerr << "Invalid Combine Archive" << std::endl;
    }
    SemsimCombineArchive semsimCombineArchive;
//    semsimCombineArchive.setArchive(combineArchive);

    return semsimCombineArchive;

}
//
//
//const CombineArchive &semsim::SemsimCombineArchive::getArchive() const {
//    return archive_;
//}
//
//void semsim::SemsimCombineArchive::setArchive(const CombineArchive &archive) {
//    archive_ = archive;
//}
//
//semsim::SemsimCombineArchive::~SemsimCombineArchive() {
//    archive_.cleanUp();
//}
//
//semsim::SemsimCombineArchive::SemsimCombineArchive(const semsim::SemsimCombineArchive &semsimCombineArchive) {
//    archive_ = semsimCombineArchive.archive_;
//
//}
//
//semsim::SemsimCombineArchive::SemsimCombineArchive(semsim::SemsimCombineArchive &&semsimCombineArchive) noexcept {
//    archive_ = semsimCombineArchive.archive_;
//
//}
//
//semsim::SemsimCombineArchive &
//semsim::SemsimCombineArchive::operator=(const semsim::SemsimCombineArchive &semsimCombineArchive) = default;
//
//semsim::SemsimCombineArchive &
//semsim::SemsimCombineArchive::operator=(semsim::SemsimCombineArchive &&semsimCombineArchive) noexcept {
//    archive_ = semsimCombineArchive.archive_;
//    return *this;
//}
//
//void semsim::SemsimCombineArchive::cleanUp() {
//    archive_.cleanUp();
//}
//
























