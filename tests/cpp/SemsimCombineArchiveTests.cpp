//
// Created by Ciaran on 4/11/2020.
//

#include <string>
#include "gtest/gtest.h"
#include "semsim/SemsimCombineArchive.h"
#include "AnnotationSamples.h"
#include "semsim/SemSim.h"

#include "combine/combinearchive.h"
#include "omex/CaContent.h"
#include "omex/CaOmexManifest.h"
#include "omex/CaReader.h"
#include "combine/omexdescription.h"

class SemsimCombineArchiveTests : public ::testing::Test {
public:

    AnnotationSamples samples;

    SemsimCombineArchiveTests() = default;

};

TEST_F(SemsimCombineArchiveTests, TestThatUrlIsNotFile
) {
semsim::SemsimCombineArchive combineArchive = semsim::SemsimCombineArchive::fromUrl(
        samples.gold_standard_url2, samples.gold_standard_filename2);
combineArchive.

cleanUp();

}

TEST_F(SemsimCombineArchiveTests, Testy
) {
std::string filename = "/mnt/d/libsemsim/tests/Smith_2004.omex";

CombineArchive combineArchive;
combineArchive.
initializeFromArchive(filename);

int num_entries = combineArchive.getNumEntries();

std::cout << "number of entries: " << num_entries <<
std::endl;
auto locs = combineArchive.getAllLocations();
for (
auto &it
: locs) {
std::cout << it <<
std::endl;
}

OmexDescription description = combineArchive.getMetadataForLocation(locs[1]);
std::cout << description.

toXML()

<<
std::endl;

//    const CaContent *entry = combineArchive.getEntry(1);
//    std::cout << entry->getLocation() << std::endl;
//    std::cout << entry->getAnnotationString() << std::endl;
std::cout << combineArchive.extractEntryToString("./model/smith_2004.rdf") <<
std::endl;


//    std::cout << entry->getCrossRef(0) << std::endl;
//    for (unsigned int i = 0; i < entry->getNumCrossRefs(); i++) {
//        std::cout << i << ": " << entry->getCrossRef(i)->getLocation() << std::endl;
//    }

}

TEST_F(SemsimCombineArchiveTests, Testz
) {
semsim::SemsimCombineArchive archive;
archive.
initializeFromArchive(samples
.gold_standard_filename2);

for (
int i = 0;
i<archive.

getNumEntries();

i++) {
const CaContent *entry = archive.getEntry(i);
std::cout << entry->

getFormat()

<<
std::endl;
std::cout << "entry->getFormat()" <<
std::endl;

}

//    auto *content = archive.getEntryByFormat("cellml");

//    std::cout << content->get << std::endl;
//
//    OmexDescription description = archive.getMetadataForLocation(".");
////    std::string s = description.toXML();
////    std::cout << s << std::endl;
//    for (int i = 0; i < archive.getNumEntries(); ++i) {
//        const CaContent *entry = archive.getEntry(i);
//        std::cout << " " << i << ": location: " << entry->getLocation() << " format: " << entry->getFormat() << std::endl;
////        printMetaDataFor(archive, entry->getLocation());
////        std::cout << entry->getAnnotation()->toXMLString() << std::endl;
//    }

//

//    std::cout << num_entries << std::endl;
//    auto locs = archive.getAllLocations();
//    for (auto &it : locs) {
//        std::cout << it << std::endl;
//    }
//
//    CaOmexManifest *manifest = archive.getManifest();
//    std::cout << manifest << std::endl;
//    auto s = manifest->getListOfContents()->getAnnotationString();
//    std::cout << "S" << s << std::endl;
//    auto x = archive.getEntry(1);
//    std::cout << x->getLocation() << std::endl;
//    const CaContent* content = archive.getEntryByFormat("rdf");
//    content->getLocation();

//    auto y = archive.getEntryByLocation("./model/BIOMD0000000204_new.rdf");
//    auto s = y->getLocation();
//    std::cout << s << std::endl;


}























