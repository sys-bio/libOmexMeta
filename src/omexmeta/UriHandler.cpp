//
// Created by Ciaran on 09/11/2020.
//

#include "omexmeta/UriHandler.h"
#include "omexmeta/OmexMetaUtils.h"
#include <regex>

namespace omexmeta {

    const std::string &UriHandler::getRepository() const {
        return repository_;
    }

    UriHandler &UriHandler::setRepository(const std::string &repository) {

        // we need to remember to update the strings that depend on repository_

        if (OmexMetaUtils::endsWith(repository, "/")) {
            model_ = OmexMetaUtils::stringReplace(model_, repository_, repository);
            archive_ = OmexMetaUtils::stringReplace(archive_, repository_, repository);
            local_ = OmexMetaUtils::stringReplace(local_, repository_, repository);
            repository_ = repository;
        } else {
            model_ = OmexMetaUtils::stringReplace(model_, repository_, repository + "/");
            archive_ = OmexMetaUtils::stringReplace(archive_, repository_, repository + "/");
            local_ = OmexMetaUtils::stringReplace(local_, repository_, repository + "/");
            repository_ = repository + "/";
        }
        return *this;
    }

    const std::string &UriHandler::getArchive() const {
        return archive_;
    }
    UriHandler &UriHandler::setArchive(const std::string &archiveName) {
        if (OmexMetaUtils::startsWith(archiveName, "http")) {
            throw std::invalid_argument("std::invalid_argument: RDF::setArchiveUri: "
                                        "Specified \"archiveName\" argument \"" +
                                        archiveName + "\" begins with \"http\". Since the archive url is built "
                                                      "using the repositoryName argument, please only specify "
                                                      "the name of the omex archive. Like \"myOmexFile.omex\"");
        }

        // remove the repository uri section from archive uri
        std::string archive_without_repository = OmexMetaUtils::stringReplace(archive_, repository_, "");

        // now we replace the archive minus repository name part of model and local
        if (OmexMetaUtils::endsWith(archiveName, "/")) {
            model_ = OmexMetaUtils::stringReplace(model_, archive_without_repository, archiveName);
            local_ = OmexMetaUtils::stringReplace(local_, archive_without_repository, archiveName);
            archive_ = repository_ + archiveName + "/";
        } else {
            model_ = OmexMetaUtils::stringReplace(model_, archive_without_repository, archiveName + "/");
            local_ = OmexMetaUtils::stringReplace(local_, archive_without_repository, archiveName + "/");
            archive_ = repository_ + archiveName + "/";

        }

        return *this;
    }

    const std::string &UriHandler::getModel() const {
        return model_;
    }

    UriHandler &UriHandler::setModel(std::string modelName) {
        if (OmexMetaUtils::startsWith(modelName, "http")) {
            throw std::invalid_argument("std::invalid_argument: RDF::setModelUri: "
                                        "Specified \"modelName\" argument \"" +
                                        modelName + "\" begins with \"http\". Since the model url is built "
                                                    "using the repositoryName argument, please only specify "
                                                    "the name of the model. Like \"NewModel.sbml\"");
        }
        // first we make sure the suffix ends with a "#"
        if (!OmexMetaUtils::endsWith(modelName, "#")) {
            modelName += "#";
        }

        // Now we check for file extension
        std::vector<std::string> suffexes = {".xml#", ".sbml#", ".cellml#"};
        bool good = false;
        for (auto &it : suffexes) {
            if (OmexMetaUtils::endsWith(modelName, it)) {
                good = true;
            }
        }
        // automatically add .xml if one of the above suffixes was not detected
        if (!good) {
            // remember to remove the trailing "#"
            modelName.pop_back();
            modelName += ".xml#";
        }

        // concatonate archive and model, being sensitive to ending "/"
        if (OmexMetaUtils::endsWith(getArchive(), "/")) {
            model_ = getArchive() + modelName;
        } else {
            model_ = getArchive() + "/" + modelName;
        }

        // Since the model name is also used for the local name we
        // figure that out here. We know modelName definitely contains
        // a suffux like .xml.
        // we need to remove it so we can add .rdf.
        // We do this in a way that enables multiple "." in a model_name
        std::vector<std::string> split = OmexMetaUtils::splitStringBy(modelName, '.');
        if (split.size() <= 1) {
            throw std::logic_error("std::logic_error: RDF::setModelUri: You should never get a "
                                   "a value less than 2 here because you are splitting a string. "
                                   "If you are seeing this message this is a bug. Please report "
                                   "it as a github issue (https://github.com/sys-bio/libOmexMeta/issues)");
        }
        // remove the last element which should contain the extension.
        split.pop_back();

        // docs-build up the string again with any dots that appeared before the final
        std::ostringstream os;
        for (auto &it : split) {
            os << it << ".";
        }
        // Now we can docs-build up the local string
        if (OmexMetaUtils::endsWith(getArchive(), "/")) {
            local_ = getArchive() + os.str() + "rdf#";
        } else {
            local_ = getArchive() + "/" + os.str() + "rdf#";
        }
        return *this;
    }

    const std::string &UriHandler::getLocal() const {
        return local_;
    }
    std::string UriHandler::uriModifier(std::string uri_to_modify, eUriType type) const {
        switch (type) {
            case UNKNOWN:
                return uri_to_modify;
            case LOCAL:
                return OmexMetaUtils::concatMetaIdAndUri(uri_to_modify, getLocal());
            case MODEL:
                return OmexMetaUtils::concatMetaIdAndUri(uri_to_modify, getModel());
            case IDENTIFIERS:
                return OmexMetaUtils::concatMetaIdAndUri(uri_to_modify, "https://identifiers.org/");
        }


    }


}// namespace omexmeta