//
// Created by Ciaran on 4/8/2020.
//

#ifndef LIBSEMSIM_RDF_H
#define LIBSEMSIM_RDF_H

#include "semsim/RedlandAPIWrapper/RedlandAPIWrapper.h"
//#include "semsim/Writer.h"
//#include "semsim/Editor.h"
//#include "semsim/XmlAssistant.h"
//#include "semsim/Query.h"
//#include "semsim/Reader.h"
//#include "semsim/Query.h"

#include "librdf.h"
#include <unordered_map>
#include <string>
#include <iostream>
#include <cstring>
#include <utility>


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
        LibrdfUri base_uri_;
        NamespaceMap namespaces_;
        std::vector<std::string> seen_namespaces_;
        NamespaceMap default_namespaces_ = {
                {"http://purl.org/dc/terms/",                "dcterms"},
                {"http://biomodels.net/biology-qualifiers/", "bqbiol"},
                {"http://biomodels.net/model-qualifiers/",   "bqmodel"},
                {"http://www.bhi.washington.edu/semsim#",    "semsim"},
        };

        RDF(const std::string &storage_type = "memory", const std::string &storage_name = "SemsimStore",
            const char *storage_options = nullptr, const char *model_options = nullptr);

        static RDF fromString(const std::string &str, const std::string &format = "guess");

    };
}





//        LibrdfUri getBaseUri() const;
//
//        std::string getBaseUriAsString() const;
//
//        void setBaseUri(std::string baseUri);
//
//        void setBaseUri(LibrdfUri base_uri);

//        static LibRDFObjectsTuple init();


//        RDF(LibrdfWorld world, RaptorWorld raptor_world_, LibrdfStorage storage, LibrdfModel model);

//        ~RDF();
//
//        RDF(const RDF &libRdfModel);
//
//        RDF(RDF &&libRdfModel) noexcept;
//
//        RDF &operator=(const RDF &libRdfModel);
//
//        RDF &operator=(RDF &&libRdfModel) noexcept;
//
//        const std::unordered_map<std::string, std::string> &getNamespaces() const;
//
//        void setNamespaces(const std::unordered_map<std::string, std::string> &namespaces);
//
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
////        Editor toEditor(std::string xml, XmlAssistantType type);
////
////        Editor *toEditorPtr(std::string xml, XmlAssistantType type);
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
////        int size() const;
////
////        Triples toTriples();
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
