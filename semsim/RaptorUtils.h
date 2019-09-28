# ifndef SEMSIM_RAPTOR_UTILS_H_
# define SEMSIM_RAPTOR_UTILS_H_

# include <raptor2.h>

# include <iostream>

namespace semsim {

    inline void SerializeURIStatement(const std::string& subject,
      const std::string& predicate,
      const std::string& object,
      raptor_world* world,
      raptor_serializer* serializer) {

      if (!subject.size())
        throw std::runtime_error("Subject is empty.");
      if (!predicate.size())
        throw std::runtime_error("Predicate is empty.");
      if (!object.size())
        throw std::runtime_error("Object is empty.");

      raptor_statement* s = raptor_new_statement(world);
      s->subject = raptor_new_term_from_uri_string(world, (const unsigned char*)subject.c_str());
      s->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)predicate.c_str());
      s->object = raptor_new_term_from_uri_string(world, (const unsigned char*)object.c_str());
      raptor_serializer_serialize_statement(serializer, s);
      raptor_free_statement(s);
    }

    inline void SerializeURIStatement(const std::string& subject,
      const std::string& predicate,
      double value,
      raptor_world* world,
      raptor_serializer* serializer) {

      if (!subject.size())
        throw std::runtime_error("Subject is empty.");
      if (!predicate.size())
        throw std::runtime_error("Predicate is empty.");

      raptor_statement* s = raptor_new_statement(world);
      std::stringstream ss;
      ss << value;
      std::string value_str=ss.str();
      s->subject = raptor_new_term_from_uri_string(world, (const unsigned char*)subject.c_str());
      s->predicate = raptor_new_term_from_uri_string(world, (const unsigned char*)predicate.c_str());
      s->object = raptor_new_term_from_literal(world, (const unsigned char*)value_str.c_str(), NULL, NULL);
      raptor_serializer_serialize_statement(serializer, s);
      raptor_free_statement(s);
    }

}

# endif
