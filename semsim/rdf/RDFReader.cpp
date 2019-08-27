# include "semsim/rdf/RDFReader.h"

# include "raptor2.h"
# include <iostream>

namespace semsim {
    static std::string RaptorURIToString(raptor_uri* u) {
      unsigned char* c = raptor_uri_to_string(u);
      std::string result((const char*)c);
      raptor_free_memory(c);
      return result;
    }

    static URI RaptorTermToURI(raptor_term* t) {
      if (!t)
        throw std::runtime_error("Raptor term is null");
      switch (t->type) {
        case RAPTOR_TERM_TYPE_URI:
          return URI(RaptorURIToString(t->value.uri));
        default:
          throw std::runtime_error("Raptor term is wrong type - not a URI");
      }
    }

    static std::string RaptorTermToRepr(raptor_term* t) {
      if (!t)
        throw std::runtime_error("Raptor term is null");
      switch (t->type) {
        case RAPTOR_TERM_TYPE_URI:
          return "uri:"+RaptorURIToString(t->value.uri);
        case RAPTOR_TERM_TYPE_LITERAL:
          return "lit:"+std::string((const char*)t->value.literal.string);
        case RAPTOR_TERM_TYPE_BLANK:
          return "<blank>";
        default:
          throw std::runtime_error("Raptor term is wrong type - not a URI");
      }
    }

    static bool isMetaId(const std::string& uri) {
      return uri.find("#") != std::string::npos;
    }

    static bool isMetaId(raptor_term *t) {
      if (!t)
        throw std::runtime_error("Raptor term is null");
      switch (t->type) {
        case RAPTOR_TERM_TYPE_URI:
          return isMetaId(RaptorURIToString(t->value.uri));
        default:
          return false;
      }
    }

    static std::string extractMetaId(const std::string& uri) {
      return uri.substr(uri.find("#")+1, std::string::npos);
    }

    static std::string extractMetaId(raptor_term *t) {
      if (!t)
        throw std::runtime_error("Raptor term is null");
      switch (t->type) {
        case RAPTOR_TERM_TYPE_URI:
          return extractMetaId(RaptorURIToString(t->value.uri));
        default:
          throw std::runtime_error("Expected term to be a uri");
      }
    }

    static void addTermToEntity(EntityBase& entity, const Relation& relation, const Resource& resource) {
      if (relation == bqb::is)
        entity.addDefinition(resource);
      else
        entity.addExtraneousTerm(Term(relation, resource));
    }

    static void addTermToCompositeAnnotation(CompositeAnnotation& annotation, const Relation& relation, const Resource& resource) {
      addTermToEntity(annotation.getEntity(), relation, resource);
    }

    static void addTermToSingularAnnotation(SingularAnnotation& annotation, const Relation& relation, const Resource& resource) {
      addTermToEntity(annotation, relation, resource);
    }

    static void addTermToAnnotation(AnnotationBase& annotation, const Relation& relation, const Resource& resource) {
      if (annotation.isComposite())
        addTermToCompositeAnnotation(dynamic_cast<CompositeAnnotation&>(annotation), relation, resource);
      else
        addTermToSingularAnnotation(dynamic_cast<SingularAnnotation&>(annotation), relation, resource);
    }

    static void process_triple(void* user_data, raptor_statement* triple) {
      Model& model=*(Model*)user_data;
      if (isMetaId(triple->subject)) {
        std::string metaid = extractMetaId(triple->subject);
        if (model.hasComponentWithMetaId(metaid)) {
          Component& component = model.findComponentWithMetaId(metaid);
          if (!component.hasAnnotation()) {
            component.setAnnotation(SingularAnnotation(metaid));
          }
          addTermToAnnotation(component.getAnnotation(), Relation(RaptorTermToURI(triple->predicate)), Resource(RaptorTermToURI(triple->object)));
          // std::cerr << metaid << " " << RaptorTermToRepr(triple->predicate) << " " << RaptorTermToRepr(triple->object) << "\n";
        }
      }
    }

    void applyRDFAnnotationsToModel(Model& model, const std::string& rdf, const std::string& rdf_format) {
      raptor_world* world = raptor_new_world();
      raptor_parser* rdf_parser = raptor_new_parser(world, "rdfxml");
      raptor_parser_set_statement_handler(rdf_parser, &model, process_triple);

      // unsigned char* uri_string = raptor_uri_filename_to_uri_string("");
      raptor_uri* uri = raptor_new_uri(world, (const unsigned char*)".");
      raptor_uri* base_uri = raptor_uri_copy(uri);

      raptor_parser_parse_start(rdf_parser, base_uri);
      raptor_parser_parse_chunk(rdf_parser, (const unsigned char*)rdf.c_str(), rdf.size(), 1);

      raptor_free_parser(rdf_parser);
      raptor_free_uri(base_uri);
      raptor_free_uri(uri);
      // raptor_free_memory(uri_string);

      raptor_free_world(world);
    }
}
