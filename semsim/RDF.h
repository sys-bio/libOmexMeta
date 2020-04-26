//
// Created by Ciaran on 4/8/2020.
//

#ifndef LIBSEMGEN_RDF_H
#define LIBSEMGEN_RDF_H

#include <unordered_map>
#include "librdf.h"
#include "semsim/Writer.h"
#include "semsim/Editor.h"
#include "semsim/XmlAssistant.h"

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

        NamespaceMap namespaces_;
        std::vector<std::string> seen_namespaces_;
        NamespaceMap default_namespaces_ = {
                {"http://purl.org/dc/terms/",                "dcterms"},
                {"http://biomodels.net/biology-qualifiers/", "bqbiol"},
                {"http://biomodels.net/model-qualifiers/",   "bqmodel"},
                {"http://www.bhi.washington.edu/semsim#",    "semsim"},
        };

        semsim::Writer makeWriter(const std::string &format, const std::string &base_uri);


    public:

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

        static RDF fromUrl(std::string url);

        static semsim::RDF fromXML(const std::string &filename, std::string format);

        static RDF fromFile(std::string filename);

        static RDF fromOmex(std::string filename_or_url);

        std::string toString(std::string format, std::string base_uri = "./SemsimModel");

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

        semsim::RDF
        query(std::string query_str, std::string query_format = "sparql", std::string results_mime_type = "text/csv");

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
