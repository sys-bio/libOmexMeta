#include "catch.hpp"

#include <zipper/zipper.h>
#include <zipper/unzipper.h>
#include <zipper/tools.h>

#include <vector>
#include <fstream>
#include <ostream>
#include <string>
#include <map>

using namespace zipper;

SCENARIO("archive write", "[zipper]")
{
  GIVEN("An archive outputed to a file")
  {
    // just in case the last test fails there
    // will still be one zip file around delete it first

    if (checkFileExists("ziptest.zip"))
      std::remove("ziptest.zip");

    zipper::Zipper zipper("ziptest.zip");

    WHEN("a file containing 'test file compression' is added and named 'test1'")
    {
      std::ofstream test1("test1.txt");
      test1 << "test file compression";
      test1.flush();
      test1.close();

      std::ifstream test1stream("test1.txt");

      zipper.add(test1stream, "test1.txt");

      test1stream.close();
      zipper.close();

      std::remove("test1.txt");

      zipper::Unzipper unzipper("ziptest.zip");

      THEN("the zip file has one entry named 'test1.txt'")
      {
        std::vector<zipper::ZipEntry> entries = unzipper.entries();
        REQUIRE(entries.size() == 1);
        REQUIRE(entries.front().name == "test1.txt");

        AND_THEN("extracting the test1.txt entry creates a file named 'test1.txt' with the text 'test file compression'")
        {
          unzipper.extractEntry("test1.txt");
          // due to sections forking or creating different stacks we need to make sure the local instance is closed to
          // prevent mixing the closing when both instances are freed at the end of the scope
          unzipper.close();

          REQUIRE(checkFileExists("test1.txt"));

          std::ifstream testfile("test1.txt");
          REQUIRE(testfile.good());

          std::string test((std::istreambuf_iterator<char>(testfile)), std::istreambuf_iterator<char>());
          testfile.close();
          REQUIRE(test == "test file compression");

          AND_WHEN("another file containing 'other data to compression test' and named 'test2.dat' is added inside a folder 'TestFolder'")
          {
            std::ofstream test2("test2.dat");
            test2 << "other data to compression test";
            test2.flush();
            test2.close();

            std::ifstream test2stream("test2.dat");

            zipper.open();
            zipper.add(test2stream, "TestFolder/test2.dat");
            zipper.close();

            test2stream.close();
            std::remove("test2.dat");

            zipper::Unzipper unzipper("ziptest.zip");

            AND_THEN("the zip file has two entrys named 'test1.txt' and 'TestFolder/test2.dat'")
            {
              REQUIRE(unzipper.entries().size() == 2);
              REQUIRE(unzipper.entries().front().name == "test1.txt");
              REQUIRE(unzipper.entries()[1].name == "TestFolder/test2.dat");

              AND_THEN("extracting the test2.dat entry creates a folder 'TestFolder' with a file named 'test2.dat' with the text 'other data to compression test'")
              {
                unzipper.extract();
                unzipper.close();

                REQUIRE(checkFileExists("TestFolder/test2.dat"));

                std::ifstream testfile("TestFolder/test2.dat");
                REQUIRE(testfile.good());

                std::string test((std::istreambuf_iterator<char>(testfile)), std::istreambuf_iterator<char>());
                testfile.close();
                REQUIRE(test == "other data to compression test");

                AND_WHEN("adding a folder to the zip, creates one entry for each file inside the folder with the name in zip as 'Folder/...'")
                {
                  makedir(currentPath() + "/TestFiles/subfolder");
                  std::ofstream test("TestFiles/test1.txt");
                  test << "test file compression";
                  test.flush();
                  test.close();

                  std::ofstream test1("TestFiles/test2.pdf");
                  test1 << "test file compression";
                  test1.flush();
                  test1.close();

                  std::ofstream test2("TestFiles/subfolder/test-sub.txt");
                  test2 << "test file compression";
                  test2.flush();
                  test2.close();

                  zipper.open();
                  zipper.add("TestFiles");
                  zipper.close();

                  zipper::Unzipper unzipper("ziptest.zip");
                  REQUIRE(unzipper.entries().size() == 5);

                  AND_THEN("extracting to a new folder 'NewDestination' craetes the file structure from zip in the new destination folder")
                  {
                    makedir(currentPath() + "/NewDestination");

                    unzipper.extract(currentPath() + "/NewDestination");
                    REQUIRE(checkFileExists("NewDestination/TestFiles/test1.txt"));
                    REQUIRE(checkFileExists("NewDestination/TestFiles/test2.pdf"));
                    REQUIRE(checkFileExists("NewDestination/TestFiles/subfolder/test-sub.txt"));
                  }

                  unzipper.close();
                }
              }
            }

            removeFolder("TestFolder");
            removeFolder("TestFiles");
            removeFolder("NewDestination");
            std::remove("test1.txt");
          }
        }
      }

      std::remove("ziptest.zip");
    }

  }
}
