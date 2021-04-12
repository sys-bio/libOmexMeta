#include "omexmeta/OmexMetaUtils.h"
#include "omexmeta/UriHandler.h"
#include "gtest/gtest.h"
#include <iostream>

using namespace std;
using namespace omexmeta;

class UriHandlerTests : public ::testing::Test {
public:
    void SetUp() override {
    }
};

TEST_F(UriHandlerTests, TestDefaultValues) {
    UriHandler handler;
    const std::string &repository = handler.getRepository();
    const std::string &archive = handler.getArchive();
    const std::string &model = handler.getModel();
    const std::string &local = handler.getLocal();

    ASSERT_STREQ("http://omex-library.org/", repository.c_str());
    ASSERT_STREQ("http://omex-library.org/NewOmex.omex/", archive.c_str());
    ASSERT_STREQ("http://omex-library.org/NewOmex.omex/NewModel.xml", model.c_str());
    ASSERT_STREQ("http://omex-library.org/NewOmex.omex/NewModel.rdf#", local.c_str());
}


TEST_F(UriHandlerTests, SetRepository) {
    UriHandler handler;
    handler.setRepository("http://my-new-omex-library.org/");

    const std::string &repository = handler.getRepository();
    const std::string &archive = handler.getArchive();
    const std::string &model = handler.getModel();
    const std::string &local = handler.getLocal();

    ASSERT_STREQ("http://my-new-omex-library.org/", repository.c_str());
    ASSERT_STREQ("http://my-new-omex-library.org/NewOmex.omex/", archive.c_str());
    ASSERT_STREQ("http://my-new-omex-library.org/NewOmex.omex/NewModel.xml", model.c_str());
    ASSERT_STREQ("http://my-new-omex-library.org/NewOmex.omex/NewModel.rdf#", local.c_str());
}


TEST_F(UriHandlerTests, SetArchive) {
    UriHandler handler;
    handler.setArchive("MyAwesomeArchive.omex");

    const std::string &repository = handler.getRepository();
    const std::string &archive = handler.getArchive();
    const std::string &model = handler.getModel();
    const std::string &local = handler.getLocal();

    ASSERT_STREQ("http://omex-library.org/", repository.c_str());
    ASSERT_STREQ("http://omex-library.org/MyAwesomeArchive.omex/", archive.c_str());
    ASSERT_STREQ("http://omex-library.org/MyAwesomeArchive.omex/NewModel.xml", model.c_str());
    ASSERT_STREQ("http://omex-library.org/MyAwesomeArchive.omex/NewModel.rdf#", local.c_str());
}
TEST_F(UriHandlerTests, SetModel) {
    UriHandler handler;
    handler.setModel("MyAwesomeModel");

    const std::string &repository = handler.getRepository();
    const std::string &archive = handler.getArchive();
    const std::string &model = handler.getModel();
    const std::string &local = handler.getLocal();

    ASSERT_STREQ("http://omex-library.org/", repository.c_str());
    ASSERT_STREQ("http://omex-library.org/NewOmex.omex/", archive.c_str());
    ASSERT_STREQ("http://omex-library.org/NewOmex.omex/MyAwesomeModel.xml", model.c_str());
    ASSERT_STREQ("http://omex-library.org/NewOmex.omex/MyAwesomeModel.rdf#", local.c_str());
}
/*
 * To test UriHandler::uriModifier we need a type which implements the getLocalUri
 * and getModel uri methods.
 */
class Cls {
public:
    std::string getLocalUri() {
        return "http://my-new-omex-library.org/NewOmex.omex/NewModel.rdf";
    }
    std::string getModelUri() {
        return "http://my-new-omex-library.org/NewOmex.omex/NewModel.xml";
    }
};


TEST_F(UriHandlerTests, UriModifierTest1) {
    Cls cls;
    std::string uri_to_modify = "Property";
    ASSERT_STREQ(
            "http://my-new-omex-library.org/NewOmex.omex/NewModel.xml#Property",
            UriHandler::uriModifier<Cls>(cls, uri_to_modify, MODEL_URI).c_str());

    ASSERT_STREQ(
            "http://my-new-omex-library.org/NewOmex.omex/NewModel.rdf#Property",
            UriHandler::uriModifier<Cls>(cls, uri_to_modify, LOCAL_URI).c_str());

    ASSERT_STREQ(
            "Property",
            UriHandler::uriModifier<Cls>(cls, uri_to_modify, NONE).c_str());

    ASSERT_STREQ(
            "https://identifiers.org/Property",
            UriHandler::uriModifier<Cls>(cls, uri_to_modify, IDENTIFIERS_URI).c_str());

}

