//
// Created by Ciaran on 4/8/2020.
//

#ifndef LIBSEMSIM_RDF_H
#define LIBSEMSIM_RDF_H

#include "RedlandAPIWrapper.h"
#include "semsim/_Reader.h"
#include "semsim/Writer.h"
#include "semsim/SemsimUtils.h"
#include "semsim/Triple.h"
#include "semsim/Triples.h"
//#include "semsim/Editor.h"
//#include "semsim/XmlAssistant.h"
//#include "semsim/Query.h"

#include "librdf.h"
#include <unordered_map>
#include <string>
#include <iostream>
#include <cstring>
#include <utility>

using namespace redland;

namespace semsim {

//    class Editor; // forward declaration

    typedef std::unordered_map<std::string, std::string> NamespaceMap;

//    typedef std::tuple<LibrdfWorld, RaptorWorld, LibrdfStorage, LibrdfModel> LibRDFObjectsTuple;

    class RDF {
    private:
        LibrdfStorage storage_;
        LibrdfModel model_;

        static std::vector<std::string> getValidParserNames();

//        semsim::Writer makeWriter(const std::string &format);

    public:
        std::string base_uri_;
        NamespaceMap namespaces_;
        std::vector<std::string> seen_namespaces_;
        NamespaceMap default_namespaces_ = {
                {"http://purl.org/dc/terms/",                "dcterms"},
                {"http://biomodels.net/biology-qualifiers/", "bqbiol"},
                {"http://biomodels.net/model-qualifiers/",   "bqmodel"},
                {"http://www.bhi.washington.edu/semsim#",    "semsim"},
        };

        explicit RDF(const std::string &base_uri = "./Annotations.rdf", const std::string &storage_type = "memory",
                     const std::string &storage_name = "SemsimStore",
                     const char *storage_options = nullptr, const char *model_options = nullptr);

        static RDF fromString(const std::string &str, const std::string &format = "guess");

        const LibrdfModel &getModel() const;

        static std::ostringstream listOptions();

        int size() const;

        std::string toString(const std::string &format = "rdfxml-abbrev", const std::string &base_uri = std::string());

        const std::string &getBaseUri() const;

        void setBaseUri(const std::string base_uri);

        const NamespaceMap &getNamespaces() const;

        void setNamespaces(const NamespaceMap &namespaces);

        Writer makeWriter(const std::string &format);

        std::unordered_map<std::string, std::string>
        propagateNamespacesFromParser(std::vector<std::string> seen_namespaces);

        Triples toTriples();
    };
}

//        static RDF fromUrl(std::string url, std::string filename, std::string format);
//
//        static semsim::RDF fromXML(const std::string &filename, std::string format);
//
//        static RDF fromFile(std::string filename, std::string format);
//
//        static RDF fromOmex(const std::string &filename_or_url, std::string format);
//
//        std::string toString(const std::string &format, const std::string &base_uri);
//
//
////        static RDF fromStream(librdf_stream *stream);
////
////        librdf_stream *toStream();
//
//        void toFile(std::string format);
//
////        Editor toEditor(std::string xml, SemsimXmlType type);
////
////        Editor *toEditorPtr(std::string xml, SemsimXmlType type);
//
//        static std::ostringstream listOptions();
//
//        std::unordered_map<std::string, std::string> propagateNamespacesFromParser(
//                std::vector<std::string> seen_namespaces);
//
//        std::string queryResultsAsStr(const std::string &query_str, const std::string& results_format);
//
////        semsim::ResultsMap queryResultsAsMap(const std::string &query_str);
////
////        semsim::RDF queryResultsAsRDF(const std::string &query_str);
////
////        semsim::Triples queryResultsAsTriples(const std::string &query_str);
////
////
//    };
//}



//    + fromWWW() : static RDF
//    + fromXML() : static RDF
//    + fromFile() : static RDF
//    + fromModel() : static RDF
//    + load
//    + query() : RDF
//    + addStatement() : RDF
//    + removeStatement() : RDF
//    + replaceStatement() : RDF
//    + toString(std::string format) : std::string
//    + toFile(std::string format) : std::string


#endif //LIBSEMSIM_RDF_H
