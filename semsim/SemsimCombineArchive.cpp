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

semsim::SemsimCombineArchive::SemsimCombineArchive(std::string file_or_uri) : file_or_uri_(std::move(file_or_uri)) {}

bool semsim::SemsimCombineArchive::isfile() {
    struct stat buffer{};
    return (stat(file_or_uri_.c_str(), &buffer) == 0);
}

bool semsim::SemsimCombineArchive::isurl() {
    return false;
}

bool semsim::SemsimCombineArchive::open() {

//    try {
//        fromUrl();
//    } catch (std::exception &e){
//        fromFile();
//    }

}

int semsim::SemsimCombineArchive::fromUrl(const std::string &output_filename) {
    CurlGet::download(file_or_uri_, output_filename);
    CombineArchive combineArchive;
    if (!combineArchive.initializeFromArchive(output_filename)) {
        std::cerr << "Invalid Combine Archive" << std::endl;
        return 1;
    }

}

void semsim::SemsimCombineArchive::fromFile() {

}
























