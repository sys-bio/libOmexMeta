//
// Created by Ciaran on 4/9/2020.
//

#include "semsim/_Reader.h"
#include "AnnotationSamples.h"
#include "RedlandAPIWrapper.h"

#include <librdf.h>
#include <unordered_map>
#include "gtest/gtest.h"
#include "raptor2.h"

using namespace semsim;

class ReaderTests : public ::testing::Test {
public:

    AnnotationSamples samples;

    LibrdfStorage storage;
    LibrdfModel model;

    ReaderTests() {
        model = LibrdfModel(storage.get());
    };

    static void
    assertModelSizesAreDifferentAfterParsing(const LibrdfModel &model, const std::string &annotation_string) {
        semsim::Reader reader(model, "rdfxml");
        int size_before = reader.getModel().size();
        reader.fromString(annotation_string);
        int size_after = reader.getModel().size();
        ASSERT_GT(size_after, size_before);
    }
};

TEST_F(ReaderTests, TestReaderInstantiation) {
    semsim::Reader reader(model, "rdfxml", "file://./annotations.rdf");
    ASSERT_TRUE(true);
}

TEST_F(ReaderTests, TestReaderGetBastURI) {
    semsim::Reader reader(model, "rdfxml", "file://Base");
    std::string x = reader.getBaseUri().str();
    std::string expected = "file://Base";
    ASSERT_STREQ(x.c_str(), expected.c_str());
}

//TEST_F(ReaderTests, TestGetOptions) {
//    raptor_domain domain;
//    int num_raptor_options = (int) raptor_option_get_count() - 1;
//    raptor_world *raptor_world_ptr = librdf_world_get_raptor(World::getWorld());
//    std::ostringstream os;
//    int i = 0;
//    while (i != num_raptor_options) {
//        raptor_option_description *parser_opt = raptor_world_get_option_description(raptor_world_ptr,
//                                                                                    RAPTOR_DOMAIN_PARSER,
//                                                                                    (raptor_option) i);
//        os << "option, name, label, domain, value type, url" <<
//           std::endl;
//        if (parser_opt) {
//
//            os << parser_opt->option << "," << parser_opt->name << "," << parser_opt->label << "," << parser_opt->domain
//               << "," << parser_opt->value_type << "," <<
//               raptor_uri_to_string(parser_opt->uri) << std::endl;
//        } else {
//            raptor_option_description *serializer_opt = raptor_world_get_option_description(
//                    raptor_world_ptr, RAPTOR_DOMAIN_SERIALIZER, (raptor_option) i);
//            if (serializer_opt) {
//                os << serializer_opt->option << "," << serializer_opt->name << "," << serializer_opt->label << ","
//                   << serializer_opt->domain << "," << serializer_opt->value_type << "," <<
//                   raptor_uri_to_string(serializer_opt->uri) << std::endl;
//            }
//        }
//        i++;
//    }
////    std::cout << os.str() << std::endl;
//}

TEST_F(ReaderTests, TestFromString) {
    assertModelSizesAreDifferentAfterParsing(model, samples.singular_annotation1);
}

TEST_F(ReaderTests, TestFromString2) {
    assertModelSizesAreDifferentAfterParsing(model, samples.singular_annotation2);
}

TEST_F(ReaderTests, TestFromString3) {
    assertModelSizesAreDifferentAfterParsing(model, samples.singular_annotation3);
}


TEST_F(ReaderTests, TestFromStringComposite_annotation_pe) {
    assertModelSizesAreDifferentAfterParsing(model, samples.composite_annotation_pe);
}

TEST_F(ReaderTests, TestFromStringComposite_annotation_pp) {
    assertModelSizesAreDifferentAfterParsing(model, samples.composite_annotation_pp);
}

TEST_F(ReaderTests, TestFromStringComposite_annotation_pf) {
    assertModelSizesAreDifferentAfterParsing(model, samples.composite_annotation_pf);
}

TEST_F(ReaderTests, TestFromStringTabular_data1) {
    assertModelSizesAreDifferentAfterParsing(model, samples.tabular_data1);
}

TEST_F(ReaderTests, TestParseNamespaces) {
    Reader reader(model, "rdfxml", "file://./annotations.rdf");
    reader.fromString(samples.singular_annotation1);
    auto actual = reader.getSeenNamespaces();
    std::vector<std::string> expected = {
            "http://biomodels.net/biology-qualifiers/",
            "http://www.w3.org/1999/02/22-rdf-syntax-ns#"
    };
    ASSERT_EQ(expected, actual);
}
//
//TEST_F(ReaderTests, Test1) {
//    /*
//     * Test that I can read then change settings then read some more.
//     */
//}
//
//
//TEST_F(ReaderTests, Test2) {
//    /*
//     * Test that I can read language other than rdfxml
//     */
//}
//





















