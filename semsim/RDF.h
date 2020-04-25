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

    typedef std::tuple<librdf_world *, raptor_world *, librdf_storage *, librdf_model *> LibRDFObjectsTuple;

    class RDF {
    private:
        librdf_world *world_;
        raptor_world *raptor_world_;
        librdf_storage *storage_;
        librdf_model *model_;

        std::unordered_map<const char *, const char *> namespaces_;

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

        void setNamespaces(const std::unordered_map<const char *, const char *> &namespaces);

        const std::unordered_map<const char *, const char *> &getNamespaces() const;

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

        void declareNamespaces();

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
