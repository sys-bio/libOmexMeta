


#include <semsim/uri.h>
#include <semsim/Resource.h>
#include <sbml/SBMLTypes.h>
#include "gtest/gtest.h"
#include "SBMLFactory.h"

using namespace semsim;
using namespace std;

class RelationTests : public ::testing::Test {
public:
    std::string url_str1;
    Url url;
    SBMLDocument* doc;

    void SetUp() override {
        url_str1 = "http://co.mbine.org/standards/qualifiers";
        url = Url(url_str1);

        doc = semsim_test::SBMLFactory::getSBMLDocument(semsim_test::SBML_ANNOTATED);
    }

};


TEST_F(RelationTests, TestInstantiation){
    Relation relation(url);
    ASSERT_STREQ(relation.toString().c_str(), url_str1.c_str() );
}
