//
// Created by Ciaran on 09/11/2020.
//

#include "omexmeta/UriHandler.h"
#include "omexmeta/OmexMetaUtils.h"
#include <regex>

namespace omexmeta {

    const std::string &UriHandler::getRepositoryUri() const {
        return repository_uri_;
    }

    UriHandler &UriHandler::setRepositoryUri(const std::string &repository) {

        // we need to remember to update the strings that depend on repository_

        if (OmexMetaUtils::endsWith(repository, "/")) {
            model_uri_ = OmexMetaUtils::stringReplace(model_uri_, repository_uri_, repository);
            archive_uri_ = OmexMetaUtils::stringReplace(archive_uri_, repository_uri_, repository);
            local_uri_ = OmexMetaUtils::stringReplace(local_uri_, repository_uri_, repository);
            repository_uri_ = repository;
        } else {
            model_uri_ = OmexMetaUtils::stringReplace(model_uri_, repository_uri_, repository + "/");
            archive_uri_ = OmexMetaUtils::stringReplace(archive_uri_, repository_uri_, repository + "/");
            local_uri_ = OmexMetaUtils::stringReplace(local_uri_, repository_uri_, repository + "/");
            repository_uri_ = repository + "/";
        }
        return *this;
    }

    const std::string &UriHandler::getArchiveUri() const {
        return archive_uri_;
    }
    UriHandler &UriHandler::setArchiveUri(const std::string &archive) {
        if (OmexMetaUtils::startsWith(archive, "http")) {
            throw std::invalid_argument("std::invalid_argument: RDF::setArchiveUri: "
                                        "Specified \"archiveName\" argument \"" +
                                        archive + "\" begins with \"http\". Since the archive url is built "
                                                      "using the repositoryName argument, please only specify "
                                                      "the name of the omex archive. Like \"myOmexFile.omex\"");
        }

        // remove the repository uri section from archive uri
        std::string archive_without_repository = OmexMetaUtils::stringReplace(archive_uri_, repository_uri_, "");

        // now we replace the archive minus repository name part of model and local
        if (OmexMetaUtils::endsWith(archive, "/")) {
            model_uri_ = OmexMetaUtils::stringReplace(model_uri_, archive_without_repository, archive);
            local_uri_ = OmexMetaUtils::stringReplace(local_uri_, archive_without_repository, archive);
            archive_uri_ = repository_uri_ + archive + "/";
        } else {
            model_uri_ = OmexMetaUtils::stringReplace(model_uri_, archive_without_repository, archive + "/");
            local_uri_ = OmexMetaUtils::stringReplace(local_uri_, archive_without_repository, archive + "/");
            archive_uri_ = repository_uri_ + archive + "/";

        }

        return *this;
    }

    const std::string &UriHandler::getModelUri() const {
        return model_uri_;
    }

    UriHandler &UriHandler::setModelUri(std::string model) {
        if (OmexMetaUtils::startsWith(model, "http")) {
            throw std::invalid_argument("std::invalid_argument: RDF::setModelUri: "
                                        "Specified \"modelName\" argument \"" +
                                        model + "\" begins with \"http\". Since the model url is built "
                                                    "using the repositoryName argument, please only specify "
                                                    "the name of the model. For example \"NewModel.sbml\"");
        }
        // first we make sure the suffix ends with a "#"

        // Now we check for file extension
        std::vector<std::string> suffexes = {".xml", ".sbml", ".cellml"};
        bool good = false;
        for (auto &it : suffexes) {
            if (OmexMetaUtils::endsWith(model, it)) {
                good = true;
            }
        }
        // automatically add .xml if one of the above suffixes was not detected
        if (!good) {
            // remember to remove the trailing "#"
            model += ".xml";
        }

        // concatonate archive and model, being sensitive to ending "/"
        if (OmexMetaUtils::endsWith(getArchiveUri(), "/")) {
            model_uri_ = getArchiveUri() + model;
        } else {
            model_uri_ = getArchiveUri() + "/" + model;
        }

        // Since the model name is also used for the local name we
        // figure that out here. We know modelName definitely contains
        // a suffux like .xml.
        // we need to remove it so we can add .rdf.
        // We do this in a way that enables multiple "." in a model_name
        std::vector<std::string> split = OmexMetaUtils::splitStringBy(model, '.');
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
        if (OmexMetaUtils::endsWith(getArchiveUri(), "/")) {
            local_uri_ = getArchiveUri() + os.str() + "rdf#";
        } else {
            local_uri_ = getArchiveUri() + "/" + os.str() + "rdf#";
        }
        return *this;
    }

    const std::string &UriHandler::getLocalUri() const {
        return local_uri_;
    }
    std::string UriHandler::uriModifier(std::string uri_to_modify, eUriType type) const {
        switch (type) {
            case NONE:
                return uri_to_modify;
            case LOCAL_URI:
                return OmexMetaUtils::concatMetaIdAndUri(uri_to_modify, getLocalUri());
            case MODEL_URI:
                return OmexMetaUtils::concatMetaIdAndUri(uri_to_modify, getModelUri());
            case IDENTIFIERS_URI:
                return OmexMetaUtils::concatMetaIdAndUri(uri_to_modify, "https://identifiers.org/");
        }
        throw std::logic_error("UriHandler::uriModifier: unrecognized eUriType");
    }

    bool UriHandler::operator==(const UriHandler &rhs) const {
        return repository_uri_ == rhs.repository_uri_ &&
               archive_uri_ == rhs.archive_uri_ &&
               model_uri_ == rhs.model_uri_ &&
               local_uri_ == rhs.local_uri_;
    }
    bool UriHandler::operator!=(const UriHandler &rhs) const {
        return !(rhs == *this);
    }


}// namespace omexmeta