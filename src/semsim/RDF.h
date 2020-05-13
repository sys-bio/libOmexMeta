//
// Created by Ciaran on 4/8/2020.
//

#ifndef LIBSEMGEN_RDF_H
#define LIBSEMGEN_RDF_H

#include <unordered_map>
#include "librdf.h"
#include "Writer.h"
#include "Editor.h"
#include "XmlAssistant.h"
#include "Query.h"

namespace semsim {

    class Editor; // forward declaration

    typedef std::unordered_map<std::string, std::string> NamespaceMap;

    typedef std::tuple<librdf_world *, raptor_world *, librdf_storage *, librdf_model *> LibRDFObjectsTuple;

    class RDF {
    private:
        librdf_world *world_;
        raptor_world *raptor_world_;
        librdf_storage *storage_;
        librdf_model *model_;


        semsim::Writer makeWriter(const std::string &format);

    public:
        librdf_uri *base_uri_;
        NamespaceMap namespaces_;
        std::vector<std::string> seen_namespaces_;
        NamespaceMap default_namespaces_ = {
                {"http://purl.org/dc/terms/",                "dcterms"},
                {"http://biomodels.net/biology-qualifiers/", "bqbiol"},
                {"http://biomodels.net/model-qualifiers/",   "bqmodel"},
                {"http://www.bhi.washington.edu/semsim#",    "semsim"},
        };

        librdf_uri *getBaseUri() const;

        std::string getBaseUriAsString() const;

        void setBaseUri(std::string baseUri);

        void setBaseUri(librdf_uri *base_uri);

        static LibRDFObjectsTuple init();

        RDF();

        RDF(librdf_world *world, raptor_world *raptor_world_, librdf_storage *storage, librdf_model *model);

        ~RDF();

        RDF(const RDF &libRdfModel);

        RDF(RDF &&libRdfModel) noexcept;

        RDF &operator=(const RDF &libRdfModel);

        RDF &operator=(RDF &&libRdfModel) noexcept;

        bool operator==(const RDF &rhs) const;

        bool operator!=(const RDF &rhs) const;

        const std::unordered_map<std::string, std::string> &getNamespaces() const;

        void setNamespaces(const std::unordered_map<std::string, std::string> &namespaces);

        static RDF fromUrl(std::string url, std::string filename, std::string format);

        static semsim::RDF fromXML(const std::string &filename, std::string format);

        static RDF fromFile(std::string filename, std::string format);

        static RDF fromOmex(const std::string &filename_or_url, std::string format);

        std::string toString(const std::string &format, const std::string &base_uri);

        static RDF fromString(const std::string &str, std::string format = "guess");

        static RDF fromStream(librdf_stream *stream);

        librdf_stream *toStream();

        void toFile(std::string format);

        Editor toEditor(std::string xml, XmlAssistantType type);

        static std::ostringstream listOptions();

        librdf_world *getWorld() const;

        librdf_storage *getStorage() const;

        librdf_model *getModel() const;

        raptor_world *getRaptorWorld() const;

        void setWorld(librdf_world *world);

        void setStorage(librdf_storage *storage);

        void setModel(librdf_model *model);

        void setRaptorWorld(raptor_world *raptorWorldPtr);

        std::unordered_map<std::string, std::string> propagateNamespacesFromParser(
                std::vector<std::string> seen_namespaces);

        std::string queryResultsAsStr(const std::string &query_str, const std::string& results_format);

        semsim::ResultsMap queryResultsAsMap(const std::string &query_str);

        semsim::RDF queryResultsAsRDF(const std::string &query_str);

        semsim::Triples queryResultsAsTriples(const std::string &query_str);

        int size() const;

        Triples toTriples();
    };
}



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


#endif //LIBSEMGEN_RDF_H
