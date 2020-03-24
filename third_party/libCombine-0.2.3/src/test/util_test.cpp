#include "catch.hpp"

#include <combine/util.h>
#include <combine/knownformats.h>

LIBCOMBINE_CPP_NAMESPACE_USE

extern std::string getTestFile(const std::string& fileName);

SCENARIO("utility methods", "[combine][util]")
{
  GIVEN("Testing the extension for various files")
  {
    REQUIRE(Util::getExtension("test.xml") == "xml");
    REQUIRE(Util::getExtension("test.tar.gz") == "gz");
    REQUIRE(Util::getExtension("test.tar.bz2") == "bz2");
    REQUIRE(Util::getExtension("c:\\").empty());
    REQUIRE(Util::getExtension("/").empty());
    REQUIRE(Util::getExtension("..").empty());
  }

  GIVEN("Testing of KnownFormats")
  {
    REQUIRE(KnownFormats::isFormat("sbml","http://identifiers.org/combine.specifications/sbml.level-3.version.2"));
    REQUIRE(KnownFormats::isFormat("sbml","http://identifiers.org/combine.specifications/sbml"));
    REQUIRE_FALSE(KnownFormats::isFormat("sbml","something else"));


    REQUIRE(KnownFormats::isFormat("sbml",
            KnownFormats::guessFormat(getTestFile("test-data/BorisEJB.xml"))));
  }
}
