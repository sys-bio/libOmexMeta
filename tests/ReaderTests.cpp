//
// Created by Ciaran on 4/9/2020.
//

#include <librdf.h>
#include <unordered_map>
#include "gtest/gtest.h"
#include "AnnotationSamples.h"
#include "raptor2.h"
#include "semsim/SemSim.h"
#include "semsim/Reader.h"

class ReaderTests : public ::testing::Test {
public:

    AnnotationSamples samples;
    librdf_world *world;
    raptor_world *raptor_world_ptr;
    librdf_storage *storage;
    librdf_model *model;

    ReaderTests() {

        semsim::LibrdfObjectsTuple objectsTuple = semsim::RDF::init();
        world = std::get<0>(objectsTuple);
        raptor_world_ptr = std::get<1>(objectsTuple);
        storage = std::get<2>(objectsTuple);
        model = std::get<3>(objectsTuple);
    };

    void assertModelSizesAreDifferentAfterParsing(const std::string &annotation_string) {
        semsim::Reader reader(world, model, "rdfxml");
        int size_before = librdf_model_size(model);
        reader.fromString(annotation_string);
        int size_after = librdf_model_size(model);
        ASSERT_GT(size_after, size_before);
    }
};


TEST_F(ReaderTests, TestReaderInstantiation) {
    semsim::Reader reader(world, model, "rdfxml");
    ASSERT_TRUE(true);
}


TEST_F(ReaderTests, TestGetOptions) {
    raptor_domain domain;
    int num_raptor_options = (int) raptor_option_get_count() - 1;
    std::ostringstream os;
    int i = 0;
    while (i != num_raptor_options) {
        raptor_option_description *parser_opt = raptor_world_get_option_description(raptor_world_ptr,
                                                                                    RAPTOR_DOMAIN_PARSER,
                                                                                    (raptor_option) i);
        os << "option, name, label, domain, value type, url" << std::endl;
        if (parser_opt) {

            os << parser_opt->option << "," << parser_opt->name << "," << parser_opt->label << "," << parser_opt->domain
               << "," << parser_opt->value_type << "," << raptor_uri_to_string(parser_opt->uri) << std::endl;
        } else {
            raptor_option_description *serializer_opt = raptor_world_get_option_description(raptor_world_ptr,
                                                                                            RAPTOR_DOMAIN_SERIALIZER,
                                                                                            (raptor_option) i);
            if (serializer_opt) {
                os << serializer_opt->option << "," << serializer_opt->name << "," << serializer_opt->label << ","
                   << serializer_opt->domain
                   << "," << serializer_opt->value_type << "," << raptor_uri_to_string(serializer_opt->uri)
                   << std::endl;
            }
        }
        i++;
    }

    std::cout << os.str() << std::endl;


}

TEST_F(ReaderTests, TestReaderInstantiation3) {
    semsim::Reader reader(world, model, "rdfxml");
    librdf_parser *parser = reader.getParser();
//    librdf_parser_set_feature(parser, (raptor_option*)0, nullptr, 1);
    unsigned int num_raptor_options = raptor_option_get_count();
    std::cout << "num_raptor_options " << num_raptor_options << std::endl;
//    auto x = raptor_option_description();
//    raptor_world_get_parser_description()
    raptor_domain domain;
    auto x = raptor_world_get_option_description(raptor_world_ptr, RAPTOR_DOMAIN_SERIALIZER, (raptor_option) 32);
    if (!x) {
        throw std::invalid_argument("bad");
    }
    std::cout << x->label << std::endl;
    std::cout << x->option << std::endl;
    std::cout << x->name_len << std::endl;
    std::cout << x->label << std::endl;
    std::cout << x->uri << std::endl;
    std::cout << x->value_type << std::endl;
//    void* x;
//    void* y;
//    void* z = raptor_world_get_option_description(raptor_world_ptr, *(const raptor_domain*)x, *(const raptor_option*)y);

//    librdf_uri* f;
//    raptor_option option;
//    const char** name;
//    const char** label;
//    raptor_uri** uri;
//    librdf_parser_
//    feature_i = raptor_world_get_option_from_uri(scontext->serializer->world->raptor_world_ptr, (raptor_uri*)feature);
//    int x = raptor_features_enumerate(option,name, label, uri);
//    librdf_parser_get_feature(parser, f);

//    int i;
//    for (i = 0; i < RAPTOR_FEATURE_LAST; i++) {
//        const char *name;
//        raptor_uri *uri;
//        const char *label;
//        if (raptor_features_enumerate((raptor_feature) i, &name, &uri, &label))
//            continue;
//        /* do something with name, uri and label */
//    }
}

TEST_F(ReaderTests, TestFromString) {
    assertModelSizesAreDifferentAfterParsing(samples.singular_annotation1);
}

TEST_F(ReaderTests, TestFromString2) {
    assertModelSizesAreDifferentAfterParsing(samples.singular_annotation2);
}

TEST_F(ReaderTests, TestFromString3) {
    assertModelSizesAreDifferentAfterParsing(samples.singular_annotation3);
}


TEST_F(ReaderTests, TestFromStringComposite_annotation_pe) {
    assertModelSizesAreDifferentAfterParsing(samples.composite_annotation_pe);
}

TEST_F(ReaderTests, TestFromStringComposite_annotation_pp) {
    assertModelSizesAreDifferentAfterParsing(samples.composite_annotation_pp);
}

TEST_F(ReaderTests, TestFromStringComposite_annotation_pf) {
    assertModelSizesAreDifferentAfterParsing(samples.composite_annotation_pf);
}

TEST_F(ReaderTests, TestFromStringTabular_data1) {
    assertModelSizesAreDifferentAfterParsing(samples.tabular_data1);
}

TEST_F(ReaderTests, TestReaderReadsNamespaces) {
    // todo: finish working out whether namespaces are ported into model when reading
    semsim::Reader reader(world, model, "rdfxml");
    reader.fromString(samples.singular_annotation1);

    librdf_parser *parser = reader.getParser();
    int count = librdf_parser_get_namespaces_seen_count(parser);
    count -= 1; //(0 indexed)

    std::unordered_map<std::string, std::string> map;
    raptor_uri *ns_uri;
    unsigned char *ns;
    const char *prefix;
    std::string nss;
    while (count >= 0) {
        ns_uri = librdf_parser_get_namespaces_seen_uri(parser, count);
        ns = raptor_uri_to_string(ns_uri);
        nss = (const char *) ns;
        prefix = librdf_parser_get_namespaces_seen_prefix(parser, count);
        map[prefix] = nss;
        std::cout << prefix << " " << nss << std::endl;
        count--;
    }
}

TEST_F(ReaderTests, TestEqualityBetweenModelPtrs) {
    semsim::SemsimUtils::download(samples.sbml_url1, samples.sbml_filename1);
    semsim::Reader reader(world, model, "rdfxml");
    ASSERT_EQ(model, reader.getModel());
}

TEST_F(ReaderTests, TestParseNamespaces) {
    semsim::SemsimUtils::download(samples.sbml_url1, samples.sbml_filename1);
    semsim::Reader reader(world, model, "rdfxml");
    reader.fromFile(samples.sbml_filename1);
    auto x = reader.parseNamespacesWithPrefix();
    int size = x.size();
    ASSERT_EQ(6, size);
}


TEST_F(ReaderTests, TestSBMLFromFile1) {
    semsim::SemsimUtils::download(samples.sbml_url1, samples.sbml_filename1);
    std::cout << model << std::endl;

    semsim::Reader reader(world, model, "rdfxml");
    int size_before = librdf_model_size(model);
    reader.fromFile(samples.sbml_filename1);
    int size_after = librdf_model_size(model);
    std::cout << reader.getModel() << std::endl;

    std::cout << size_before << std::endl;
    std::cout << size_after << std::endl;

    raptor_iostream *iostream = raptor_new_iostream_to_file_handle(reader.getRaptorWorld(), stdout);
    librdf_serializer *serializer = librdf_new_serializer(world, "rdfxml", nullptr, nullptr);
    raptor_uri *uri = raptor_new_uri(raptor_world_ptr, reinterpret_cast<const unsigned char *>("./base.xml"));
    librdf_serializer_serialize_model_to_iostream(serializer, uri, reader.getModel(), iostream);
}
//ASSERT_GT(size_after, size_before);
//}



















