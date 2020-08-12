//
// Created by Ciaran on 4/13/2020.
//

#ifndef LIBOMEXMETA_OMEXMETAUTILS_H
#define LIBOMEXMETA_OMEXMETAUTILS_H

#include "omexmeta/Query.h"
#include "omexmeta/CurlGet.h"
#include "omexmeta/MetaID.h"

#include "LibrdfQuery.h"

#include <librdf.h>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <stdexcept>
#include <sstream>
#include <filesystem>
#include <assert.h>
#include "libxml/tree.h"

using namespace redland;

namespace omexmeta {

    class OmexMetaUtils {
    public:
        OmexMetaUtils() = default;

        static bool exists(const std::string &filename);

        static int removeFile(const std::string &filename);

        static void removeIfExists(const std::string &filename);

        static void download(const std::string &url, std::string filename);

        static std::vector<std::string> splitStringBy(const std::string &str, char delimiter);

        /*
         * @brief utility for generating unique metaids given an xml document
         * @brief model a librdf_model* pointer
         * @brief a string that will be used for the ID. There will be 4 digits, though this can be changed.
         * @brief exclusions. Mostly needed internally for dealing with metaids that already exist.
         */
        static std::string generateUniqueMetaid(
                librdf_model *model, const std::string &metaid_base,
                const std::vector<std::string> &exclusions = std::vector<std::string>(),
                const std::string& local_uri = std::string()
        );

        /*
         * @brief process a string intended to be a base uri.
         * @param str The string that will become a base uri
         * @param absolute_path automatically make str an absolute path to the current
         * working directory.
         *
         * Base uri's are important in redland libraries. If they do not begin with `file://`
         * `http` or `https`, sparql querying will break down. This is a helper function
         * to ensure the base uri is properly formatted.
         */
        static std::string prepareBaseUri(std::string str, bool absolute_path = false);

        /*
         * @brief takes a uri as std::string and returns the string
         * with the last section removed;
         *
         * Example: www.uri.com/identifer/PD12345 will
         * turn into www.uri.com/identifier/
         */
        static std::string getNamespaceFromUri(const std::string &uri);

        /*
         * @brief helper function that returns true when
         * uri starts with either `https://` `http://` or `file://`
         * @param uri the uri to test.
         */
        static bool isFormattedUri(std::string uri);

        /*
         * @brief test to see whether a string ends with another string
         * @param fullString the string to test
         * @param ending the ending to test for
         */
        static bool endsWith(std::string const &full_string, std::string const &ending);

        static bool
        assertRegexMatchSplitByNewLine(const std::string &expected_string, const std::string &actual_string);

        static bool assertMatchByNewLine(const std::string &expected_string, const std::string &actual_string);

        /*
         * @brief configures the "myOMEXlib", "myOMEX" and "local"
         * prefixes
         * @ param omex_name the name of the omex container your model is in
         * @param model_name the name of the model your are annotating. Extension should
         * be included or it will be given the ".xml" suffix.
         */
        static std::vector<std::string>
        configureSelfStrings(std::string repository_name, std::string omex_name, std::string model_name);

        static std::string addLocalPrefixToMetaid(std::string metaid, std::string local);

        static std::string
        stringReplace(std::string str, const std::string &string_to_replace, const std::string &replacement);

        static bool startsWith(const std::string &full_string, const std::string &start);

        static bool stringInVector(std::vector<std::string> vec, const std::string &string);

        static xmlDoc *parseXmlDocument(const std::string &xml_string);

        static std::string getXmlNodeProperty(xmlNode *node, const std::string &property);

        static xmlNode *getChildElementCalled(xmlNode *node, const std::string &name);

        static std::vector<xmlNode *> getAllChildElements(xmlNode *node);
    };
}

#endif //LIBOMEXMETA_OMEXMETAUTILS_H
