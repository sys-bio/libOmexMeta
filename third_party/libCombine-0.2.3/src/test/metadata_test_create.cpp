#include "catch.hpp"

#include <combine/combinearchive.h>
#include <combine/omexdescription.h>
#include <combine/vcard.h>

#include <sbml/annotation/Date.h>

#include <vector>
#include <fstream>
#include <ostream>
#include <string>
#include <map>

LIBCOMBINE_CPP_NAMESPACE_USE

SCENARIO("getting / setting metadata elements", "[combine][metadata]")
{
  GIVEN("A new vcard and description is is created.")
  {
    OmexDescription desc;
    REQUIRE(desc.getAbout().empty());
    REQUIRE(desc.getDescription().empty());
    REQUIRE(desc.getCreators().size() == 0);
    REQUIRE(desc.getModified().size() == 0);

    VCard vcard;
    REQUIRE(vcard.getEmail().empty());
    REQUIRE(vcard.getFamilyName().empty());
    REQUIRE(vcard.getGivenName().empty());
    REQUIRE(vcard.getOrganization().empty());

    WHEN("the description is changed")
    {
      desc.setAbout(".");
      desc.setDescription("combine archive");
      desc.setCreated(std::string("2016-08-08T11:00:00Z"));

      THEN("the description values are updated")
      {
        REQUIRE(desc.getAbout() == ".");
        REQUIRE(desc.getDescription() == "combine archive");
        REQUIRE(desc.getCreated().getDateAsString() == "2016-08-08T11:00:00Z");

        AND_WHEN("the vcard is changed")
        {
          vcard.setEmail("test@caltech.edu");
          vcard.setGivenName("Sarah");
          vcard.setFamilyName("Keating");
          vcard.setOrganization("Caltech");

          AND_THEN("the vcard is updated")
          {
            REQUIRE(vcard.getEmail() == "test@caltech.edu");
            REQUIRE(vcard.getGivenName() == "Sarah");
            REQUIRE(vcard.getFamilyName() == "Keating");
            REQUIRE(vcard.getOrganization() == "Caltech");

            AND_WHEN("the vcard is added to the description")
            {
              desc.addCreator(vcard);
              THEN("the description contains the vcard")
              {
                REQUIRE(desc.getCreators().size() == 1);


                AND_WHEN("the description is written to file and read back in")
                {
                  std::string xml = desc.toXML();
                  std::vector<OmexDescription> descs = OmexDescription::parseString(xml);


                  THEN("the values remain the same")
                  {
                    REQUIRE(descs.size() == 1);
                    OmexDescription first = descs.front();
                    REQUIRE(first.getAbout() == desc.getAbout());
                    REQUIRE(first.getDescription() == desc.getDescription());
                    REQUIRE(first.getCreated().getDateAsString() == desc.getCreated().getDateAsString());
                    REQUIRE(first.getNumModified() == desc.getNumModified());
                    REQUIRE(first.getNumCreators() == desc.getNumCreators());


                    vcard = first.getCreators().front();

                    REQUIRE(vcard.getEmail() == "test@caltech.edu");
                    REQUIRE(vcard.getGivenName() == "Sarah");
                    REQUIRE(vcard.getFamilyName() == "Keating");
                    REQUIRE(vcard.getOrganization() == "Caltech");
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}
