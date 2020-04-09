//
// Created by Ciaran on 4/8/2020.
//

#ifndef LIBSEMGEN_RDF_H
#define LIBSEMGEN_RDF_H

#include "librdf.h"
#include "Writer.h"

namespace semsim {
    class RDF {
    private:
        librdf_world *world;
        librdf_storage *storage;
        librdf_parser *parser;
        librdf_model *model;
        raptor_world *raptor_world_ptr;
        std::string name = "semsim";
        librdf_uri *uri;

        semsim::Writer makeWriter(const std::string &format, const std::string &base_uri);

        //todo ensure serializer is in constructor and equality operators...

    public:

        RDF();

        ~RDF();

        RDF(const RDF &libRdfModel);

        RDF(RDF &&libRdfModel) noexcept;

        RDF &operator=(const RDF &libRdfModel);

        RDF &operator=(RDF &&libRdfModel) noexcept;

        bool operator==(const RDF &rhs) const;

        bool operator!=(const RDF &rhs) const;

        static RDF fromUrl(std::string url);

        static RDF fromML(std::string filename);

        static RDF fromRDF(std::string filename);

        void fromString(std::string str);

        void toString(std::string format, std::string base_uri="./SemsimModel");

        void registerNamespace(std::string ns, std::string prefix);

        void toFile(std::string format);

        void addStatement(std::string subject, std::string predicate, std::string resource);




//    + fromWWW() : static RDF
//    + fromML() : static RDF
//    + fromRDF() : static RDF
//    + fromModel() : static RDF
//    + load
//    + query() : RDF
//    + addStatement() : RDF
//    + removeStatement() : RDF
//    + replaceStatement() : RDF
//    + toString(std::string format) : std::string
//    + toFile(std::string format) : std::string

        librdf_serializer *makeSerializer(std::string format);
    };
}

#endif //LIBSEMGEN_RDF_H
